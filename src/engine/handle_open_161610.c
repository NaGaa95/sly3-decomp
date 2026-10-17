// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct CreateEntry { short delta, padding; char *(*fn)(void *); };
struct CreateTarget { unsigned char prefix[0xC]; struct CreateEntry *table; };
struct CreateObject { unsigned char prefix[0x1E8]; void *owner; };
struct CreateOwner { unsigned char prefix[0x17EC]; void *h17EC; void *h17F0; void *h17F4; unsigned char gap17F8[0x1884-0x17F8]; struct CreateTarget *target; unsigned char gap1888[0x188C-0x1888]; int mode; };
struct CreateSelf { unsigned char prefix[0x10]; struct CreateOwner *owner; unsigned char gap14[0x38-0x14]; int state; };
struct CreateObject *func_001FBE30(void *handle, int flag);
Qword func_001619F8(void *self, void *object);
void func_00212D50(void *object, void *target, Qword value);

void func_00161610(struct CreateSelf *self)
{
    void *handle;
    struct CreateObject *object;
    switch(self->state) {
    case 0: handle = self->owner->h17EC; break;
    case 3: handle = self->owner->h17F0; break;
    case 4: handle = self->owner->h17F4; break;
    default: handle = 0; break;
    }
    if(handle) {
        object = func_001FBE30(handle, 0);
        if(object) {
            object->owner = self->owner;
            if(self->state == 4 && self->owner->mode == 2) {
                struct CreateTarget *target = self->owner->target;
                func_00212D50(object, target, *(Qword *)(target->table[36].fn((char *)target + target->table[36].delta) + 0x30));
            } else {
                func_00212D50(object, 0, func_001619F8(self, object));
            }
        }
    }
}
