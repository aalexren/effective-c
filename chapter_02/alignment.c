#include <stdio.h>
#include <stdalign.h>
#include <stddef.h>

struct S { int i; double d; char c; };

int main(void) {
    printf("Alignment of struct S: %zu\n", alignof(struct S));
    printf("Size of struct S: %zu\n", sizeof(struct S));
    
    // Show member offsets
    printf("Offset of i: %zu\n", offsetof(struct S, i));
    printf("Offset of d: %zu\n", offsetof(struct S, d));
    printf("Offset of c: %zu\n", offsetof(struct S, c));

    unsigned char bad_buff[sizeof(struct S)];
    alignas(struct S) unsigned char good_buff[sizeof(struct S)];

    // Get addresses
    uintptr_t bad_addr = (uintptr_t)(void*)bad_buff;
    uintptr_t good_addr = (uintptr_t)(void*)good_buff;
    size_t alignment = alignof(struct S);

    printf("=== STRUCT INFO ===\n");
        printf("sizeof(struct S) = %zu bytes\n", sizeof(struct S));
        printf("alignof(struct S) = %zu bytes\n\n", alignof(struct S));
    
    printf("=== BUFFER ADDRESSES ===\n");
    printf("bad_buff address:  %p (decimal: %lu)\n", (void*)bad_buff, bad_addr);
    printf("good_buff address: %p (decimal: %lu)\n\n", (void*)good_buff, good_addr);
    
    // Check alignment
    printf("=== ALIGNMENT CHECK ===\n");
    printf("Required alignment: %zu bytes\n", alignment);
    printf("\nbad_buff:\n");
    printf("  Address %% %zu = %lu\n", alignment, bad_addr % alignment);
    printf("  Is aligned? %s %s\n", 
            (bad_addr % alignment == 0) ? "YES ✓" : "NO ✗",
            (bad_addr % alignment == 0) ? "" : "← MISALIGNED!");
    
    printf("\ngood_buff:\n");
    printf("  Address %% %zu = %lu\n", alignment, good_addr % alignment);
    printf("  Is aligned? %s\n", 
            (good_addr % alignment == 0) ? "YES ✓" : "NO ✗");
    
    struct S *bad_ptr = (struct S*)bad_buff;
    struct S *good_ptr = (struct S*)good_buff;

    // Demonstrate potential issue
       printf("\n=== DEMONSTRATION ===\n");
       if (bad_addr % alignment != 0) {
           printf("⚠️  bad_s_ptr is MISALIGNED!\n");
           printf("   Accessing bad_s_ptr->d (double at offset %zu) may:\n", offsetof(struct S, d));
           printf("   - Cause SIGBUS/SIGSEGV on ARM/RISC-V\n");
           printf("   - Be slower on x86-64\n");
           printf("   - Is Undefined Behavior per C standard\n");
       }
       
       if (good_addr % alignment == 0) {
           printf("✅ good_s_ptr is PROPERLY ALIGNED!\n");
           printf("   Safe to access all members.\n");
       }
}