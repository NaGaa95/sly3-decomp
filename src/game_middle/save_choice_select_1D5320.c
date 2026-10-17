// SLY3_CFLAGS: -Os -G0
extern unsigned char D_00375290[];
extern char D_00345AB0[], D_00345CA0[];
struct SaveSelectView {
    unsigned char opaque00[0x13950];
    void *selectedBlock;
};
struct SaveChoice {
    int id;
    int word4;
    int count;
    char *entries;
};
int func_001CFDF8(void *save);
void func_001D5320(struct SaveChoice *choice)
{
    if (((struct SaveSelectView *)D_00375290)->selectedBlock && !func_001CFDF8(D_00375290)) {
        choice->id = 0x57;
        choice->count = 2;
        choice->entries = D_00345AB0;
    } else {
        choice->id = 0x56;
        choice->count = 2;
        choice->entries = D_00345CA0;
    }
}
