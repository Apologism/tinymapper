#ifndef TINYMAPPER_PROCESS_H
#define TINYMAPPER_PROCESS_H

#include <Windows.h>
#include <tlhelp32.h>
#include <stdint.h>
#include <stdio.h>

/// Finds a process with the filename that matches `ident`, then opens that process with permissions `perms`.
///
/// Note: as of right now numeric identifiers are not supported.
/// If it doesn't find the handle it will return an invalid handle value.
static HANDLE acquire_process_handle(const char* ident, uint32_t perms) {
    // pointer to list of processes.
    HANDLE process_list = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    // process entry struct where we'll be filling in the information.
    PROCESSENTRY32 process_info = { .dwSize = sizeof(PROCESSENTRY32) };

    if (process_list == INVALID_HANDLE_VALUE) {
        puts("Error: couldn't get handle to process list.");
        return INVALID_HANDLE_VALUE;
    }

    // get the first process and store it into `process_info`.
    if (!Process32First(process_list, &process_info)) {
        puts("Error: couldn't get handle to first process.");
        return INVALID_HANDLE_VALUE;
    }

    do {
        // check to see if process name is the same as `ident`.
        if (strcmp(ident, process_info.szExeFile) == 0) {
            // Open a handle to the target process.
            return OpenProcess(perms, FALSE, process_info.th32ProcessID);
        }
        // iterate through the entire process list.
    } while (Process32Next(process_list, &process_info));

    // we went through the entire process list and couldn't find the target exe name.
    return INVALID_HANDLE_VALUE;
}

#endif //TINYMAPPER_PROCESS_H