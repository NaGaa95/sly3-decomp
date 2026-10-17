// SLY3_CFLAGS: -Os -G0
struct StepEntry { short delta; short pad; void (*method)(void *); };
struct StepChild { unsigned char prefix[0xC]; struct StepEntry *table; };
struct StepInput { float x; float y; };
struct StepOwner {
    unsigned char prefix[0x134]; struct StepInput *input;
    unsigned char gap138[0x2A0-0x138]; int count;
    struct StepChild *children[(0xE44-0x2A4)/4]; int mode;
    unsigned char gapE48[0x10A0-0xE48]; unsigned char block[0x6C];
    float value; unsigned char gap1110[0x115C-0x1110]; void *pending;
    unsigned char gap1160[0x140C-0x1160]; unsigned char aux[1];
};
char *func_001F4A80(void *self);
void func_001A9998(void *value);
void func_00156FD0(void *value);
int func_00157398(void *value);
void func_0022A7F8(void *value);
float func_00168108(void *controller,float x,float y,float value);
void func_00152978(struct StepOwner *self)
{
    if(self->mode==-1) {
        func_001A9998(self->aux);
        func_00156FD0(self->block);
        if(!func_00157398(self->block)) {
            if(self->count>0) {
                int last=self->count-1;
                struct StepChild *child=self->children[last];
                child->table[11].method((char *)child+child->table[11].delta);
                return;
            }
            if(self->pending) {
                func_0022A7F8(self->pending);
                return;
            }
        }
    }
    self->value=func_00168108(func_001F4A80(self),self->input->x,self->input->y,self->value);
}
