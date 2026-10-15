// SLY3_CFLAGS: -Os -G0
struct SaveBlockContext {
    unsigned char opaque00[8];
    int mode;
    unsigned char opaque0C[0x13954 - 0xC];
    void *selectedBlock;
};
struct M;
struct SAVE;
struct Q;
struct B { int c; unsigned char *pb; };
extern struct B D_004793C8;
void func_001CFB40(struct M *save, struct SAVE *block, char *path);
int func_001D09C8(void *save, void *path, void *block, int bytes);
void func_001CF578(void *save);
void func_0021C0F0(struct B *records, struct Q *block);
void func_0021D010(void *block, int retainValues);

int func_001D0410(void *save, void *block)
{
    struct SaveBlockContext *context = save;
    char path[0x50];
    if (context->mode == 6)
        context->selectedBlock = block;
    func_001CFB40(save, block, path);
    return func_001D09C8(save, path, block, 0x6808);
}

int func_001D0478(void *save, void *block)
{
    struct SaveBlockContext *context = save;
    char path[0x50];
    if (D_004793C8.c)
        func_0021C0F0(&D_004793C8, block);
    func_0021D010(block, 0);
    if (block == context->selectedBlock)
        func_001CF578(save);
    func_001CFB40(save, block, path);
    return func_001D09C8(save, path, block, 0x6808);
}
