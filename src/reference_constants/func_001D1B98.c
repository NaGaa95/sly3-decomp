// Original USA entry 0x1d1b98; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
extern char D_0046F550[],D_00475480[];
int func_001D45B0(void *);
const unsigned short *func_00150630(void *,int);
unsigned short *func_00271730(unsigned short *,const unsigned short *);
void func_001D1B98(unsigned short *destination)  {
    func_00271730(destination,func_00150630(D_00475480,func_001D45B0(D_0046F550)));
}
