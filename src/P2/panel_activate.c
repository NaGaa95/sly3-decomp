// SLY3_CFLAGS: -Os -G0
struct Method { short delta,unused; void (*method)(void); };
struct LinkedPanel { unsigned char prefix[0xC]; struct Method *methods; };
struct Panel { unsigned char prefix[0x34]; struct LinkedPanel *linked; };
static inline void CallPanel(struct LinkedPanel *linked,int slot)
{
    ((void (*)(void *))linked->methods[slot].method)((char *)linked+linked->methods[slot].delta);
}
static inline void CallPanelInt(struct LinkedPanel *linked,int slot,int value)
{
    ((void (*)(void *,int))linked->methods[slot].method)((char *)linked+linked->methods[slot].delta,value);
}
extern char D_0036BB98[],D_00475480[];
extern int D_0046FD30;
void func_0021DDC0(void *panel,int selection);
void func_00165548(void *clock,int channel,float scale);
void func_001A93C8(void *game,int index,unsigned int mode);
void func_00222D38(struct Panel *panel,int selection)
{
    func_0021DDC0(panel,selection);
    func_00165548(D_0036BB98,9,0.0f);
    func_001A93C8(D_00475480,-1,0);
    if(!D_0046FD30)
        CallPanelInt(panel->linked,53,0x377);
    else
        CallPanel(panel->linked,56);
}
