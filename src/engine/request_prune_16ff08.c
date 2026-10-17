// SLY3_CFLAGS: -Os -G0
struct PruneRequest { void *object; int rest[4]; };
struct PruneOwner { unsigned char prefix[0xD8]; int count; struct PruneRequest requests[32]; int itemCount; int items[8]; };
int func_00170C28(void *owner, void *value);
int func_0013B500(void *object, int kind);
void func_001702A0(void *owner, void *entry);
void *func_00291F38(void *destination, void *source, int bytes);
void func_0016FF08(struct PruneOwner *owner, int kind)
{
    int i, j;
    for(i = owner->count - 1; i >= 0; i--) {
        void *object = owner->requests[i].object;
        if(!func_00170C28(owner, object) && func_0013B500(object, kind)) func_001702A0(owner, object);
    }
    for(j = 0; j < owner->itemCount; j++) {
        int *slot = &owner->items[j];
        if(*slot == kind) {
            func_00291F38(slot, slot + 1, (owner->itemCount - j) * 4 - 4);
            owner->itemCount--;
            j--;
        }
    }
}
