#pragma once
#define NULL ((void*)0)

typedef unsigned char       w8;
typedef unsigned short      w16;
typedef unsigned int        w32;
typedef unsigned long long  w64;

typedef w8  u8;
typedef w16 u16;
typedef w32 u32;
typedef w64 u64;

typedef signed char      i8;
typedef signed short     i16;
typedef signed int       i32;
typedef signed long long i64;

typedef float f32;
typedef float float_;
typedef double f64;
typedef double double_;

typedef char bool_;
typedef char byte;

#if defined(_M_X64) || defined(__x86_64__)
    typedef w64 wild; // 64-bit for x64
    typedef u64 uint;
    typedef i64 int_;
#elif defined(_M_IX86) || defined(__i386__)
    typedef w32 wild; // 32-bit for x86
    typedef u32 uint;
    typedef i32 int_;
#elif defined(__AVR__) || defined(__MSP430__) || defined(__I8086__) || defined(__H8300__)
    typedef w16 wild;
    typedef u16 uint;
    typedef i16 int_;
#elif defined(__SIZEOF_POINTER__)
    #if __SIZEOF_POINTER__ == 8
        typedef w64 wild;
    #elif __SIZEOF_POINTER__ == 4
        typedef w32 wild;
    #else
        typedef w16 wild;
    #endif
#else
    #error "Unsupported Architecture"
#endif

typedef char char_;

#if defined(_WIN32)
#define OSSTR_FMT 1
#else
#define OSSTR_FMT 0
#endif

#pragma pack(push, 1)

typedef struct {
    w8 _fmt;    // 0: UTF-8, 1: UTF-16, 2: Raw/Blob
    wild _len;  // Byte length
    wild _cap;  // Total capacity
    wild _data; // The pointer
} string;

static inline string vcl_string_new() {
    string s = { OSSTR_FMT, 0, 0, 0 };
    return s;
}

#pragma pack(pop)