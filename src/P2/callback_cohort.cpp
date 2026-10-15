// Recovered callback actor/menu/related object queries and script/counter formatting.
// Structure names are provisional; accessed offsets and strides are original.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "game_text.h"
struct CALLBACK_GAME_COUNTERS { char prefix[0x4F58]; int first,second; };
extern "C" CALLBACK_GAME_COUNTERS D_00475480;
extern "C" void func_00271448(char *,const char *,...);
extern "C" void *memset(void *,int,unsigned int);
extern "C" int func_0013B500(void *,int);
struct CALLBACK_LABEL { char prefix[0xE8]; int stringId; };
struct CALLBACK_MENU { char prefix[0x74]; int count; CALLBACK_LABEL *labels[1]; };
struct CALLBACK_KIND { int unknown,index; };
struct CALLBACK_RELATED {
    char prefix[0x19C]; int stringId; int unknown1A0; int amount;
    char pad1A8[0x1B4-0x1A8]; CALLBACK_KIND *kind;
};
struct CALLBACK_ACTOR_STATE {
    char prefix[0x508]; int mode;
    char pad50C[0x9E0-0x50C]; CALLBACK_RELATED *related;
    char pad9E4[0xF90-0x9E4]; CALLBACK_MENU *menu;
    char padF94[0x1404-0xF94]; int fallbackStringId;
};
struct CALLBACK_KIND_INFO { int amount,stringId,unknown; };
extern "C" CALLBACK_KIND_INFO D_00349070[];
extern "C" void *func_001F4AD0(void *,int);
extern "C" const unsigned short *func_0024C668(CALLBACK_MENU *);
extern "C" const unsigned short *func_0024C6A0(CALLBACK_MENU *);
extern "C" const char D_00327ED0[],D_00327ED8[];

extern "C" void func_0025F2E8(unsigned short *out,int which) {
    CALLBACK_ACTOR_STATE *actor=static_cast<CALLBACK_ACTOR_STATE *>(func_001F4AD0(&D_00475480,0));
    if(actor&&func_0013B500(actor,51)) {
        CALLBACK_MENU *menu=actor->menu;
        const unsigned short *text=0;
        if(menu) {
            switch(which) {
            case 1:text=func_0024C668(menu);break;
            case 0:text=func_0024C6A0(menu);break;
            }
        }
        if(text)func_00271730(out,text);
    }
}

extern "C" void func_0025F398(unsigned short *out,int index) {
    CALLBACK_ACTOR_STATE *actor=static_cast<CALLBACK_ACTOR_STATE *>(func_001F4AD0(&D_00475480,0));
    if(actor&&func_0013B500(actor,51)) {
        CALLBACK_MENU *menu=actor->menu;
        if(menu&&index<menu->count)
            func_00271730(out,func_00150630(&D_00475480,menu->labels[index]->stringId));
    }
}

extern "C" void func_0025F628(unsigned short *out) {
    CALLBACK_ACTOR_STATE *actor=static_cast<CALLBACK_ACTOR_STATE *>(func_001F4AD0(&D_00475480,0));
    int stringId=-1;
    if(actor&&func_0013B500(actor,51)) {
        CALLBACK_RELATED *related=actor->related;
        if(related&&actor->mode==12) {
            if(func_0013B500(related,106)) stringId=D_00349070[related->kind->index].stringId;
            else if(func_0013B500(related,104)) stringId=related->stringId;
            else stringId=actor->fallbackStringId;
        }
    }
    if(stringId!=-1)func_00271730(out,func_00150630(&D_00475480,stringId));
}

extern "C" void func_0025F720(unsigned short *out) {
    CALLBACK_ACTOR_STATE *actor=static_cast<CALLBACK_ACTOR_STATE *>(func_001F4AD0(&D_00475480,0));
    char text[32];memset(text,0,sizeof(text));
    if(actor&&func_0013B500(actor,51)) {
        CALLBACK_RELATED *related=actor->related;
        if(related&&actor->mode==12) {
            if(func_0013B500(related,106)) func_00271448(text,D_00327ED0,D_00349070[related->kind->index].amount);
            else if(func_0013B500(related,104)) {
                if(related->amount)func_00271448(text,D_00327ED0,related->amount);
            }
        }
    }
    func_002717E0(out,text);
}

struct CALLBACK_REF_VALUE {
    int tag; union { int n;float g;void *pv; } value;
    CALLBACK_REF_VALUE(const CALLBACK_REF_VALUE &); ~CALLBACK_REF_VALUE();
};
extern "C" CALLBACK_REF_VALUE func_002BC010(int,void *);
extern "C" void func_0012BC20(CALLBACK_REF_VALUE *);
inline CALLBACK_REF_VALUE::~CALLBACK_REF_VALUE() { func_0012BC20(this); }
extern "C" unsigned char D_00468D30[];
static inline int ReadValue(int *tag) {
    CALLBACK_REF_VALUE ref=func_002BC010((int)tag,D_00468D30);
    return ref.value.n;
}
extern "C" void func_0025F018(unsigned short *out,int **arg) {
    int *tag=*arg;
    if(tag&&*tag) {
        char text[32];
        func_00271448(text,D_00327ED0,ReadValue(tag));
        func_002717E0(out,text);
    }
}

extern "C" void func_0025F098(unsigned short *out) {
    char text[32];func_00271448(text,D_00327ED8,D_00475480.first,D_00475480.second);
    func_002717E0(out,text);
}

struct CALLBACK_ID_SOURCE { char prefix[0x120]; int id; };
extern "C" unsigned char D_0036C700[];
extern "C" int func_001852E0(void *);
extern "C" void func_0025F0E8(unsigned short *out,int unused,CALLBACK_ID_SOURCE *source) {
    int value;
    if(func_0013B500(source,167))value=source->id;
    else value=func_001852E0(D_0036C700);
    char text[32];func_00271448(text,D_00327ED0,value);func_002717E0(out,text);
}
