// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct VECTOR { float x, y, z, w; } __attribute__((aligned(16))) VECTOR;
typedef struct OBJ {
    char pad0[0x40]; int n40; char pad44[0x60 - 0x44];
    float g60; float g64; int n68; int pad6C; float g70; float g74; char pad78[8]; float g80;
    char pad84[0xD0 - 0x84]; VECTOR vD0; VECTOR vE0;
} OBJ;
extern float D_003457A8;
extern VECTOR D_0031FA00, D_0031FA10;
void func_001C7340(OBJ *p);
void func_00139740(OBJ *p)
{
    func_001C7340(p);
    p->n68 = 2;
    p->n40 = -1;
    p->g70 = 0.35f;
    p->g74 = 800.0f;
    p->g80 = D_003457A8;
    p->vD0 = D_0031FA00;
    p->vE0 = D_0031FA10;
    p->g64 = 1.0f;
    p->g60 = 1.0f;
}
