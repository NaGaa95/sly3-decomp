// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
static inline float sqrtf_(float x) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
struct Vector3 { float x,y,z; };
struct Spread { unsigned char prefix[0x200]; float scale; struct Vector3 vector; };
extern struct Vector3 D_00327260;
void func_0024F188(struct Spread *spread,float scale)
{
    spread->vector=D_00327260;
    spread->vector.x*=scale;
    spread->vector.y*=scale;
    spread->vector.z*=1.0f/sqrtf_(scale);
    spread->scale=scale;
}
