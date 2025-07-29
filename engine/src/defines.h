#pragma once

// Unsigned int types
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

// Signed int types
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

// Floating point types
typedef float float32_t;
typedef double float64_t;

// Boolean type
typedef int bool32_t;
typedef char bool8_t;

// Properly define static assertions
#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif

// Ensure all type are of the correct size
STATIC_ASSERT(sizeof(uint8_t) == 1, "uint8_t must be 1 byte");
STATIC_ASSERT(sizeof(uint16_t) == 2, "uint16_t must be 2 bytes");
STATIC_ASSERT(sizeof(uint32_t) == 4, "uint32_t must be 4 bytes");
STATIC_ASSERT(sizeof(uint64_t) == 8, "uint64_t must be 8 bytes");

STATIC_ASSERT(sizeof(int8_t) == 1, "int8_t must be 1 byte");
STATIC_ASSERT(sizeof(int16_t) == 2, "int16_t must be 2 bytes");
STATIC_ASSERT(sizeof(int32_t) == 4, "int32_t must be 4 bytes");
STATIC_ASSERT(sizeof(int64_t) == 8, "int64_t must be 8 bytes");

STATIC_ASSERT(sizeof(float32_t) == 4, "float32_t must be 4 bytes");
STATIC_ASSERT(sizeof(float64_t) == 8, "float64_t must be 8 bytes");

#define TRUE 1
#define FALSE 0

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define PLATFORM_WINDOWS 1
#ifndef _WIN64
#error "This project requires a 64-bit Windows platform."
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
#define PLATFORM_LINUX 1
#else
#error "Unknown platform!"
#endif

#ifdef EXPORT
// Exports
#ifdef _MSC_VER
#define API __declspec(dllexport)
#else
#define API __attribute__((visibility("default")))
#endif
#else
// Imports
#ifdef _MSC_VER
#define API __declspec(dllimport)
#else
#define API
#endif
#endif