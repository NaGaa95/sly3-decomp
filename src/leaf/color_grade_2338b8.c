// SLY3_CFLAGS: -Os -G0 -fno-cse-skip-blocks
// Colour grading of one RGBA pixel: unpack to floats, push each channel along a power curve by the difference between its weight
// and the mean of the other two weights (grade table D_00341FF8, exponent 1/3 or 1.8), convert to HLS, scale lightness and
// saturation through the curve D_00341FF0 (saturation only when bit 1 of D_0036DBEC is clear), convert back and repack.
struct ClutPixel { unsigned char red, green, blue, alpha; };
struct G { char pad0[0x38]; float p38, p3C, p40; char pad44[0x50 - 0x44]; float w0, w1, w2; };
extern struct G D_0036BC10;
extern char D_00341FF0[];
extern char D_00341FF8[];
extern unsigned int D_0036DBEC;
void func_0011F230(struct ClutPixel *, float *);
void func_0011F770(float *, float *);
void func_0011FA88(float *, float *);
void func_0011F288(float *, int, struct ClutPixel *);
float func_0011EE68(void *, float);
float func_002A42C8(float, float);
void func_002338B8(struct ClutPixel *color)
{
    float rgb[4] __attribute__((aligned(16)));
    struct ClutPixel copy;
    float adj[4] __attribute__((aligned(16)));
    float hls[4] __attribute__((aligned(16)));
    int i;
    copy = *color;
    func_0011F230(&copy, rgb);
    adj[0] = D_0036BC10.w0 - (D_0036BC10.w1 + D_0036BC10.w2) * 0.5f;
    adj[1] = D_0036BC10.w1 - (D_0036BC10.w0 + D_0036BC10.w2) * 0.5f;
    adj[2] = D_0036BC10.w2 - (D_0036BC10.w0 + D_0036BC10.w1) * 0.5f;
    for (i = 0; i < 3; i++) {
        if (adj[i] != 0.0f) {
            float t = func_0011EE68(D_00341FF8, adj[i] * 0.01f);
            float v = rgb[i] + rgb[i];
            if (0.0f < t) {
                v = (1.0f - t) * v + t * func_002A42C8(v, 1.0f / 3.0f);
            } else {
                t = -t;
                v = (1.0f - t) * v + t * func_002A42C8(v, 1.8000001f);
            }
            rgb[i] = v * 0.5f;
        }
    }
    func_0011F770(rgb, hls);
    hls[1] = hls[1] * D_0036BC10.p38;
    hls[1] = func_0011EE68(D_00341FF0, (hls[1] - D_0036BC10.p38 * 0.25f) * D_0036BC10.p3C + D_0036BC10.p38 * 0.25f);
    if (!(((int)D_0036DBEC >> 1) & 1))
        hls[2] = func_0011EE68(D_00341FF0, hls[2] * D_0036BC10.p40);
    func_0011FA88(hls, rgb);
    func_0011F288(rgb, color->alpha, color);
}
