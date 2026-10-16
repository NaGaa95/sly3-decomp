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
int func_0021DD30(void *panel);
void func_0021DE60(void *panel);
void func_00165548(void *clock,int channel,float scale);
void func_001A9420(void *game,int index,unsigned int mode);
void func_00222DC8(struct Panel *panel)
{
    if(func_0021DD30(panel)) {
        func_00165548(D_0036BB98,9,1.0f);
        func_001A9420(D_00475480,-1,0);
        func_0021DE60(panel);
        CallPanel(panel->linked,54);
        panel->linked=0;
    }
}
