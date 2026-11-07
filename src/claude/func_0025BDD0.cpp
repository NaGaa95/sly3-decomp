// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Sly3 level/task reset: focus Guard scopes as in src/engine/focus_start_18a0d0.cpp, CTX scope, slot-57 Remove loop.
struct LINKO { unsigned char prefix[0xF0]; int first; int second; };
struct OBJ { unsigned char prefix[0x6C]; LINKO *link; unsigned char gap70[0xFC - 0x70]; int first; int second; };
class Guard {
public:
    LINKO *link;
    OBJ *object;
    int linkFirst, objectFirst, linkSecond, objectSecond;
    Guard(OBJ *target, int first, int second)
    {
        link = target->link;
        object = target;
        if (object) {
            objectFirst = object->first;
            object->first = first;
            objectSecond = object->second;
            object->second = second;
        }
        if (link) {
            linkFirst = link->first;
            link->first = first;
            linkSecond = link->second;
            link->second = second;
        }
    }
    Guard(LINKO *target, int first, int second)
    {
        link = target;
        object = 0;
        if (link) {
            linkFirst = link->first;
            link->first = first;
            linkSecond = link->second;
            link->second = second;
        }
    }
    ~Guard()
    {
        if (link) {
            link->first = linkFirst;
            link->second = linkSecond;
        }
        if (object) {
            object->first = objectFirst;
            object->second = objectSecond;
        }
    }
};
struct VO {
    char pad[12];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void Remove();
};
struct CTX { int a; CTX(); ~CTX(); };
struct TBL { unsigned char prefix[0x1498]; int w1498, w149C, w14A0; };
struct S {
    char pad[0x3EB8]; int c; VO *ap[(0x4044 - 0x3EBC) / 4]; LINKO *p4044; OBJ *p4048; char pad404C[4]; void *p4050;
    char pad4054[0x4FA4 - 0x4054]; int n4FA4;
};
extern "C" {
extern char D_0046F550[];
extern TBL D_0036C700;
extern char D_0036F864[];
extern char D_00474FF0[];
void func_001D2C90(void *);
void func_0025BD68(S *);
void func_001F4B00(S *, int, int);
void func_00187118(void *);
void func_00188620(OBJ *);
void func_00186298(LINKO *);
void func_0018A900(int *count, OBJ ***list);
void func_0018A3E8(OBJ *object, int state);
void func_00210C90(void *, int);
void func_0025BBD0(S *);
void func_0025BD20(S *);
void func_0015AE70(S *);
void func_0015B790(S *);
void func_001FC6A0(S *);
void func_00247588(void *);
void func_0025BDD0(S *p);
}
void func_0025BDD0(S *p)
{
    int i;
    func_001D2C90(D_0046F550);
    func_0025BD68(p);
    func_001F4B00(p, 0, 0);
    func_001F4B00(p, 1, 0);
    while (p->c > 0) p->ap[p->c - 1]->Remove();
    p->n4FA4 = 0;
    if (p->p4050) {
        func_00187118(p->p4050);
        p->p4050 = 0;
    }
    int w1498, w149C, w14A0;
    w1498 = D_0036C700.w1498;
    w149C = D_0036C700.w149C;
    w14A0 = D_0036C700.w14A0;
    if (p->p4048) {
        Guard guard(p->p4048, 2, 0);
        func_00188620(p->p4048);
    }
    if (p->p4044) {
        Guard guard(p->p4044, 2, 0);
        func_00186298(p->p4044);
    }
    D_0036C700.w1498 = w1498;
    D_0036C700.w149C = w149C;
    D_0036C700.w14A0 = w14A0;
    {
        CTX ctx;
        int count;
        OBJ **list;
        func_0018A900(&count, &list);
        for (i = 0; i < count; i++) {
            OBJ *object = list[i];
            Guard guard(object, 2, 0);
            func_0018A3E8(object, -1);
        }
    }
    for (i = 0; i < 2; i++) func_00210C90(D_0036F864 + i * 0x11C0, 3);
    func_0025BBD0(p);
    func_0025BD20(p);
    func_0015AE70(p);
    func_0015B790(p);
    func_001FC6A0(p);
    func_00247588(D_00474FF0);
}
