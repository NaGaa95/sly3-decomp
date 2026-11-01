// Build the description text of the current menu entry: the pending message, else the entry title with its unlock requirement and the affordable/unaffordable hint (fallback text when the entry is invalid or not unlockable).
// SLY3_CFLAGS: -Os -G0
struct Row {
    unsigned char opaque00[8];
    int cost;
    unsigned char opaque0C[0x1C - 0xC];
    int title;
    int unlock;
    unsigned char opaque24[0x3C - 0x24];
};
struct Menu {
    unsigned char opaque000[0x40];
    int message;
    unsigned char opaque44[4];
    int messageId;
    unsigned char opaque4C[4];
    int blocked;
    unsigned char opaque54[0x27C - 0x54];
    unsigned int selection;
};
extern struct Menu D_0046F810;
extern struct Row D_00343098[];
extern unsigned char D_00475480[];
extern unsigned char D_0036C700[];
extern const char D_003260B0[], D_003260B8[];
unsigned short *func_00150630(void *game, int name);
void func_00271730(unsigned short *text, unsigned short *string);
void func_00271780(unsigned short *text, unsigned short *string);
unsigned short *func_00271828(unsigned short *text, const char *literal);
int func_001852E0(void *context);


void func_00220C68(unsigned short *text)
{
    if (D_0046F810.message != -1) {
        func_00271730(text, func_00150630(D_00475480, D_0046F810.messageId));
    } else if (D_0046F810.blocked == 0) {
        unsigned int selection = D_0046F810.selection;
        if (selection < 0x43) {
            unsigned int off = selection * sizeof(struct Row);
            struct Row *table = D_00343098;
            int *unlock0 = &table->unlock;
            int *unlock = (int *)((char *)unlock0 + off);
            if (*unlock != -1) {
                int *cost0 = &table->cost;
                int *cost = (int *)((char *)cost0 + off);
                int id = func_001852E0(D_0036C700) < *cost ? 0x12E : 0x12F;
                func_00271730(text, func_00150630(D_00475480, D_00343098[selection].title));
                func_00271828(text, D_003260B0);
                func_00271780(text, func_00150630(D_00475480, *unlock));
                func_00271828(text, D_003260B8);
                func_00271780(text, func_00150630(D_00475480, id));
                return;
            }
        }
        func_00271730(text, func_00150630(D_00475480, 0x131));
    }
}
