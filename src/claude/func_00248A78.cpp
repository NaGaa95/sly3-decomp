// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-strength-reduce
class X;
typedef void (X::*PMF)();
struct P {char pad0[0x140];float weights[8][4];char pad1C0[4];float outputs[4];char pad1D4[0x3C];X *object;int count;X *refs[8];X *component;};
struct LM {float low,high;};
extern "C" LM D_00341FF0;
extern "C" PMF D_00326EB8,D_00326EC0;
extern "C" float func_0011EE68(LM *,float);
extern "C" void *memset(void *,int,unsigned int);
extern "C" void func_00290E98(int,int);
static inline X *Receiver(X **pp) { return *(X *volatile *)pp; }
// func_00248A78: set one category volume of a sound channel and push the product to the IOP (cf. Sly 2 SetSoundChannelVolume).
extern "C" void func_00248A78(P *p,int channel,int category,float input)
{
    if((unsigned int)category>=8)return;
    if(channel<0)return;
    if(channel>=4)return;
    input=func_0011EE68(&D_00341FF0,input);
    if(p->weights[category][channel]==input)return;
    float (*w)[4]=p->weights;
    if(category==2){
        PMF action;
        memset(&action,0,8);
        if(input==0.0f)action=D_00326EB8;
        else if(w[2][channel]==0.0f)action=D_00326EC0;
        if(action!=0){
            switch(channel){
            case 0:if(p->component)(p->component->*action)();break;
            case 1:for(int i=0;i<p->count;i++){int t=i*4+(int)p;void *x;__asm__("":"=r"(x):"0"(t));__asm__("": :"r"(t));if(Receiver(&((P *)x)->refs[0])){x=((P *)x)->refs[0];(((X *)x)->*action)();}}break;
            case 2:if(p->object)(p->object->*action)();break;
            }
        }
    }
    p->weights[category][channel]=input;
    input=1.0f;
    for(int i=0;i<8;i++)input*=p->weights[i][channel];
    int next=(int)(input*1024.0f);
    if((int)(p->outputs[channel]*1024.0f)!=next){
        p->outputs[channel]=input;
        func_00290E98(channel,next);
    }
}

