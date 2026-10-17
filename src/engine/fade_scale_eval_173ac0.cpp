// SLY3_CFLAGS: -Os -G0 -ffast-math -fno-exceptions
extern "C" {
extern float D_0036BB98;
extern const float D_00321160[3];
extern unsigned char D_00475480[];
int func_001A9478(void *manager, int index);
}
struct FadeSource { unsigned char prefix[0x44]; float scale; unsigned char gap48[8]; float duration; };
struct FadeSelf { unsigned char prefix[0x14]; FadeSource *source; unsigned char gap18[0x4C - 0x18]; float start; };
extern "C" float func_00173AC0(FadeSelf *self)
{
    FadeSource *source;
    if(func_001A9478(D_00475480, -1)) return 0.0f;
    source = self->source;
    if(0.0f < source->duration) {
        float elapsed = D_0036BB98 - self->start;
        float one = 1.0f;
        float span = source->duration <? one;
        float t = one <? (elapsed / span);
        return source->scale * (D_00321160[0] + t * (D_00321160[1] + t * D_00321160[2]));
    }
    return source->scale;
}
