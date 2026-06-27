#include "core.h"
#include <string.h>
#include <stdlib.h>

// Stark Mode Global Flag for Black Ops 2
int box64_t6sp_workaround = 0;

int main(int argc, const char **argv, char **env) {

    // Scan arguments to see if a Black Ops 2 executable is trying to boot
    for (int i = 0; i < argc; ++i) {
        if (argv[i] && (strstr(argv[i], "t6sp.exe") || strstr(argv[i], "t6zm.exe") || strstr(argv[i], "t6mp.exe"))) {
            box64_t6sp_workaround = 1;
            break;
        }
    }

    x64emu_t* emu = NULL;
    elfheader_t* elf_header = NULL;
    if (initialize(argc, argv, env, &emu, &elf_header, 1)) {
        return -1;
    }

    return emulate(emu, elf_header);
}
