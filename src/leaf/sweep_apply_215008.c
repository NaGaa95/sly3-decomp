// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Request { unsigned char prefix0[4]; void *owner; unsigned char gap8[0x18 - 8]; unsigned long flags; };
struct Sweeper {
    unsigned char prefix0[0x544];
    void *primary;
    unsigned char gap548[0x550 - 0x548];
    int hit;
    unsigned char gap554[0x560 - 0x554];
    void *secondary;
};
extern char D_00475480[];
void func_0023EDD0(struct Sweeper *self, struct Request *request, int a, int b, int c, int *out);
int func_0013B500(void *owner, int kind);
void func_001CD858(void *world, struct Request *request, void *target, int a, int b, int *result);
void func_001CC790(void *world, void *target, struct Request *request, int a, int b, int c, int *result);
void func_001CBAA0(void *world, int result);
void func_00215008(struct Sweeper *self, struct Request *request, int a, int b, int c, int *out)
{
    int result;
    func_0023EDD0(self, request, a, b, c, out);
    if (func_0013B500(request->owner, 0x62)) {
        void *target = self->primary;
        if (target) {
            result = 0;
            if (request->flags & 0x20000)
                func_001CD858(D_00475480, request, target, 0, 0, &result);
            else
                func_001CC790(D_00475480, target, request, a, b, c, &result);
            if (result) {
                func_001CBAA0(D_00475480, result);
                self->hit = 1;
            }
        }
    } else {
        void *target = self->secondary;
        if (target) {
            if (request->flags & 0x20000)
                func_001CD858(D_00475480, request, target, 0, 0, out);
            else
                func_001CC790(D_00475480, target, request, a, b, c, out);
        }
    }
}
struct ValueHolder { unsigned char prefix0[0x1DC]; int value; };
int func_00215158(struct ValueHolder *self)
{
    return self->value;
}
