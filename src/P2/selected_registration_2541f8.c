// SLY3_CFLAGS: -Os -G0
struct SelectedRegistrationOwner {
    unsigned char prefix[0x3AC];
    void *selected;
    unsigned char gap3B0[0x28];
    void *registration;
};
void func_00256470(void *registration, void *owner);
void *func_00241AD8(void *selected);
void func_00256410(void *registration, void *owner);
void func_002541F8(void *receiver, void *selected)
{
    struct SelectedRegistrationOwner *owner = receiver;
    if (selected != owner->selected) {
        if (owner->selected) {
            func_00256470(owner->registration, owner);
            owner->registration = 0;
        }
        owner->selected = selected;
        if (selected) {
            owner->registration = func_00241AD8(selected);
            func_00256410(owner->registration, owner);
        }
    }
}
