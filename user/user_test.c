#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/riscv.h"

#define PAGES 5 // Number of pages to check

int main() {
    int accessed;
    uint64 *pages[PAGES];

    // Allocate pages
    for (int i = 0; i < PAGES; i++) {
        pages[i] = (uint64 *) sbrk(PGSIZE); // Allocate one page
    }

    // Access some of the pages to set the PTE_A bit
    *pages[1] = 1; // Access page 1
    *pages[3] = 3; // Access page 3

    // Check the access bit status using pgaccess
    if (pgaccess((uint64 *) pages, PAGES, &accessed) < 0) {
        printf("pgaccess failed\n");
        exit(1);
    }

    // Print the accessed bitmask
    printf("Accessed bitmask: %d\n", accessed);
    // Expected output: binary 1010 (decimal 10), meaning pages 1 and 3 were accessed

    exit(0);
}
