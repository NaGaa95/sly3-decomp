// SLY3_CFLAGS: -Os -G0
int func_00169E88(void *self);
void func_0011B028(void *list,void *receiver);
struct SwapEntry { short delta,padding; void (*fn)(void *); };
struct SwapTable { unsigned char prefix[0x1C]; struct SwapEntry *table; };
struct SwapRoot { unsigned char prefix[0x300]; struct SwapTable *current; };
struct SwapSelf { struct SwapRoot *root; unsigned char gap4[0x1C-4]; struct SwapEntry *table; };
void func_00169D98(struct SwapSelf *self)
{
    if(!func_00169E88(self)) {
        struct SwapTable *old=self->root->current;
        struct SwapTable *current;
        func_0011B028((char *)self->root+0x300,self);
        current=self->root->current;
        if(current!=old) {
            self->table[2].fn((char *)self+self->table[2].delta);
            if(current) current->table[1].fn((char *)current+current->table[1].delta);
        }
    }
}
