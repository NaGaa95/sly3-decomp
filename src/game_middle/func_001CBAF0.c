// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
// Update the two contact positions of every pair in a list (position + axis * scale, or the shared fallback) and
// store the projected separation of the two positions on the pair's axis. Same routine as Sly 2 func_001A7E60.
typedef int qword __attribute__((mode(TI)));
struct Source { int x0, x4; float scale; };
struct Link { char pad[0x70]; qword position; };
struct Endpoint { struct Source *source; struct Link *link; int x8; int xC; qword result; qword fallback; qword x30; };
struct Pair { struct Endpoint e[2]; qword axis; int separation; int pad[2]; int mode; };
qword func_0028E910(struct Link *link, struct Link *other, qword q);
// position + axis.xyz * scale (the scale word goes through qmtc2 and is also parked in the union slot)
static inline qword PositionPlusAxis(qword a, qword *axis, int scaleBits)
{
    union { qword q; float f; } t;
    register qword s __asm__("vf3"); /* pinned: scale in vf3, position in vf2 (original allocation) */
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(scaleBits));
    t.q = s;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(a) : "0"(a), "j"(*axis), "j"(s) : "memory");
    return a;
}
void func_001CBAF0(void *unused, int n, struct Pair **pairs)
{
    int i;
    for (i = 0; i < n; i++) {
        struct Pair *p = pairs[i];
        struct Endpoint *e = p->e;
        int j;
        for (j = 0; j < 2; j++, e++) {
            struct Link *o = e->link;
            int scaleBits;
            qword position;
            if (!o)
                continue;
            if (j == 0) {
                switch (p->mode) {
                case 4: case 5: case 6:
                    {
                        union { float f; int i; } u;
                        u.f = -e->source->scale;
                        scaleBits = u.i;
                    }
                    position = o->position;
                    break;
                default:
                    goto fallback;
                }
            } else {
                switch (p->mode) {
                case 7: case 9:
                    position = o->position;
                    scaleBits = *(int *)&e->source->scale;
                    break;
                default:
                    goto fallback;
                }
            }
            e->result = PositionPlusAxis(position, &p->axis, scaleBits);
            continue;
        fallback:
            e->result = func_0028E910(o, 0, e->fallback);
        }
        {
            qword d, r, one;
            int bits;
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(p->e[0].result), "j"(p->e[1].result));
            __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(r), "=j"(one) : "j"(p->axis), "j"(d));
            __asm__("qmfc2.ni %0, %2\n\tsw %0, %1" : "=&r"(bits), "=m"(p->separation) : "j"(r));
        }
    }
}
