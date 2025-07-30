#pragma once

#include "defines.h"

#define LOG_WARNING_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// Disable debug and trace logging in release builds
#if RELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

typedef enum log_level {
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_TRACE
} log_level;

bool8_t initialize_logging();
void shutdown_logging();

API void log_output(log_level level, const char* message, ...);

// Logs a fatal-level message
#define FATAL(message, ...) \
    log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);

#ifndef ERROR
// Logs an error-level message
#define ERROR(message, ...) \
    log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARNING_ENABLED == 1
// Logs a warning-level message
#define WARNING(message, ...) \
    log_output(LOG_LEVEL_WARNING, message, ##__VA_ARGS__);
#else
// Does nothing if warnings are disabled
#define WARNING(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
// Logs an info-level message
#define INFO(message, ...) \
    log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
// Does nothing if info logging is disabled
#define INFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
// Logs a debug-level message
#define DEBUG(message, ...) \
    log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
// Does nothing if debug logging is disabled
#define DEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
// Logs a trace-level message
#define TRACE(message, ...) \
    log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
// Does nothing if trace logging is disabled
#define TRACE(message, ...)
#endif