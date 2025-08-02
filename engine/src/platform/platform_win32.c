#include "platform/platform.h"

// Windows platform layer
#if PLATFORM_WINDOWS

#include "core/logger.h"

#include <windows.h>
#include <windowsx.h> // param input extraction

typedef struct internal_state {
    HINSTANCE h_instance;
    HWND hwnd;
} internal_state;

// Clock
static float64_t clock_frequency;
static LARGE_INTEGER start_time;

LRESULT CALLBACK win32_process_message(HWND hwnd, uint32_t msg, WPARAM w_param, LPARAM l_param);

bool8_t platform_startup(
    platform_state *plat_state,
    const char *app_name,
    int32_t x, int32_t y,
    int32_t width, int32_t height) {

    plat_state -> internal_state = malloc(sizeof(internal_state));
    internal_state *state = (internal_state *)plat_state -> internal_state;

    state -> h_instance = GetModuleHandle(0);

    // Setup and register the window class
    HICON icon = LoadIcon(state -> h_instance, IDI_APPLICATION);
    WNDCLASS wc;
    wc.style = CS_DBLCLKS; // Get double-click
    wc.lpfnWndProc = win32_process_message;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = state -> h_instance;
    wc.hIcon = icon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszClassName = "window_class";

    if (!RegisterClassA(&wc)) {
        MessageBoxA(0, "Window registration failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return FALSE;
    }

    // Create window
    uint32_t client_x = x;
    uint32_t client_y = y;
    uint32_t client_width = width;
    uint32_t client_height = height;

    uint32_t window_x = client_x;
    uint32_t window_y = client_y;
    uint32_t window_width = client_width;
    uint32_t window_height = client_height;

    uint32_t window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
    uint32_t window_ex_style = WS_EX_APPWINDOW;

    window_style |= WS_MAXIMIZEBOX;
    window_style |= WS_MINIMIZEBOX;

    // Obtain the size of the border
    RECT border_rect = {0, 0, 0, 0};
    AdjustWindowRectEx(&border_rect, window_style, FALSE, window_ex_style);

    // In this case, border rectangle is negative
    window_x += border_rect.left;
    window_y += border_rect.top;

    // Grow by the size of the OS border
    window_width += border_rect.right - border_rect.left;
    window_height += border_rect.bottom - border_rect.top;

    HWND handle = CreateWindowExA(
        window_ex_style, "window_class", app_name,
        window_style,
        window_x, window_y, window_width, window_height,
        0, 0, state -> h_instance, 0);

    if (!handle) {
        MessageBoxA(NULL, "Window creation failed!", "Error", MB_ICONEXCLAMATION | MB_OK);

        FATAL("Window creation failed!");
        return FALSE;
    }
    else {
        state -> hwnd = handle;
    }

    // Show the window
    bool32_t should_activate = TRUE;
    int32_t show_window_cmd_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;
    ShowWindow(state -> hwnd, show_window_cmd_flags);

    // Clock setup
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    clock_frequency = 1.0 / (float64_t)frequency.QuadPart;
    QueryPerformanceCounter(&start_time);

    return TRUE;
}

void platform_shutdown(platform_state *plat_state) {
    // Simply cold-cast to the known type
    internal_state *state = (internal_state *)plat_state -> internal_state;

    if (state -> hwnd) {
        DestroyWindow(state -> hwnd);
        state -> hwnd = 0;
    }
}

bool8_t platform_pump_msg(platform_state *plat_state) {
    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return TRUE;
}

void* platform_allocate(uint64_t size, bool8_t aligned) {
    return malloc(size);
}

void platform_free(void *block, bool8_t aligned) {
    free(block);
}

void* platform_zero_memory(void *block, uint64_t size) {
    return memset(block, 0, size);
}

void* platform_copy_memory(void *dest, const void *src, uint64_t size) {
    return memcpy(dest, src, size);
}

void* platform_set_memory(void *dest, int32_t value, uint64_t size) {
    return memset(dest, value, size);
}

void platform_console_write(const char* msg, uint8_t color) {
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // FATAL, ERROR, WARNING, INFO, DEBUG, TRACE
    static uint8_t levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[color]);
    OutputDebugStringA(msg);
    uint64_t msg_len = strlen(msg);
    LPDWORD num_written = 0;
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), msg, (DWORD)msg_len, num_written, 0);
}

void platform_console_write_error(const char* msg, uint8_t color) {
    HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
    // FATAL, ERROR, WARNING, INFO, DEBUG, TRACE
    static uint8_t levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[color]);
    OutputDebugStringA(msg);
    uint64_t msg_len = strlen(msg);
    LPDWORD num_written = 0;
    WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), msg, (DWORD)msg_len, num_written, 0);
}

float64_t platform_get_absolute_time() {
    LARGE_INTEGER current_time;
    QueryPerformanceCounter(&current_time);
    return (float64_t)current_time.QuadPart * clock_frequency;
}

void platform_sleep(uint64_t ms) {
    Sleep(ms);
}

LRESULT CALLBACK win32_process_message(HWND hwnd, uint32_t msg, WPARAM w_param, LPARAM l_param) {
    switch (msg) {
        case WM_ERASEBKGND:
            // Notify the OS that erasing will be handled by the app to prevent flickering
            return 1;
        case WM_CLOSE:
            // Fire an event to close the app
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_SIZE: {
            // Get the update size
            // RECT r;
            // GetClientRect(hwnd, &r);
            // int32_t width = r.right - r.left;
            // int32_t height = r.bottom - r.top;

            // Fire an event to resize the app
            // return 0;
        } break;
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP: {
            // Key pressed/released
            // bool8_t pressed = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
            // TODO: Handle key events
        } break;
        case WM_MOUSEMOVE: {
            // Mouse moved
        } break;
        case WM_MOUSEWHEEL: {
            // int32_t z_delta = GET_WHEEL_DELTA_WPARAM(w_param);
            // if (z_delta != 0) {
            //     // Flatten the input to an OS-independent {-1, 1}
            //     z_delta = (z_delta < 0) ? -1 : 1;
            //     // TODO: Handle mouse wheel input
            // }
        } break;
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP: {
            // bool8_t pressed = (msg == WM_LBUTTONDOWN || msg == WM_MBUTTONDOWN || msg == WM_RBUTTONDOWN);
            // TODO: Handle mouse button events
        } break;
    }

    return DefWindowProcA(hwnd, msg, w_param, l_param);
}

#endif // PLATFORM_WINDOWS