// Original USA entry 0x186e28; ordinary C reconstruction.
// Actual UTF16 destination A0 is retained across lookup. Global475480.object4044 supplies signed ID C8; null object or ID-1 leaves the destination unchanged.150630 receives explicit global A0/ID A1 and returns the actual UTF16 pointer;271730 receives explicit destination/source. No original FPR input is read.
// SLY3_CFLAGS: -Os -G0
struct Object  {
    char pad[0xC8];
    int id;
};
struct Global  {
    char pad[0x4044];
    struct Object *object;
};
extern struct Global D_00475480;
const unsigned short *func_00150630(void *,int);
void func_00271730(unsigned short *,const unsigned short *);
void func_00186E28(unsigned short *text)  {
    if(D_00475480.object && D_00475480.object->id!=-1)func_00271730(text,func_00150630(&D_00475480,D_00475480.object->id));
}
