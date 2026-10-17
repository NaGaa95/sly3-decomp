// SLY3_CFLAGS: -Os -G0
typedef struct CRef {
    short tag;
    short padding;
    union { int integer; float real; void *pointer; } payload;
} CRef;
struct KEY;
struct SelectSlot { unsigned char payload[0x6864]; };
struct SelectMenu {
    unsigned char opaque00[8];
    int mode;
    unsigned char opaque0C[0x24 - 0xC];
    struct SelectSlot slots[3];
    struct SelectSlot *selected;
};
struct SelectAction {
    unsigned char opaque00[8];
    int index;
    unsigned char opaque0C[0x1C - 0xC];
    unsigned int flags;
};
extern struct SelectMenu D_00375290;
extern int D_00375228;
extern struct KEY *D_004794EC;
CRef *func_002BC010(CRef *output, struct KEY *key, unsigned char *buffer);
void func_0012BC20(CRef *reference);
void func_0021D010(void *block, int retainValues);
void func_0018AB08(int value);
void *func_002459F8(int identifier);
void func_00244F08(void *object, void *owner);

void func_001D1470(struct SelectAction *action)
{
    if (D_00375290.mode == 6 && D_00375228 == 1) {
        struct SelectSlot *slot = &D_00375290.slots[action->index];
        CRef value;
        float present;
        func_002BC010(&value, D_004794EC, slot->payload);
        present = value.payload.real;
        func_0012BC20(&value);
        if (present == 0.0f) {
            D_00375290.selected = slot;
            func_0021D010(slot, 1);
            func_0018AB08((int)D_00375290.selected);
            return;
        }
        func_00244F08(func_002459F8(0x36), 0);
    }
    if (action)
        action->flags |= 2;
}
