// Sly 2 reference: src/hand/SyncVBlank__Fv.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
extern int D_0036E690;
extern int D_0036E69C;
extern "C" void func_002936E0(int sid) __asm__("func_002936E0");
void SyncVBlank() __asm__("func_00195688");
void SyncVBlank()
{
    D_0036E69C = 1;
    func_002936E0(D_0036E690);
}
