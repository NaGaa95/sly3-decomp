// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int ParticleWord __attribute__((mode(TI)));
struct ParticleMatrix { ParticleWord rows[4]; };
struct RelativeFrame { char prefix[0x40]; ParticleMatrix matrix; };
struct RuntimeAttachedPointOwner {
    char prefix[0x40];
    RelativeFrame *frame;
    char opaque44[0x80 - 0x44];
    ParticleWord point;
};
extern "C" ParticleWord func_0028BCD0(RelativeFrame *,void *,ParticleWord);
extern ParticleWord D_00317560;

static __inline__ ParticleWord RuntimeAffinePointXYZ(const ParticleMatrix *matrix,ParticleWord point)
{
    ParticleWord result;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(result) : "j"(matrix->rows[0]),"j"(matrix->rows[1]),"j"(matrix->rows[2]),"j"(matrix->rows[3]),"j"(point));
    return result;
}

extern "C" ParticleWord func_002900F8(RuntimeAttachedPointOwner *owner)
{
    RelativeFrame *frame = owner->frame;
    ParticleWord result;
    if (frame)
        result = func_0028BCD0(frame,0,RuntimeAffinePointXYZ(&frame->matrix,owner->point));
    else
        result = D_00317560;
    return result;
}
