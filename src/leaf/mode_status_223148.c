// SLY3_CFLAGS: -Os -G0
// Compose the status line for the current mode (1-3 pair of labels, 4-7 the shared hint) from two literals and the localised strings.
extern int D_0046FD30;
extern unsigned char D_00475480[];
extern const char D_003261F0[], D_00326188[], D_00326200[], D_00326210[], D_003261B8[];
unsigned short *func_00150630(void *game, int id);
unsigned short *func_002717E0(unsigned short *destination, const char *text);
unsigned short *func_00271780(unsigned short *destination, const unsigned short *source);
unsigned short *func_00271828(unsigned short *destination, const char *text);

void func_00223148(unsigned short *text)
{
    switch (D_0046FD30) {
    case 1:
        func_002717E0(text, D_003261F0);
        func_00271780(text, func_00150630(D_00475480, 0x99));
        func_00271828(text, D_00326188);
        func_00271828(text, D_00326200);
        func_00271780(text, func_00150630(D_00475480, 0x98));
        break;
    case 2:
        func_002717E0(text, D_003261F0);
        func_00271780(text, func_00150630(D_00475480, 0x9C));
        func_00271828(text, D_00326188);
        func_00271828(text, D_00326200);
        func_00271780(text, func_00150630(D_00475480, 0x9D));
        break;
    case 3:
        func_002717E0(text, D_003261F0);
        func_00271780(text, func_00150630(D_00475480, 0x9C));
        func_00271828(text, D_00326188);
        func_00271828(text, D_00326200);
        func_00271780(text, func_00150630(D_00475480, 0x9E));
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        func_002717E0(text, D_00326210);
        func_00271828(text, D_003261B8);
        func_00271780(text, func_00150630(D_00475480, 0x47));
        break;
    }
}
