// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Slot { unsigned char prefix[0x9C]; float secondary; float primary; };
struct Tracker { unsigned char prefix[0x14]; struct Slot *slot; unsigned char gap18[0x7CBC]; int state; };
extern struct Tracker D_004BC230;
extern char D_00475480[];
const unsigned short *func_00150630(void *game,int id);
unsigned short *func_00271730(unsigned short *destination,const unsigned short *text);
void func_00285220(unsigned short *destination)
{
    int id=-1;
    if(D_004BC230.state==6) {
        struct Slot *slot=D_004BC230.slot;
        if(slot->primary!=0.0f)
            id=0x1ED;
        else if(slot->secondary!=0.0f)
            id=0x1F1;
    }
    if(id!=-1)
        func_00271730(destination,func_00150630(D_00475480,id));
}
