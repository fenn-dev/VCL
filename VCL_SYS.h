#pragma once
#include "VCL_TYPES.h"

// --- OS ABSTRACTION LAYER ---
#if defined(_WIN32)
    #ifndef WINAPI
        #define WINAPI __stdcall
    #endif
    #define NULL ((void*)0)
    extern void* WINAPI GetStdHandle(w32 nStdHandle);
    extern int   WINAPI WriteFile(void* hFile, const void* lpBuffer, w32 nBytes, w32* lpWritten, void* lpOverlapped);
    extern void  WINAPI ExitProcess(w32 uExitCode);
    #define vcl_STDOUT_HANDLE GetStdHandle((w32)-11)
#else
    extern long write(int fd, const void *buf, unsigned long count);
    extern void _exit(int status);
    #define vcl_STDOUT_HANDLE 1
    #define NULL ((void*)0)
#endif

// --- HAND-ROLLED UTILITIES ---

static inline wild vcl_strlen(const char* s) {
    const char* p = s;
    while (*p) p++;
    return (wild)(p - s);
}

static inline void vcl_memcpy(void* dest, const void* src, wild n) {
    char* d = (char*)dest;
    const char* s = (char*)src;
    while (n--) *d++ = *s++;
}

// --- CORE STRING LOGIC ---

static inline void vcl_string_assign_c(string* s, const char* src) {
    if (!src) return;
    wild slen = vcl_strlen(src);
    if (slen > s->_cap) {
        extern void* realloc(void* ptr, wild size); 
        void* new_ptr = realloc((void*)s->_data, slen);
        if (new_ptr) {
            s->_data = (wild)new_ptr;
            s->_cap = slen;
        }
    }
    vcl_memcpy((void*)s->_data, src, slen);
    s->_len = slen;
}

static inline void vcl_string_assign_s(string* s, string src) {
    if (src._len == 0) return;
    if (src._len > s->_cap) {
        extern void* realloc(void* ptr, wild size); 
        void* new_ptr = realloc((void*)s->_data, src._len);
        if (new_ptr) {
            s->_data = (wild)new_ptr;
            s->_cap = src._len;
        }
    }
    vcl_memcpy((void*)s->_data, (void*)src._data, src._len);
    s->_len = src._len;
    s->_fmt = src._fmt;
}

// Helper macro for internal use before the official one is defined
#define _internal_assign(s, src) vcl_string_assign_c(s, src)

static inline string to_string(wild value) {
    string s = vcl_string_new();
    char buffer[24]; 
    int_ i = 0;

    if (value == 0) {
        vcl_string_assign_c(&s, "0"); // Call the specific _c function
        return s;
    }

    while (value > 0) {
        buffer[i++] = (char)((value % 10) + 48);
        value /= 10;
    }

    char final[24];
    for (int_ j = 0; j < i; j++) {
        final[j] = buffer[i - 1 - j];
    }
    final[i] = '\0';

    vcl_string_assign_c(&s, final); // Call the specific _c function
    return s;
}

static inline void vcl_print_s(string s) {
    w32 written;
    WriteFile(vcl_STDOUT_HANDLE, (void*)s._data, (w32)s._len, &written, NULL);
}

static inline void vcl_print_c(const char* c) {
    vcl_print_s((string){0, vcl_strlen(c), 0, (wild)c});
}

// --- UNIVERSAL VCL INTERFACE ---

#define vcl_assign_string(s, src) _Generic((src), \
    string: vcl_string_assign_s, \
    char*: vcl_string_assign_c, \
    const char*: vcl_string_assign_c \
)(s, src)

#define vcl_print(x) _Generic((x), \
    string: vcl_print_s,           \
    char*: vcl_print_c,            \
    const char*: vcl_print_c       \
)(x)
