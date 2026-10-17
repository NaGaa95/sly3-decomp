// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct Object { unsigned char prefix[0xD0]; Object *next; };
struct Holder {
    unsigned char prefix[0x3EB8];
    int count;
    void *sprites[1];
};
struct HolderView { unsigned char prefix[0x3EF0]; Object *head; };
extern "C" {
extern float D_0036BBA8;
void func_0027DD40(void *holder);
void func_002740B8(void *object);
void func_002BFD80(void *scope, int flags);
void func_001662C0(void *sprite);
}
struct UpdateScope {
    ~UpdateScope() { func_002BFD80(this, 2); }
};
extern "C" void func_0027DE38(Holder *holder)
{
    func_0027DD40(holder);
    if (D_0036BBA8 <= 0.0f)
        return;
    {
        UpdateScope scope;
        for (Object *object = ((HolderView *)holder)->head; object; object = object->next)
            func_002740B8(object);
    }
    for (int i = 0; i < holder->count; i++)
        func_001662C0(holder->sprites[i]);
}
