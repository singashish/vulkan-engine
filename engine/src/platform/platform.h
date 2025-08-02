#pragma once

#include "defines.h"

typedef struct platform_state {
    void *internal_state;
} platform_state;

API bool8 platform_init(
    platform_state *plat_state,
    const char *app_name,
    int32 x, int32 y,
    int32 width, int32 height);

API void platform_shutdown(platform_state *plat_state);

API bool8 platform_pump_msg(platform_state *plat_state);

void* platform_allocate(uint64 size, bool8 aligned);
void platform_free(void *block, bool8 aligned);
void* platform_zero_memory(void *block, uint64 size);
void* platform_copy_memory(void *dest, const void *src, uint64 size);
void* platform_set_memory(void *dest, int32 value, uint64 size);

void platform_console_write(const char* msg, uint8 color);
void platform_console_write_error(const char* msg, uint8 color);

float64 platform_get_absolute_time();

// Sleep on the thread for the provided milliseconds.
// This blocks the main thread.
// Should only be used for giving time back to the OS for unused update power.
// That's why its not exported.
void platform_sleep(uint64 ms);