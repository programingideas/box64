#include "core.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, const char **argv, char **env) {

    // --- CUSTOM BLACK OPS 2 BYPASS PATCH START ---
    if (argc > 1 && argv[1] != NULL && (strstr(argv[1], "t6sp.exe") || strstr(argv[1], "t6mp.exe") || strstr(argv[1], "t6zm.exe"))) {
        setenv("BOX64_DYNAREC_FASTROUND", "1", 1);
        setenv("BOX64_DYNAREC_WEAKBARRIER", "0", 1);
    }
    // --- CUSTOM BLACK OPS 2 BYPASS PATCH END ---

    x64emu_t* emu = NULL;
    elfheader_t* elf_header = NULL;
    if (initialize(argc, argv, env, &emu, &elf_header, 1)) {
        return -1;
    }

    return emulate(emu, elf_header);
}
