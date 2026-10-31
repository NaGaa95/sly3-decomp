// Fill the text object with the localised string that belongs to the current mode (1-7).
// SLY3_CFLAGS: -Os -G0
extern unsigned char D_00475480[];
extern int D_0046FD30;
char *func_00150630(void *game, int name);
void func_00271730(void *text, char *string);

void func_00223078(void *text)
{
    switch (D_0046FD30) {
    case 1: func_00271730(text, func_00150630(D_00475480, 0x97)); break;
    case 2: func_00271730(text, func_00150630(D_00475480, 0x9A)); break;
    case 3: func_00271730(text, func_00150630(D_00475480, 0x9B)); break;
    case 4: func_00271730(text, func_00150630(D_00475480, 0xA0)); break;
    case 5: func_00271730(text, func_00150630(D_00475480, 0xA1)); break;
    case 6: func_00271730(text, func_00150630(D_00475480, 0x9F)); break;
    case 7: func_00271730(text, func_00150630(D_00475480, 0xA2)); break;
    }
}
