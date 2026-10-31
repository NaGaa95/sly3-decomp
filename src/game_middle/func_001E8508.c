// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Recalculate the camera frustum/projection from the fov and the viewport rectangle (cf. func_00166808).
struct RECT { int left, top, right, bottom; };
struct CM {
    char pad0[0x110]; float x110; float x114; float x118; char pad11C[0x134 - 0x11C];
    float x134; float x138; float x13C; float x140; float x144; float x148; char pad14C[0x160 - 0x14C];
    struct RECT rc; char pad170[0x1A0 - 0x170]; char m1A0[1];
};
float tanf(float);
void func_0011D8A8(void *p, float a, float b, float c, float d, float e, float f);
static __inline__ float SqrtF(float x) { float r; __asm__ __volatile__("sqrt.s %0,%1" : "=&f"(r) : "f"(x)); return r; }
static __inline__ float GMin(float a, float b) { return b < a ? b : a; }
void func_001E8508(struct CM *pcm)
{
    struct RECT *prc = &pcm->rc;
    float t, c;
    pcm->x134 = (float)(prc->right - prc->left) / (float)(prc->bottom - prc->top);
    t = tanf(pcm->x118 * 0.5f);
    c = pcm->x134;
    pcm->x13C = t;
    pcm->x138 = t * c;
    pcm->x114 = GMin(1.0f, pcm->x118 / pcm->x110);
    pcm->x140 = t * SqrtF(c * c + 1.0f) * pcm->x144 + 1.0f;
    {
        float a = (float)(prc->right - prc->left) / (pcm->x138 * 4096.0f);
        float b = (float)(prc->bottom - prc->top) / (t * 4096.0f);
        func_0011D8A8(pcm->m1A0, a, b, 0.0f, 0.0f, pcm->x144, pcm->x148);
    }
}
