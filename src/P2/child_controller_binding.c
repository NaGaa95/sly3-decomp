// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ChildBindingOwner;
struct ChildBindingOps {
    char otherEntries[0x1B0];
    short deactivateAdjustment,deactivateReserved;
    void (*deactivate)(int receiver);
    char unusedEntry55[8];
    short activateAdjustment,activateReserved;
    void (*activate)(void *receiver);
};
struct BindingChild {
    char unaccessed[0xC];
    struct ChildBindingOps *operations;
    char unaccessed10[0x13C-0x10];
    struct ChildBindingOwner *owner;
};
struct ChildBindingOwner {
    char unaccessed[0x130];
    int state;
    char unaccessed134[0x168-0x134];
    struct BindingChild *binding;
};

static inline void DeactivateBinding(struct BindingChild *child)
{
    struct ChildBindingOps *operations=child->operations;
    operations->deactivate((int)((char *)child+operations->deactivateAdjustment));
}

void func_001F4D38(struct ChildBindingOwner *owner,struct BindingChild *child)
{
    struct BindingChild *previous=owner->binding;
    if(previous==child)
        return;
    if(previous)
        DeactivateBinding(previous);
    owner->binding=child;
    if(child) {
        child->owner=owner;
        if(owner->state!=-1) {
            struct BindingChild *current=owner->binding;
            struct ChildBindingOps *operations=current->operations;
            operations->activate((char *)current+operations->activateAdjustment);
        } else {
            DeactivateBinding(owner->binding);
        }
    }
}
