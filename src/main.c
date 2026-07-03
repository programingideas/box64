#include "core.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// Stark Mode Global Flag for Black Ops 2
int box64_t6sp_workaround = 0;

int main(int argc, const char **argv, char **env) {

    // Scan arguments to see if a Black Ops 2 executable is trying to boot
    for (int i = 0; i < argc; ++i) {
        if (argv[i]) {
            // Create a lowercase copy of the argument for robust matching
            char *lower_arg = strdup(argv[i]);
            if (lower_arg) {
                for (int j = 0; lower_arg[j]; j++) {
                    lower_arg[j] = tolower((unsigned char)lower_arg[j]);
                }

                if (strstr(lower_arg, "t6sp.exe") || strndup && (strstr(lower_arg, "t6zm.exe") || strstr(lower_arg, "t6mp.exe"))) {
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
