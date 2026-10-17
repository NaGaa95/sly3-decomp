// SLY3_CFLAGS: -Os -G0 -fno-gcse
struct Choice { char unknown_0[0x40]; int title; char unknown_44[0xC]; int state; };
struct Option { char unknown_0[0x60]; int title; };
extern struct Option *D_0046FBC0;
extern struct Choice *D_004BC244;
extern char D_00475480[];
const unsigned short *func_00150630(void *,int);
unsigned short *func_00271730(unsigned short *,const unsigned short *);
static inline int StateOf(struct Choice *choice){ return choice ? choice->state : -1; }
void func_00222588(unsigned short *output)
{
    if(D_0046FBC0) {
        func_00271730(output,func_00150630(D_00475480,D_0046FBC0->title));
        return;
    }
    if(StateOf(D_004BC244)==0 || StateOf(D_004BC244)==2)
        func_00271730(output,func_00150630(D_00475480,D_004BC244->title));
}
