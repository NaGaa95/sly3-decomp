// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_ASFIX: engine-divfix1
// Ping-pong frame animator (Sly 2 UpdatePingpong / UCompletePingpong): advance the frame cursor by dframe * dt, bounce at
// both ends (re-rolling the loop speed and the pause when it returns to frame 0), and the completion fraction getter.
struct SAI { int a; };
struct PINGPONG {
    char pad[0x1C]; int cframe; char pad1[0x38 - 0x20]; SAI sai; char pad2[0x50 - 0x3C];
    float dtLoopMin; float dtLoopMax; float dtPauseMin; float dtPauseMax; float dframe; float iframe; float dtPause; float dtPauseRemaining;
};
extern struct { float t; float dt; } D_0036BB98;
extern "C" int func_0011AEF8(SAI *psai);
extern "C" float func_0011E940(float gLow, float gHigh);
extern "C" void func_00237220(PINGPONG *p, int iframe);
extern "C" void func_002375D8(PINGPONG *ppingpong, float dt)
{
    if (func_0011AEF8(&ppingpong->sai) || ppingpong->cframe < 2)
        return;

    if (ppingpong->dtPauseRemaining > 0.0f)
    {
        ppingpong->dtPauseRemaining -= D_0036BB98.dt;
        return;
    }

    float dframe = ppingpong->dframe * D_0036BB98.dt;
    ppingpong->iframe += dframe;

    if (ppingpong->iframe >= (float)ppingpong->cframe)
    {
        ppingpong->iframe -= dframe;
        ppingpong->dframe = -ppingpong->dframe;
    }

    if (ppingpong->iframe < 0.0f)
    {
        ppingpong->iframe = 0.0f;
        float rand1 = func_0011E940(ppingpong->dtLoopMin, ppingpong->dtLoopMax);
        ppingpong->dframe = (float)(ppingpong->cframe * 2) / rand1;

        float rand2 = func_0011E940(ppingpong->dtPauseMin, ppingpong->dtPauseMax);
        ppingpong->dtPause = rand2;
        ppingpong->dtPauseRemaining = rand2;
    }

    func_00237220(ppingpong, (int)ppingpong->iframe);
}
extern "C" float func_002376F0(PINGPONG *ppingpong)
{
    float absDframe = ppingpong->dframe;
    float progress;

    if (absDframe < 0.0f)
    {
        absDframe = -absDframe;
        progress = (float)(ppingpong->cframe * 2) - ppingpong->iframe;
    }
    else
    {
        progress = ppingpong->iframe;
    }

    return (progress / absDframe) /
           (((float)(ppingpong->cframe * 2) / absDframe) + ppingpong->dtPause);
}
