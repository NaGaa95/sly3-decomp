// Complete original Sly3 body; ordinary source/profile reconstruction.
// F12 duration is added to original global clock. The one MIN.S primitive has real tied float input/result and float limit input, preserving PS2 hardware min behavior. The timer load/store and addition are C.
// SLY3_CFLAGS: -Os -G0
struct Object { char pad[0x134]; float time; }; extern float D_0036BB98; static inline float HardwareMin(float value,float limit) { asm("min.s %0,%0,%1" : "+f"(value) : "f"(limit)); return value; } void func_0014CB98(struct Object *p,float duration) { float limit=p->time; float value=D_0036BB98+duration; p->time=HardwareMin(value,limit); }
