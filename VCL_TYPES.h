#pragma once

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

#if defined(_M_X64) || defined(__x86_64__)
    typedef w64 wild; // 64-bit for x64
    typedef u64 uint;
    typedef u64 int_;
#elif defined(_M_IX86) || defined(__i386__)
    typedef w32 wild; // 32-bit for x86
    typedef u32 uint;
    typedef u32 int_;
#else
    #error "Unsupported Architecture"
#endif

#pragma pack(push, 1)
typedef struct {
    wild len;
    w8 data[];
} vnl_osstring;
#pragma pack(pop)