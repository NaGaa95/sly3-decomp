// Sly 2 counterpart: sceGsResetGraph (decomp src/lib/sceGsResetGraph.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct {
    short sceGsInterMode;
    short sceGsOutMode;
    short sceGsFFMode;
    short sceGsVersion;
    int vsync_id;
    int handler_id;
} sceGsGParam;
sceGsGParam *func_0029F148(void);
int func_002939E0(unsigned long);
int func_00293D90(int);
int func_002933A0(int, int);
void func_002932A0(short, short, short);
void func_0029EFB8(short mode, short inter, short omode, short ffmode)
{
    sceGsGParam *gp;
    switch (mode) {
    case 0:
        gp = func_0029F148();
        *(volatile unsigned long *)0x12001000 = 0x200;
        gp->sceGsInterMode = inter;
        gp->sceGsOutMode = omode;
        gp->sceGsVersion = (*(volatile unsigned long *)0x12001000 >> 16) & 0xFF;
        func_002939E0(0xFF00);
        gp->sceGsFFMode = (ffmode != 0);
        if (gp->vsync_id) {
            func_00293D90(2);
            func_002933A0(2, gp->handler_id);
            gp->vsync_id = 0;
            gp->handler_id = 0;
        }
        func_002932A0(inter & 1, omode & 0xFF, ffmode & 1);
        break;
    case 1:
        *(volatile unsigned long *)0x12001000 = 0x100;
        break;
    case 5:
        gp = func_0029F148();
        gp->sceGsInterMode = inter;
        gp->sceGsOutMode = omode;
        gp->sceGsFFMode = (ffmode != 0);
        gp->sceGsVersion = (*(volatile unsigned long *)0x12001000 >> 16) & 0xFF;
        func_002932A0(inter & 1, omode & 0xFF, ffmode & 1);
        break;
    }
}
