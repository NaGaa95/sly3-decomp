// SLY3_CFLAGS: -Os -G0
// Combine the base gate flags of an actor with the two linked targets: each linked target that contains the given object
// raises the result to at least 3. Second function: mode 0..2 predicate on the same object.
struct Link { unsigned char pad00[0x14]; void **target; };
struct Self {
    unsigned char pad00[0x1470]; int mode;
    unsigned char pad1474[0x15E0 - 0x1474]; struct Link *first;
    unsigned char pad15E4[0x15F0 - 0x15E4]; struct Link *second;
};
int func_00156948(void *self);
int func_001C8F20(void *object, void *ancestor);
int func_0013CD00(int first, int second);
int func_0022D130(struct Self *self, void *object)
{
    int result = func_00156948(self);
    if (self->first) {
        if (func_001C8F20(object, *self->first->target))
            result = func_0013CD00(result, 3);
    }
    if (self->second) {
        if (func_001C8F20(object, *self->second->target))
            result = func_0013CD00(result, 3);
    }
    return result;
}
int func_0022D1D0(struct Self *self)
{
    int mode = self->mode;
    if (mode < 3) {
        if (mode >= 0)
            return 1;
    }
    return 0;
}
