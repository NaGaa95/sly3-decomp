// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct TFT {int fLeft,fPlus,fSpace,fPrefix,fZero,fPrec0,width,precision,cbits;char pad24[8];unsigned char conversion;char pad2d[3];int fUpper;};
extern "C" {
char *func_00271628(char *,const char *);
unsigned int strlen(const char *);
int func_002705C8(double);
unsigned char func_00270658(double,int,int);
double func_002A38B8(double,double);
int func_00270738(char *buffer,int capacity,struct TFT *f,double value);
extern char D_00328E90[],D_00328E98[];
extern char D_00349D70[];
}
int func_00270738(char *buffer,int capacity,TFT *f,double value){
    union {double d;unsigned long u;} bits;
    bits.d=value;
    if((bits.u&0x7FF0000000000000UL)==0x7FF0000000000000UL){
        func_00271628(buffer,(bits.u&0xFFFFFFFFFFFFFUL)?D_00328E90:D_00328E98);
        return strlen(buffer);
    }
    int exponent=func_002705C8(value);
    char *p=buffer;
    int scientific=f->conversion=='e';
    if(f->conversion=='g'){
        if(exponent<-4 || exponent>=f->precision){scientific=1;f->precision--;}
    }
    int roundExponent=scientific?exponent:0;
    double rounded=value+0.5*func_002A38B8(10.0,(double)(roundExponent-f->precision));
    int roundedExponent=func_002705C8(rounded);
    if(exponent<func_002705C8(rounded))exponent=roundedExponent;
    int digit,count;
    if(scientific){count=1;digit=exponent;}
    else if(exponent>=0){count=exponent+1;digit=exponent;}
    else {count=1;digit=0;}
    while(count-- >0)*p++=func_00270658(rounded,exponent,digit--);
    if(!f->fPrec0){
        *p++='.';
        count=f->precision;
        while(count-- >0)*p++=func_00270658(rounded,exponent,digit--);
        if(f->conversion=='g'){
            while(p>buffer && ((unsigned char *)p)[-1]=='0')--p;
            if(p>buffer && ((unsigned char *)p)[-1]=='.')--p;
        }
    }
    if(scientific){
        *p++='e';
        if(exponent<0){*p++='-';exponent=-exponent;}
        else *p++='+';
        int divisor=(int)func_002A38B8(10.0,2.0);
        for(int i=2;i>=0;--i){
            *p++=D_00349D70[exponent/divisor];
            exponent=(exponent%divisor)*10;
        }
    }
    return p-buffer;
}
