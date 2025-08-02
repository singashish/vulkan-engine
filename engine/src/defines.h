#pragma once

// Unsigned int types
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

// Signed int types
typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

// Floating point types
typedef float float32;
typedef double float64;

// Boolean type
typedef int bool32;
typedef char bool8;

// Properly define static assertions
#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif

// Ensure all type are of the correct size
STATIC_ASSERT(sizeof(uint8) == 1, "uint8 must be 1 byte");
STATIC_ASSERT(sizeof(uint16) == 2, "uint16 must be 2 bytes");
STATIC_ASSERT(sizeof(uint32) == 4, "uint32 must be 4 bytes");
STATIC_ASSERT(sizeof(uint64) == 8, "uint64 must be 8 bytes");

STATIC_ASSERT(sizeof(int8) == 1, "int8 must be 1 byte");
STATIC_ASSERT(sizeof(int16) == 2, "int16 must be 2 bytes");
STATIC_ASSERT(sizeof(int32) == 4, "int32 must be 4 bytes");
STATIC_ASSERT(sizeof(int64) == 8, "int64 must be 8 bytes");

STATIC_ASSERT(sizeof(float32) == 4, "float32 must be 4 bytes");
STATIC_ASSERT(sizeof(float64) == 8, "float64 must be 8 bytes");

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