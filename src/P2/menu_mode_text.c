// SLY3_CFLAGS: -Os -G0
extern int D_0046F850;
extern char D_00475480[];
const unsigned short *func_00150630(void *game,int string_id);
unsigned short *func_00271730(unsigned short *destination,const unsigned short *source);
void func_00220BF0(unsigned short *output)
{
    int text;
    switch(D_0046F850) {
    case -1: text=0x133; break;
    case 0: text=0x134; break;
    case 1: text=0x135; break;
    default: return;
    }
    func_00271730(output,func_00150630(D_00475480,text));
}
