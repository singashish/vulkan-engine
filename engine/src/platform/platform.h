#pragma once

#include "defines.h"

typedef struct platform_state {
    void *internal_state;
} platform_state;

API bool8_t platform_startup(
    platform_state *plat_state,
    const char *app_name,
    int32_t x, int32_t y,
    int32_t width, int32_t height);

API void platform_shutdown(platform_state *plat_state);

API bool8_t platform_pump_msg(platform_state *plat_state);

void* platform_allocate(uint64_t size, bool8_t aligned);
void platform_free(void *block, bool8_t aligned);
void* platform_zero_memory(void *block, uint64_t size);
void* platform_copy_memory(void *dest, const void *src, uint64_t size);
void* platform_set_memory(void *dest, int32_t value, uint64_t size);

void platform_console_write(const char* msg, uint8_t color);
void platform_console_write_error(const char* msg, uint8_t color);

float64_t platform_get_absolute_time();

// Sleep on the thread for the provided milliseconds.
// This blocks the main thread.
// Should only be used for giving time back to the OS for unused update power.
// That's why its not exported.
void platform_sleep(uint64_t ms);