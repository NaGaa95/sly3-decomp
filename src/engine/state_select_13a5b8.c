// SLY3_CFLAGS: -Os -G0
struct StateEntry { short delta; short pad; int (*method)(void *); };
struct StateHolder { unsigned char prefix[0xC]; struct StateEntry *table; };
struct StateSelf { struct StateHolder *holder; int mode; unsigned char gap8[4]; void *effect; };
int func_001398C8(void *effect);
int func_001398F0(void *effect);
void func_0013ABC8(void *self, int state);
void func_0013A5B8(struct StateSelf *self)
{
    if(self->effect) {
        if((unsigned int)(self->mode + 1) < 3) {
            if(!func_001398C8(self->effect) || (func_001398F0(self->effect)
               && self->holder->table[100].method((char *)self->holder + self->holder->table[100].delta)
               && self->holder->table[100].method((char *)self->holder + self->holder->table[100].delta) != 9)) {
                func_0013ABC8(self, 1);
            } else {
                func_0013ABC8(self, 0);
            }
        }
    }
}
