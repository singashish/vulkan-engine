#include "logger.h"
#include "asserts.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

bool8_t initialize_logging() {
    // Initialize logging subsystem
    return TRUE;
}

void shutdown_logging() {
    // Clean up logging subsystem
    // This function can be used to flush logs or release resources
}

void log_output(log_level level, const char* message, ...) {
    const char* level_strings[] = {
        "FATAL : ",
        "ERROR : ",
        "WARNING : ",
        "INFO : ",
        "DEBUG : ",
        "TRACE : "
    };

    // bool8_t is_error = (level == LOG_LEVEL_FATAL || level == LOG_LEVEL_ERROR);
    char output_msg[32000];
    memset(output_msg, 0, sizeof(output_msg));

    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(output_msg, 32000, message, arg_ptr);
    va_end(arg_ptr);

    char final_output[32000];
    snprintf(final_output, 32000, "%s%s\n", level_strings[level], output_msg);

    printf("%s", final_output);
}

void assert_failed(const char* expression, const char* msg, const char* file, int32_t line) {
    log_output(LOG_LEVEL_FATAL, "Assertion failed: %s\nmessage: %s\nfile: %s\nline: %d\n",
                expression, msg, file, line);
}