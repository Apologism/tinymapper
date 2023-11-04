#include "process.h"

int main() {
    // get a handle to the target process.
    HANDLE process = acquire_process_handle("test.exe", PROCESS_ALL_ACCESS);

    if (process == INVALID_HANDLE_VALUE) {
        puts("error: failed to get a handle to the target process.");
    }

    CloseHandle(process);

    return 0;
}
