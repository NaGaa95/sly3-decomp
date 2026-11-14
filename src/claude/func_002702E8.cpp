// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// WriteTftUl(TFT*, OSTRM*, ulong): unsigned printf conversion
struct TFT {int fLeft,fPlus,fSpace,fPrefix,fZero,fPrec0,width,precision,cbits;int matrixRows,vectorColumns;unsigned char conversion;int fUpper;};
union UL {unsigned short us;short s;unsigned int u;int i;unsigned long ul;long l;};
class OSTRM {public:char *buffer;int capacity,used;char unknownC[4];int written,buffered;int CbWrite(void *,int) __asm__("func_0025A2D0");};
extern "C" int func_002700D0(TFT *,UL *);
extern "C" int func_00270208(char *,int,unsigned long,unsigned int);
extern "C" int func_002701B0(unsigned char);
extern "C" unsigned int strlen(const char *);
extern "C" void func_00271978(char *);
extern "C" void func_002702E8(TFT *f,OSTRM *out,unsigned long n);
static inline void WritePad(OSTRM *out,char ch,int count){char b=ch;while(count-- >0)if(out->CbWrite(&b,1)!=1)break;}
void func_002702E8(TFT *f,OSTRM *out,unsigned long n){
    char digits[65];
    char prefix[3];
    int cPrefix,cDigits,cZero;
    if(f->fPrec0 || f->precision)f->fZero=0;
    if(f->fPrec0 && n==0){
        cPrefix=0;
        cZero=0;
        cDigits=0;
    } else {
        int negative=func_002700D0(f,(UL *)&n);
        cZero=f->precision;
        prefix[0]=0;
        switch(f->conversion){
        case 'd':case 'i':
            if(negative)__builtin_memcpy(prefix,"-",2);
            else if(f->fPlus)__builtin_memcpy(prefix,"+",2);
            else if(f->fSpace)__builtin_memcpy(prefix," ",2);
            cZero-=strlen(prefix);
            break;
        case 'b':if(f->fPrefix)__builtin_memcpy(prefix,"0b",3);break;
        case 'o':if(f->fPrefix)__builtin_memcpy(prefix,"0",2);break;
        case 'x':if(f->fPrefix)__builtin_memcpy(prefix,"0x",3);break;
        }
        cPrefix=strlen(prefix);
        cDigits=func_00270208(digits,0x40,n,func_002701B0(f->conversion));
        cZero-=cDigits;
        if(cZero<0)cZero=0;
    }
    digits[cDigits]=0;
    if(f->fUpper){func_00271978(prefix);func_00271978(digits);}
    int total=cPrefix+cZero+cDigits;
    int left=0,right=0;
    if(total<f->width){
        int padding=f->width-total;
        if(f->fLeft)right=padding;
        else if(f->fZero && cDigits)cZero+=padding;
        else left=padding;
    }
    WritePad(out,' ',left);
    out->CbWrite(prefix,cPrefix);
    WritePad(out,'0',cZero);
    out->CbWrite(digits,cDigits);
    WritePad(out,' ',right);
}
