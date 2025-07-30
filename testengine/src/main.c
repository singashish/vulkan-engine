#include <core/logger.h>
#include <core/asserts.h>

int main() {
    FATAL("This is a fatal error with code %d", 404);
    ERROR("This is an error with code %d", 500);
    WARNING("This is a warning with code %d", 300);
    INFO("This is an info message with code %d", 200);
    DEBUG("This is a debug message with code %d", 100);
    TRACE("This is a trace message with code %d", 0);

    ASSERT(1 == 2); // This will trigger an assertion failure
    return 0;
}