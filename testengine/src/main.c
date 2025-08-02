#include <core/logger.h>
#include <core/asserts.h>

#include <platform/platform.h>

int main() {
    FATAL("This is a fatal error with code %d", 404);
    ERROR("This is an error with code %d", 500);
    WARNING("This is a warning with code %d", 300);
    INFO("This is an info message with code %d", 200);
    DEBUG("This is a debug message with code %d", 100);
    TRACE("This is a trace message with code %d", 0);

    platform_state state;
    if (platform_init(&state, "Test Engine", 100, 100, 800, 600)) {
        while (TRUE) {
            platform_pump_msg(&state);
        }
    }
    platform_shutdown(&state);

    return 0;
}