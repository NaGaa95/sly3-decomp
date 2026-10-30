// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct M4 { float m[4][4]; } __attribute__((aligned(16)));
struct E { float x, y, z; int id; char pad[0x40]; };
struct Self { char pad[0x18]; int count; char pad1C[4]; qword points[8]; char padA0[8]; struct E *entries; char padAC[4]; struct M4 m0; struct M4 m1; };
float func_002BC420(qword *v);
float func_002BC430(qword *v);
float func_002BC448(qword *v);

void func_0014B248(struct Self *self, struct M4 *m)
{
    int i;
    struct M4 *pm;
    self->m1 = *m;
    pm = &self->m1;
    self->m0 = *pm;
    for (i = 0; i < self->count; i++) {
        struct E *e = &self->entries[i];
        qword *pt = &self->points[i];
        qword v;
        float x, y;
        e->id = -1;
        __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
                : "=j"(v) : "j"(((qword *)m)[0]), "j"(((qword *)m)[1]), "j"(((qword *)m)[2]), "j"(((qword *)m)[3]), "j"(*pt));
        x = func_002BC420(&v);
        y = func_002BC430(&v);
        {
            float z = func_002BC448(&v);
            e->x = x;
            e->y = y;
            e->z = z;
        }
    }
}
