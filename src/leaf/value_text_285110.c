// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Slot { unsigned char prefix[0x50]; int disabled; unsigned char gap54[0x4C]; float scale; };
struct Tracker { unsigned char prefix[0x14]; struct Slot *slot; unsigned char gap18[4]; float value; };
extern struct Tracker D_004BC230;
int func_002852B0(struct Tracker *tracker);
void func_00283620(struct Slot *slot,char *text,float value);
unsigned short *func_00271828(unsigned short *destination,const char *text);
void func_00285110(unsigned short *destination)
{
    char text[0x20];
    if(func_002852B0(&D_004BC230)) {
        struct Slot *slot=D_004BC230.slot;
        if(!slot->disabled&&slot->scale!=0.0f) {
            func_00283620(slot,text,D_004BC230.value);
            func_00271828(destination,text);
        }
    }
}
