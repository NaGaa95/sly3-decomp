// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern int D_0036B120;
extern "C" void func_0011C2E0(int *count,int *addressWord);
// The maintained helper returns the actual32-bit address as an integer word.
extern "C" void func_0011C268(int selection)
{
    if (selection==-1) {
        int count;
        int addressWord;
        func_0011C2E0(&count,&addressWord);
        D_0036B120=*(int *)addressWord;
    } else {
        D_0036B120=selection;
    }
}
