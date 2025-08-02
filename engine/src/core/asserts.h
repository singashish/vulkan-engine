#pragma once

#include "defines.h"

// Disable assertion by commeting out the next line
#define ASSERTS_ENABLED

#ifdef ASSERTS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

API void assert_failed(const char* expression, const char* msg, const char* file, int32 line);

#define ASSERT(expr)                                                        \
    {                                                                       \
        if (expr) {                                                         \
        } else {                                                            \
            assert_failed(#expr, "", __FILE__, __LINE__);                   \
            debugBreak();                                                   \
        }                                                                   \
    }

#define ASSERT_MSG(expr, msg)                                               \
    {                                                                       \
        if (expr) {                                                         \
        } else {                                                            \
            assert_failed(#expr, msg, __FILE__, __LINE__);                  \
            debugBreak();                                                   \
        }                                                                   \
    }

#ifdef _DEBUG
#define ASSERT_DEBUG(expr)                                                  \
    {                                                                       \
        if (expr) {                                                         \
        } else {                                                            \
            assert_failed(#expr, "", __FILE__, __LINE__);                   \
            debugBreak();                                                   \
        }                                                                   \
    }
#else
#define ASSERT_DEBUG(expr)
#endif

#else // ASSERTS_ENABLED
#define ASSERT(expr)
#define ASSERT_MSG(expr, msg)
#define ASSERT_DEBUG(expr)
#endif // ASSERTS_ENABLED