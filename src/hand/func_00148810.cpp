// Sly 2 reference: src/hand/ImrsgLookUp__FffiP4MRSGPf.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct MRSG { float t; float dt; };
int ImrsgLookUp(float t, float tMax, int cmrsg, MRSG *amrsg, float *pdt) __asm__("func_00148810");
int ImrsgLookUp(float t, float tMax, int cmrsg, MRSG *amrsg, float *pdt)
{
    int i;
    float dt;
    for (i = 0; ; amrsg++, i++) {
        if (i >= cmrsg) goto done;
        if (amrsg->dt == 0.0f) continue;
        dt = t - amrsg->t;
        if (dt < 0.0f) dt += tMax;
        if (dt < amrsg->dt + 0.0001f) break;
    }
    if (pdt) *pdt = dt;
done:
    return i;
}
