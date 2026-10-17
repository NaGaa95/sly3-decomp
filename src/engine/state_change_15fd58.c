// SLY3_CFLAGS: -Os -G0
struct StateEntry { short delta; short pad; void (*method)(void *); };
struct StateObject { unsigned char prefix[0xC]; struct StateEntry *table; };
struct StateOwner { unsigned char prefix[0x17E4]; struct StateObject *primary; void *secondary; };
struct StateSelf {
    unsigned char prefix[0x10]; struct StateOwner *owner;
    unsigned char gap14[0x40 - 0x14]; int state; float stamp;
    unsigned char gap48[0x70 - 0x48]; int word70;
};
extern float D_0036BB98;
char *func_001F4A80(void *owner);
void func_00273ED0(void *object, void *controller, void *owner, int flag);
void func_00273E48(void *object, void *controller, void *owner, int flag);
void func_00262770(void *object, void *controller);
void func_00262B60(void *object, int identifier, void *output);
void func_0015FD58(struct StateSelf *self, int state)
{
    if(state == self->state) return;
    if(self->state == 1) {
        char *controller = func_001F4A80(self->owner);
        if(self->owner->secondary) func_00273ED0(self->owner->secondary, controller, self->owner, 1);
        if(self->owner->primary) {
            self->owner->primary->table[54].method((char *)self->owner->primary + self->owner->primary->table[54].delta);
            self->word70 = -1;
        }
        self->state = state;
    } else {
        self->state = state;
    }
    self->stamp = D_0036BB98;
    if(state == 1) {
        char *controller = func_001F4A80(self->owner);
        if(self->owner->secondary) func_00273E48(self->owner->secondary, controller, self->owner, 1);
        if(self->owner->primary) {
            func_00262770(self->owner->primary, controller);
            self->owner->primary->table[56].method((char *)self->owner->primary + self->owner->primary->table[56].delta);
            func_00262B60(self->owner->primary, 0x3BE, &self->word70);
        }
    }
}
