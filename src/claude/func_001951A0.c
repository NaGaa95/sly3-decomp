// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } QU;
struct Frame { qword r[4]; unsigned char pad[0x50]; QU last; };
void func_002BC400(qword *out, void *source);
void func_001951A0(struct Frame *frame, short *out, void *source, float w)
{
    qword local;
    QU pos;
    int i;
    int delta;
    func_002BC400(&local, source);
    __asm__("vmulax.xyz $ACC,%1,%2x\n\tvmadday.xyz $ACC,%3,%2y\n\tvmaddaz.xyz $ACC,%4,%2z\n\tvmaddw.xyz %0,%5,$vf0w"
        : "=j"(pos.q) : "j"(frame->r[0]), "j"(local), "j"(frame->r[1]), "j"(frame->r[2]), "j"(frame->r[3]));
    pos.f[3] = w;
    for (i = 0; i < 4; i++) {
        if (i < 3) {
            pos.i[i] = (int)(pos.f[i] * 16.0f);
        }
        delta = pos.i[i] - frame->last.i[i];
        out[i] = delta;
    }
    frame->last = pos;
}
