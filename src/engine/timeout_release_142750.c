// SLY3_CFLAGS: -Os -G0
struct TimeoutEntry { short delta; short pad; void (*method)(void *); };
struct TimeoutHolder { unsigned char prefix[0xC]; struct TimeoutEntry *table; };
struct TimeoutObject {
    unsigned char prefix[0x28]; unsigned long flags;
    unsigned char gap30[0x134 - 0x30]; int word134;
    unsigned char gap138[0x2B0 - 0x138]; int word2B0;
};
struct TimeoutSelf {
    unsigned char prefix[0x4BC]; struct TimeoutObject *object;
    float objectStamp; struct TimeoutHolder *holder;
    unsigned char gap4C8[0x4E0 - 0x4C8]; struct TimeoutHolder *second; float secondStamp;
};
extern float D_0036BB98;
extern float D_00320070;
void func_00142750(struct TimeoutSelf *self)
{
    struct TimeoutObject *object = self->object;
    if(object) {
        if(!(object->flags & (1UL << 56))) goto clear;
        if(!object->word134) goto clear;
        if(object->word2B0 != 1) goto clear;
        if(!(D_0036BB98 - self->objectStamp > 6.0f)) goto second;
    clear:
        {
            struct TimeoutHolder *holder = self->holder;
            self->object = 0;
            if(holder) holder->table[9].method((char *)holder + holder->table[9].delta);
        }
    }
second:
    if(self->second) {
        if(D_0036BB98 - self->secondStamp > 1.5f) {
            self->second->table[9].method((char *)self->second + self->second->table[9].delta);
            self->secondStamp = D_00320070;
        }
    }
}
