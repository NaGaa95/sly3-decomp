// Recovered indexed labels, virtual option text, selection and actor amount callbacks.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "game_text.h"
extern "C" unsigned char D_00475480[];
extern "C" void func_00271448(char *,const char *,...);
struct CALLBACK_LABELS { char prefix[0xBC]; int stringIds[1]; };
extern "C" void func_0025F4F8(unsigned short *out,int index,CALLBACK_LABELS *labels) {
    func_00271730(out,func_00150630(D_00475480,labels->stringIds[index]));
}

extern "C" unsigned char D_00475480[];
extern "C" void func_00271448(char *,const char *,...);
struct CALLBACK_VIRTUAL_ENTRY { short delta,pad; const char *(*fn)(void *,int); };
struct CALLBACK_VIRTUAL_TABLE { char prefix[0x1B8]; CALLBACK_VIRTUAL_ENTRY getText; };
struct CALLBACK_OPTIONS { char prefix[12]; CALLBACK_VIRTUAL_TABLE *vtable; };
extern "C" const char D_00327EF8[];
extern "C" void func_0025F540(unsigned short *out,int id,CALLBACK_OPTIONS *options) {
    const char *text=options->vtable->getText.fn((char *)options+options->vtable->getText.delta,id);
    if (!text) func_002717E0(out,D_00327EF8);
    else func_002717E0(out,text);
}
extern "C" unsigned char D_00475480[];
extern "C" void func_00271448(char *,const char *,...);
extern "C" int D_0046F788;
extern "C" void func_0025F5E8(unsigned short *out) {
    func_00271730(out,func_00150630(D_00475480,D_0046F788));
}
extern "C" unsigned char D_00475480[];
extern "C" void func_00271448(char *,const char *,...);
struct CALLBACK_VALUE_A { char prefix[0x3C]; float value; };
struct CALLBACK_VALUE_B { char prefix[0xC4]; float value; };
struct CALLBACK_ACTOR {
    char prefix[0xF78]; int mode;
    char padF7C[0xF94-0xF7C]; float scale;
    char padF98[0x1004-0xF98];
    CALLBACK_VALUE_A *a; CALLBACK_VALUE_B *b;
};
extern "C" void *func_001F4AD0(void *,int);
extern "C" int func_0013B500(CALLBACK_ACTOR *,int);
extern "C" const char *func_0029CF10(float);
extern "C" const char D_00327EE8[],D_00327EF0[];
extern "C" void func_0025F1D8(unsigned short *out) {
    CALLBACK_ACTOR *actor=static_cast<CALLBACK_ACTOR *>(func_001F4AD0(D_00475480,0));
    if(actor&&func_0013B500(actor,51)) {
        float amount;
        switch(actor->mode) {
        case 0:amount=actor->a->value*actor->scale;break;
        case 1:amount=actor->b->value*actor->scale;break;
        }
        char text[32];
        if(func_0013B500(actor,52)) {
            func_00271448(text,D_00327EE8,(int)amount);
            func_002717E0(out,text);
        } else if(func_0013B500(actor,54)) {
            func_00271448(text,D_00327EF0,func_0029CF10(amount));
            func_002717E0(out,text);
        }
    }
}
