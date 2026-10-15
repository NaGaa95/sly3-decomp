// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" void func_0011C2E0(int *count,int *addressWord);
extern "C" void func_0011C268(int selection);
extern "C" void func_0011C438(unsigned int OSselection)
{
    int mapping[15]={1,1,2,5,4,3,7,6,-1,-1,-1,-1,0,-1,-1};
    for (int i=0;i<15;i++) {
        if (OSselection==(unsigned int)mapping[i]) {
            int count;
            int addressWord;
            func_0011C2E0(&count,&addressWord);
            for (int j=0;j<count;j++) {
                if (i==((int *)addressWord)[j]) {
                    func_0011C268(i);
                    return;
                }
            }
        }
    }
    func_0011C268(-1);
}
