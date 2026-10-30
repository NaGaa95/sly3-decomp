// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VTE { short delta; short pad; void (*pfn)(void *, int, int); };
struct Obj { unsigned char pad[0xC]; struct VTE *pvt; };
struct Self { unsigned char pad[0x48]; int n48; struct Obj *p4C; };
extern unsigned char D_00474FF0[];
void func_00248740(void *p);
void func_0018C1A8(struct Self *self)
{
    if (self->n48 != -1) {
        struct Obj *o;
        func_00248740(D_00474FF0);
        o = self->p4C;
        if (o) {
            o->pvt[0x5F].pfn((char *)o + o->pvt[0x5F].delta, 0x20, 0);
            self->p4C = 0;
        }
        self->n48 = -1;
    }
}
