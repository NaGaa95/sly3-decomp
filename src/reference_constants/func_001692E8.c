// Reference algorithm: src/hand/func_0014E270.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern float D_00320E40;
void func_001C56D0(float a, float b, float c, float d, float *pa, float *pb);
struct P { char pad[0x14]; float g240, g244, g248; };
void func_001692E8(struct P *p, float *af, float f)
{
    if (f == D_00320E40) f = 1.0f;
    func_001C56D0(1.0f, 4080.0f, p->g244 / p->g240, (1.0f - p->g248 * f) * 4080.0f, &af[0], &af[1]);
    af[0] += 8417280.0f;
    af[2] = p->g240;
    af[3] = af[0] + 8192.0f;
}
