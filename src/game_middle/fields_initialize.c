// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
extern qword D_00322ED0;
struct Triple { float x, y, z; };
struct FieldsOwner {
    int word0;
    int id4;
    unsigned char gap8[0x1C - 8];
    int id1C;
    unsigned char gap20[0xB0 - 0x20];
    qword constant;
    unsigned char gapC0[0x120 - 0xC0];
    struct Triple triple;
    unsigned char gap12C[0x190 - 0x12C];
    int flag;
};
void func_001B7190(struct FieldsOwner *owner, int word)
{
    struct Triple *t = &owner->triple;
    owner->word0 = word;
    owner->id4 = -1;
    owner->id1C = -1;
    owner->constant = D_00322ED0;
    t->x = 1.0f;
    t->y = 1.0f;
    t->z = 0.0f;
    owner->flag = 1;
}
