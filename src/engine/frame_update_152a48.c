// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct UpdateEntry { short delta; short pad; void (*method)(void *); };
struct UpdateSelf {
    unsigned char prefix[0xC]; struct UpdateEntry *table;
    unsigned char gap10[0x134-0x10]; void *input;
    unsigned char gap138[0x29C-0x138]; unsigned char list[0x2E4-0x29C]; int word2E4;
    unsigned char gap2E8[0xE40-0x2E8]; unsigned char block[0xF50-0xE40]; void *animation;
    unsigned char gapF54[0x10A0-0xF54]; unsigned char gate[0x1120-0x10A0]; Qword position;
};
extern unsigned char D_00475480[];
extern Qword D_00317560;
extern float D_0036BB9C;
extern unsigned char D_00320548[];
void func_0024E1A0(void *self);
void func_001B61A0(void *game,void *self);
void func_00152978(void *self);
void func_001540E8(void *self);
int func_001A7A80(void *input,int button,float seconds);
void func_001528E0(void *self);
void func_00152B58(void *self);
void func_001C40E0(void *self);
void func_00152E88(void *self);
void func_001555C0(void *self);
int func_00138AC8(void *animation);
void func_00137688(void *animation);
int func_00157398(void *gate);
void func_002385A8(void *list);
Qword func_00120C80(Qword current,Qword target,void *parameters,int mode,float step);
void func_001C2CC0(void *block);
void func_00152A48(struct UpdateSelf *self)
{
    func_0024E1A0(self);
    func_001B61A0(D_00475480,self);
    func_00152978(self);
    func_001540E8(self);
    if(func_001A7A80(self->input,0x200,0.0f)) func_001528E0(self);
    func_00152B58(self);
    func_001C40E0(self);
    func_00152E88(self);
    func_001555C0(self);
    if(self->animation) {
        if(func_00138AC8(self->animation)) func_00137688(&self->animation);
    }
    if(!func_00157398(self->gate)) func_002385A8(self->list);
    if(self->word2E4) self->position=func_00120C80(self->position,D_00317560,D_00320548,0,D_0036BB9C);
    self->table[98].method((char *)self+self->table[98].delta);
    func_001C2CC0(self->block);
}
