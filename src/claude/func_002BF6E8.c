// SLY3_CFLAGS: -Os -G0
struct S3C8 { char pad[0x3C8]; int a; int b; };
struct S10D0 { char pad[0x10D0]; struct S3C8 *p; };
void func_002BF6E8(struct S10D0 *s, int v) { s->p->a = v; }
void func_002BF6F8(struct S10D0 *s, int v) { s->p->b = v; }
int func_002BF708(struct S10D0 *s) { return s->p->a; }
int func_002BF718(struct S10D0 *s) { return s->p->b; }
