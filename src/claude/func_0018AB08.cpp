// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// CRef locals; their destructor is Decref (func_0012BC20).
struct CRef;
extern "C" void func_0012BC20(CRef *ref);
struct CRef {
    int tagk; union { float g; int n; } value;
    ~CRef() { func_0012BC20(this); }
};
struct Globals { unsigned char pad[0x406C]; int query; int pad4070; int lookup; };
struct Ui { unsigned char pad[0x1498]; int a; int b; int c; };
extern Globals D_00475480;
extern Ui D_0036C700;
extern unsigned char D_004BC230[], D_0046FC30[];
struct Self;
extern Self *D_0036DBA8;
extern "C" {
void func_002BC010(CRef *query, int kind, Self *self);
void func_00284568(void *p);
int func_0021DD30(void *p);
void func_0018AD58(void);
void func_00221B40(void *p);
void func_0021D290(Self *self);
void func_0021D570(Self *self);
int func_0025E4A0(int id, Self *self);
int func_0025E070(int id);
void func_00289070(void *g, int a, int b, int c, int d);
void func_00289198(void *g, int id, int c, Self *self);
}
extern "C" void func_0018AB08(Self *self)
{
    float g;
    int id;
    int value;
    {
        CRef query;
        func_002BC010(&query, D_00475480.query, self);
        g = query.value.g;
    }
    func_00284568(D_004BC230);
    if (func_0021DD30(D_0046FC30) && g == 0.0f) {
        func_0018AD58();
        func_00221B40(D_0046FC30);
        return;
    }
    D_0036DBA8 = self;
    func_0021D290(self);
    func_0021D570(self);
    D_0036C700.a = -1;
    D_0036C700.b = -1;
    D_0036C700.c = -1;
    {
        CRef query;
        func_002BC010(&query, D_00475480.lookup, self);
        value = query.value.n;
    }
    id = 1;
    if (value) id = value;
    if (func_0025E4A0(id, self)) {
        func_00289070(&D_00475480, func_0025E070(0), 0x1A8, 0x12, -1);
    } else {
        func_00289198(&D_00475480, id, 0x12, self);
    }
}
