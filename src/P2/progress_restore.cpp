// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct AssetRestoredProgress { unsigned int words[0x6808 / 4]; };
typedef char AssetRestoredProgressWidth[(sizeof(AssetRestoredProgress)==0x6808)?1:-1];
struct SESSION_MENU_SAVED { char prefix[0x1488]; int state,index,selected,parentSelected; };
extern "C" {
    extern unsigned int D_0036DBA8;
    extern unsigned char D_00468D30[], D_00375290[];
    extern SESSION_MENU_SAVED D_0036C700;
    void func_001CFDE8(void *save, int activity);
    void func_00185638(SESSION_MENU_SAVED *context);
    void func_0018AD58(void);
}

extern "C" void func_0018AC60(void)
{
    if (D_0036DBA8) {
        *reinterpret_cast<AssetRestoredProgress *>(D_00468D30) =
            *reinterpret_cast<AssetRestoredProgress *>(D_0036DBA8);
        func_001CFDE8(D_00375290, 0);
        D_0036DBA8 = 0;
        func_00185638(&D_0036C700);
        func_0018AD58();
    }
}
