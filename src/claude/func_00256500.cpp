// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly3 FTargetrecAllows (cf Sly2 0x20A818): XF vcall (slot 36) instead of func_001A62E8.
typedef int qword __attribute__((mode(TI)));
struct XF { char pad[0x30]; qword pos; };
struct LO {
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
    virtual XF *PxfGet();
};
struct Actor : LO { char pad1[0x10A0 - 0x10]; int blocked, ready, busy; };
struct P { char pad[0xC]; Actor *target; int kind; float unused, tolerance; int disabled; char pad20[8]; int count; Actor *actors[1]; };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("mfc1 %0,%1" : "=rj"(q) : "f"(f)); } };
extern "C" {
void *func_00256318(P *);
void func_00166A40(void *);
int func_00167F60(void *, qword, VU_FLOAT);
void func_00120B00(qword, float *, float *, float *);
float func_00256368(P *);
float func_0011E3B8(float);
int func_00256500(P *p, Actor *a);
}
static inline qword Sub(qword a, qword b) { __asm__("vsub.xyzw %0,%0,%1" : "=j"(a) : "j"(b), "0"(a)); return a; }

int func_00256500(P *p, Actor *a)
{
    float angle0, angle1;
    qword position0, position1;
    if (p->disabled) goto fail;
    if (!a->blocked) {
        int i, n = p->count;
        for (i = 0; i < n; i++) if (p->actors[i]->busy) goto fail;
    }
    switch (p->kind) {
    case 0: {
        if (a->ready) return 1;
        void *cm; cm = func_00256318(p);
        position0 = a->PxfGet()->pos;
        func_00166A40(cm);
        if (!func_00167F60(cm, position0, VU_FLOAT(0.0f))) goto fail;
        qword other; other = p->target->PxfGet()->pos;
        func_00120B00(Sub(position0, other), &angle0, 0, 0);
        if (p->tolerance < __builtin_fabsf(func_0011E3B8(angle0 - func_00256368(p)))) { fail: return 0; }
        return 1;
    }
    case 1: {
        position1 = a->PxfGet()->pos;
        qword other; other = p->target->PxfGet()->pos;
        func_00120B00(Sub(position1, other), &angle1, 0, 0);
        if (p->tolerance < __builtin_fabsf(func_0011E3B8(angle1 - func_00256368(p)))) return 0;
        return 1;
    }
    case -1: break;
    default: break;
    }
    return 1;
}
