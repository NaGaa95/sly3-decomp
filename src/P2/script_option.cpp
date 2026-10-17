// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct CALLBACK_REF { int tag; union { int n;float g;void *pv; } value; CALLBACK_REF(const CALLBACK_REF &); ~CALLBACK_REF(); };
extern "C" CALLBACK_REF func_002BC010(int,void *);
extern "C" void func_0012BC20(CALLBACK_REF *);
inline CALLBACK_REF::~CALLBACK_REF() { func_0012BC20(this); }
struct ScriptOwner { int enabled; unsigned char gap4[0x350]; int options[1]; };
extern "C" ScriptOwner D_004793C8;
static inline int ReadOption(int option,void *record)
{
    CALLBACK_REF ref=func_002BC010(option,record);
    return ref.value.n;
}
extern "C" int func_0025E250(int index,void *record)
{
    if(D_004793C8.enabled) {
        int option=D_004793C8.options[index];
        if(option)
            return ReadOption(option,record);
    }
    return 0;
}
