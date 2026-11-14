// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Id of the linked object at +0x16C, or -1 without one. (Split from func_0022F998's row.)
struct Link { char pad[0x4C]; int id; };
struct Obj { char pad[0x16C]; struct Link *link; };
int func_0022FC08(struct Obj *self)
{
    int id = -1;
    if (self->link)
        id = self->link->id;
    return id;
}
