// SLY3_CFLAGS: -Os -G0
struct Obj { unsigned char prefix[0x190]; int slot; };
struct Grid { unsigned char prefix[0x88]; int cell[0x28][0x20]; };
int func_0025E150(void);
int func_00185770(struct Grid *grid,struct Obj *obj)
{
    int slot;
    int selector=func_0025E150();
    if(selector==-1) return 0;
    slot=obj->slot;
    if(selector>=0 && selector<0x28) {
        if(slot>=0) {
            if(slot<0x20) goto compute;
        }
    }
    return -1;
compute:
    return grid->cell[selector][slot];
}
