// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct DL { void *pvFirst, *pvLast; int ibDle; };
struct DLI;
extern "C" DLI *D_0036AE94;
struct DLI {
    DL *pdl;
    void **ppv;
    int ibDle;
    DLI *pdliNext;
    DLI(DL *list)
        : pdl(list), ppv((void **)list), ibDle(list->ibDle),
          pdliNext(D_0036AE94)
    {
        D_0036AE94 = this;
    }
    ~DLI()
    {
        D_0036AE94 = pdliNext;
    }
    void *Next()
    {
        void *value = *ppv;
        ppv = (void **)((unsigned int)value + (unsigned int)ibDle);
        return value;
    }
};
struct ResetMethod { short delta,pad; void (*method)(void *); };
struct ResetObject { unsigned char prefix[0xC]; ResetMethod *table; };
extern "C" {
extern unsigned char D_0046F550[],D_00370AC8[],D_0046F7A0[],D_0046F810[],D_0046F770[],D_0046FAA0[],D_003751D0[],D_00375240[],D_0046FBE0[],D_0046FC30[],D_0046FC90[];
void func_001D2D10(char *);
void func_001C4F68(void *);
void func_0021EE20(int);
void func_0021FDD8(int);
void func_0021E6E8(void *);
void func_00220E28(int);
void func_001D0BB0(void *);
void func_0021EB88(void *);
void func_00222840(void *);
}
extern "C" void func_0021D7A0(DL *list)
{
    DLI iterator(list);
    ResetObject *object;
    while((object=(ResetObject *)iterator.Next())!=0) {
        ResetMethod *entry=&object->table[11];
        entry->method((char *)object+entry->delta);
    }
    func_001D2D10((char *)D_0046F550);
    func_001C4F68(D_00370AC8);
    func_0021EE20((int)D_0046F7A0);
    func_0021FDD8((int)D_0046F810);
    func_0021E6E8(D_0046F770);
    func_00220E28((int)D_0046FAA0);
    func_001D0BB0(D_003751D0);
    func_0021EB88(D_00375240);
    func_0021EB88(D_0046FBE0);
    func_0021EB88(D_0046FC30);
    func_00222840(D_0046FC90);
}
