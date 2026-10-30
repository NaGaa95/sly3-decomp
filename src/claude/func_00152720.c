// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta, reserved; void *(*call)(void *); };
struct Obj { char pad[0xC]; struct VirtualEntry *table; };
extern char D_0036C700[];
extern int D_004797C8;
void func_0024DA88(void *p);
char *func_00185720(void *a, void *b);
void func_00172D10(void *a, void *b);
float func_002A3EE8(float y, float x);
void func_001547F8(void *p);
void func_00156768(void *p, int n);
void func_001561B0(void *p);

void func_00152720(struct Obj *p)
{
    char *q = (char *)p;
    float *m;
    func_0024DA88(p);
    if (*(void **)(q + 0x1108))
        func_00172D10(*(void **)(q + 0x1108), *(void **)(func_00185720(D_0036C700, p) + 0xC));
    m = p->table[36].call((char *)p + p->table[36].delta); 
    *(float *)(q + 0x110C) = func_002A3EE8(m[1], m[0]);
    ((void (*)(void *, int))p->table[99].call)((char *)p + p->table[99].delta, 0);
    p->table[118].call((char *)p + p->table[118].delta);
    func_001547F8(p);
    func_00156768(p, (D_004797C8 >> 2) & 1);
    func_001561B0(p);
    {
        struct Obj *o = *(struct Obj **)(q + 0x1448);
        struct Obj *o2;
        if (o)
            o->table[9].call((char *)o + o->table[9].delta);
        o2 = *(struct Obj **)(q + 0x144C);
        if (o2)
            o2->table[9].call((char *)o2 + o2->table[9].delta);
    }
}
