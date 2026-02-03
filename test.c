#include "VCL_SYS.h"

int_ vcl_asm_add(int_ a, int_ b) {
    int_ result = a;
    __asm__ (
        "add %1, %0"      // %0 is result, %1 is b
        : "+r" (result)   // Output: + means read/write, r means any register
        : "r" (b)         // Input: r means any register
        : "cc"            // Flags clobber
    );
    return result;
}

int main() {
    string dynamic_str = vcl_string_new();
    vcl_assign_string(&dynamic_str, "Hello world!\n");
      
    vcl_print(dynamic_str);

    vcl_assign_string(&dynamic_str, "This is the resized version of the same string\n");

    vcl_print(dynamic_str);

    vcl_assign_string(&dynamic_str, to_string(vcl_asm_add(3ULL, 2ULL)));

    vcl_print(dynamic_str);

    return 0;
}