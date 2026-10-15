// Reference algorithm: src/hand/func_00228BB0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct T { char pad[0xD4]; float a, b; };
struct S { char pad[0xD8]; struct T *t; };
void func_0023C468(struct S *p);
void func_0023FCD8(struct S *p, int a);
void func_002804A0(struct S *p)
{
    func_0023C468(p);
    func_0023FCD8(p, 1);
    { struct T *t = p->t;
    t->b = 1.0f;
    t->a = 1.0f; }
}
