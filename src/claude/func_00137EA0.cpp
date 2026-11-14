// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Port of Sly 2 UpdateAsegaIeaCur: real loops re-reading pasega->paseg; '== 0' keeps fast-math from folding the test.
struct EA { float t; int pad[4]; };
struct ASEG { char pad[0x90]; int cea; EA *aea; };
struct ASEGA { char pad[0x14]; ASEG *paseg; char pad2[4]; float t; char pad3[0x40 - 0x20]; float svt; char pad4[0x50 - 0x44]; int ieaCur; };
extern "C" void func_00137EA0(ASEGA *pasega);
void func_00137EA0(ASEGA *pasega)
{
    ASEG *paseg = pasega->paseg;
    int cea = paseg->cea;
    int iea;
    if (cea == 0)
        return;
    if (pasega->svt >= 0.0f) {
        for (iea = 0; iea < pasega->paseg->cea; iea++)
            if (pasega->t <= pasega->paseg->aea[iea].t)
                break;
        pasega->ieaCur = iea;
    } else {
        iea = cea;
        do
            iea--;
        while (iea >= 0 && (pasega->paseg->aea[iea].t <= pasega->t) == 0);
        pasega->ieaCur = iea + 1;
    }
}
