// SLY3_CFLAGS: -Os -G0
struct Obj { unsigned char prefix[0x190]; int slot; };
struct Grid { unsigned char prefix[0x88]; int cell[0x28][0x20]; };
int func_0025E150(void);
void func_001857E8(struct Grid *grid,struct Obj *obj,int value)
{
    int slot;
    int selector=func_0025E150();
    if(selector==-1) return;
    slot=obj->slot;
    if(selector>=0 && selector<0x28) {
        if(slot>=0) {
            if(slot<0x20) grid->cell[selector][slot]=value;
        }
    }
}
