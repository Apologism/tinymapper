#include <stdio.h>

#include "process.h"

int main() {
    // get a handle to the target process.
    HANDLE process = acquire_process_handle("test.exe", PROCESS_ALL_ACCESS);

    printf("%d", process);
    return 0;
}
