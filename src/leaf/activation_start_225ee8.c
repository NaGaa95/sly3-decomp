// Start the activation: select the source, run the activation event, then claim the storage word unless the children are already finished.
// SLY3_CFLAGS: -Os -G0
struct ActivationList { void *head, *tail; int linkOffset; };
struct ActivationEntry { short delta, reserved; void (*call)(void *, int, void *, int, void *, void *); };
struct ActivationObject {
    char prefix[0xC]; struct ActivationEntry *table;
    char pad10[0x3C - 0x10]; int storage;
    char pad40[4]; void *source; struct ActivationList children;
    char pad54[4]; void *selected; float elapsed; unsigned long flags;
};
void *func_0022BF40(struct ActivationObject *object, void *source, int mode);
void func_002265E0(void *node);
int func_0011B0F0(struct ActivationList *list);
void func_00226050(struct ActivationObject *object);
void func_001C9118(struct ActivationObject *object, int mode);

void func_00225EE8(struct ActivationObject *object, void *selected)
{
    if (!(object->flags & 1L)) {
        object->selected = selected;
        object->flags |= 1L;
        object->flags &= ~2L;
        object->table[3].call((char *)object + object->table[3].delta, 5, 0, 0, 0, 0);
        if (!(object->flags & 1L)) return;
        func_002265E0(func_0022BF40(object, object->source, 0));
        if (!(object->flags & 1L)) return;
        if (func_0011B0F0(&object->children)) {
            func_00226050(object);
            return;
        }
        {
            unsigned int word = object->storage;
            if ((word ^ 1) & 1) word = *(unsigned int *)word;
            if (word & 2) return;
        }
        func_001C9118(object, 1);
        if ((object->storage ^ 1) & 1) *(int *)object->storage |= 2;
        else object->storage |= 2;
        object->flags |= 2L;
    }
}
