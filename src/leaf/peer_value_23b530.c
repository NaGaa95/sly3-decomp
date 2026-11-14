// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Store a value at +0x114 and mirror it into the peer (+0x10C) when that peer points back at this object.
// (Split from func_0023B3A8's row.)
struct Obj;
struct Peer { struct Obj *peer; char pad4[0x1C]; float value; };
struct Obj { char pad[0x10C]; struct Peer *peer; char pad110[4]; float value; };
void func_0023B530(struct Obj *self, float value)
{
    struct Peer *peer = self->peer;
    self->value = value;
    if (peer && peer->peer == self)
        peer->value = value;
}
