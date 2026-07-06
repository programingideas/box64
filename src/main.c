#include "core.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// Declare the flag globally so the rest of Box64's source files can read it
int box64_t6sp_workaround = 0;

int main(int argc, const char **argv, char **env) {

    // Scan arguments to see if a Black Ops 2 executable is trying to boot
    for (int i = 0; i < argc; ++i) {
        if (argv[i]) {
            // Use standard C-compliant length scanning to prevent strdup crashing
            size_t len = strlen(argv[i]);
            char *lower_arg = (char*)malloc(len + 1);
            if (lower_arg) {
                for (size_t j = 0; j < len; j++) {
                    lower_arg[j] = tolower((unsigned char)argv[i][j]);
                }
                lower_arg[len] = '\0';

                // Check cleanly across all Black Ops 2 core executables
                if (strstr(lower_arg, "t6sp.exe") || strstr(lower_arg, "t6zm.exe") || strstr(lower_arg, "t6mp.exe")) {
                    box64_t6sp_workaround = 1;
                    printf("[BOX64] Black Ops 2 workaround ACTIVATED via argv[%d]: %s\n", i, argv[i]);
                    free(lower_arg);
                    break;
                }
                free(lower_arg);
            }
        }
    }

    if (!box64_t6sp_workaround) {
        printf("[BOX64] Workaround inactive for this process instance (argv[1] = %s)\n", argc > 1 ? argv[1] : "none");
    }

    x64emu_t* emu = NULL;
    elfheader_t* elf_header = NULL;
    if (initialize(argc, argv, env, &emu, &elf_header, 1)) {
        return -1;
    }

    return emulate(emu, elf_header);
}
