// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
extern char D_004BC230[];
struct StoreView { unsigned char prefix[0xAC]; float *target; };
struct StoreGame { unsigned char prefix[0x4044]; struct StoreView *view; };
struct StoreOwner { unsigned char prefix[0x14]; void *source; };
int func_002852B0(void *context);
float func_0011EE68(void *source,float value);
void func_00171DD8(struct StoreOwner *owner,float value)
{
    if(func_002852B0(D_004BC230)) return;
    if(((struct StoreGame *)D_00475480)->view)
        *((struct StoreGame *)D_00475480)->view->target=func_0011EE68(owner->source,value);
}
