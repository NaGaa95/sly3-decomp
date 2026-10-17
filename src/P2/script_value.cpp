// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct CALLBACK_REF { int tag; union { int n;float g;void *pv; } value; CALLBACK_REF(const CALLBACK_REF &); ~CALLBACK_REF(); };
extern "C" CALLBACK_REF func_002BC010(int,void *);
extern "C" void func_0012BC20(CALLBACK_REF *);
inline CALLBACK_REF::~CALLBACK_REF() { func_0012BC20(this); }
struct ScriptOwner { int enabled; unsigned char gap4[0x12C]; int option; };
extern "C" ScriptOwner D_004793C8;
static inline int ReadOption(void *record)
{
    CALLBACK_REF ref=func_002BC010(D_004793C8.option,record);
    return ref.value.n;
}
extern "C" int func_0025E198(void *record)
{
    return D_004793C8.enabled ? ReadOption(record) : 0;
}
