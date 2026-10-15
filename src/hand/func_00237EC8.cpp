// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
struct CLOCK { float t; };
extern CLOCK g_clock ;
struct CIRCLER { char pad[0x50]; float radsSpeed; };
float GModPositive(float, float);
extern "C" float func_00237EC8(CIRCLER *pcircler)
{
    float angle = g_clock.t * pcircler->radsSpeed;
    return GModPositive(angle, 6.28318530718f) * 0.159154943092f;
}
