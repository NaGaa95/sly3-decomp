// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Allocator and callback registration table reconstructed from its original C++ initializer.
// Callback prototypes describe stored code addresses; this translation unit does not invoke them.
#include "heap.h"
inline CGlobalHeap::CGlobalHeap(int n) : m_n(n) {}
extern "C" byte D_0047AD10[];
extern "C" {
CLinearHeap D_0047A4A0(0x40000,D_0047AD10);
CGlobalHeap D_0047A4B0(-1);
}
struct POOLSTATE
{
    int cb;
    int c;
    int cbAlign;
    void *pv;
    int cAlloc;
    void *pvBlock;
    void *PvAlloc();
    void Reset();
    void Free(void *p);
    void WarmUp();
    POOLSTATE(int cb, int c, int cbAlign);
};

extern "C" int D_0036AE78, D_0036AE7C, D_0036AE80;
extern "C" int D_0036AE84, D_0036AE88, D_0036AE8C;
extern "C" POOLSTATE D_004D2AD8, D_004D2BB0, D_004D2C88;
extern "C" POOLSTATE D_004D2D60, D_004D2E38, D_004D2F10;
inline void *operator new(unsigned int cb, void *pv) { return pv; }
typedef void (*CALLBACK)();
extern "C" int D_00349CC8;
extern "C" void func_0017C730(void);
extern "C" void func_0017C7A8(void);
extern "C" void func_0017C848(void);
extern "C" void func_0017C8A8(void);
extern "C" void func_0017C950(void);
extern "C" void func_0017C9B0(void);
extern "C" void func_0017C9B8(void);
extern "C" void func_0017C9D8(void);
extern "C" void func_0017C9F8(void);
extern "C" void func_0017CA18(void);
extern "C" void func_0017CB18(void);
extern "C" void func_0017CBB0(void);
extern "C" void func_0017CC20(void);
extern "C" void func_0017CC88(void);
extern "C" void func_0017CDE0(void);
extern "C" void func_0017CFC0(void);
extern "C" void func_00186E28(void);
extern "C" void func_001A01F8(void);
extern "C" void func_001D1A70(void);
extern "C" void func_001D1AB0(void);
extern "C" void func_001D1B98(void);
extern "C" void func_001D1BF0(void);
extern "C" void func_001D1CC8(void);
extern "C" void func_001D1E60(void);
extern "C" void func_001D1EF8(void);
extern "C" void func_001F58E8(void);
extern "C" void func_0021A7B8(void);
extern "C" void func_0021A818(void);
extern "C" void func_002207E8(void);
extern "C" void func_002209E8(void);
extern "C" void func_00220A70(void);
extern "C" void func_00220AF0(void);
extern "C" void func_00220B70(void);
extern "C" void func_00220BF0(void);
extern "C" void func_00220C68(void);
extern "C" void func_00222140(void);
extern "C" void func_00222488(void);
extern "C" void func_002224E0(void);
extern "C" void func_00222588(void);
extern "C" void func_00222630(void);
extern "C" void func_00222690(void);
extern "C" void func_002226F0(void);
extern "C" void func_00222750(void);
extern "C" void func_00223078(void);
extern "C" void func_00223148(void);
extern "C" void func_0025EFF8(void);
extern "C" void func_0025F018(void);
extern "C" void func_0025F098(void);
extern "C" void func_0025F0E8(void);
extern "C" void func_0025F158(void);
extern "C" void func_0025F1D8(void);
extern "C" void func_0025F2E8(void);
extern "C" void func_0025F398(void);
extern "C" void func_0025F440(void);
extern "C" void func_0025F4F8(void);
extern "C" void func_0025F540(void);
extern "C" void func_0025F598(void);
extern "C" void func_0025F5C0(void);
extern "C" void func_0025F5E8(void);
extern "C" void func_0025F628(void);
extern "C" void func_0025F720(void);
extern "C" void func_00284F38(void);
extern "C" void func_00284FC8(void);
extern "C" void func_00285110(void);
extern "C" void func_00285198(void);
extern "C" void func_00285220(void);
struct CALLBACK_ENTRY { int id; CALLBACK pfn; int flags; };
// Of 178 records, record 112 reads its flags from the original runtime global.
extern "C" { CALLBACK_ENTRY D_0047A4B8[178] = {
    { 812,func_0025F0E8,0 },
    { 813,func_0025F098,0 },
    { 814,func_0025F158,0 },
    { 815,func_0025F440,0 },
    { 816,func_0025F440,1 },
    { 817,func_0025F440,2 },
    { 818,func_0025F440,3 },
    { 819,func_0025F440,4 },
    { 820,func_0025F440,5 },
    { 821,func_0025F440,6 },
    { 822,func_0025F440,7 },
    { 823,func_0025F440,8 },
    { 824,func_0025F440,9 },
    { 1468,func_0017C730,0 },
    { 1469,func_0017C730,1 },
    { 1470,func_0017C730,2 },
    { 1471,func_0017C730,3 },
    { 1472,func_0017C730,4 },
    { 1473,func_0017C730,5 },
    { 1474,func_0017C730,6 },
    { 1475,func_0017C730,7 },
    { 1476,func_0017C730,8 },
    { 1477,func_0017C730,9 },
    { 825,func_0025F1D8,0 },
    { 826,func_0025F2E8,0 },
    { 827,func_0025F2E8,1 },
    { 828,func_0025F398,0 },
    { 829,func_0025F398,1 },
    { 830,func_0025F398,2 },
    { 831,func_0025F398,3 },
    { 832,func_0025F398,4 },
    { 833,func_0025F398,5 },
    { 834,func_0025F4F8,0 },
    { 835,func_0025F4F8,1 },
    { 836,func_0025F4F8,2 },
    { 837,func_0025F4F8,3 },
    { 838,func_0025F4F8,4 },
    { 839,func_0025F4F8,5 },
    { 840,func_0025F4F8,6 },
    { 841,func_0025F4F8,7 },
    { 842,func_0025F4F8,8 },
    { 843,func_0025F4F8,9 },
    { 864,func_0025F540,864 },
    { 865,func_0025F540,865 },
    { 866,func_0025F540,866 },
    { 844,func_0025F598,0 },
    { 845,func_0025F5C0,0 },
    { 1115,func_002207E8,0 },
    { 1114,func_002207E8,0 },
    { 1225,func_002209E8,0 },
    { 1226,func_002209E8,1 },
    { 1227,func_002209E8,2 },
    { 1228,func_002209E8,3 },
    { 1229,func_002209E8,4 },
    { 1230,func_002209E8,5 },
    { 1231,func_00220A70,0 },
    { 1232,func_00220A70,1 },
    { 1233,func_00220A70,2 },
    { 1234,func_00220A70,3 },
    { 1235,func_00220A70,4 },
    { 1236,func_00220A70,5 },
    { 1219,func_00220BF0,0 },
    { 1218,func_00220C68,0 },
    { 1237,func_00220AF0,0 },
    { 1238,func_00220AF0,1 },
    { 1239,func_00220AF0,2 },
    { 1240,func_00220AF0,3 },
    { 1241,func_00220AF0,4 },
    { 1242,func_00220AF0,5 },
    { 1243,func_00220B70,0 },
    { 1244,func_00220B70,1 },
    { 1245,func_00220B70,2 },
    { 1246,func_00220B70,3 },
    { 1247,func_00220B70,4 },
    { 1248,func_00220B70,5 },
    { 846,func_0025F5E8,0 },
    { 1449,func_00222488,0 },
    { 1450,func_00222588,0 },
    { 1451,func_002224E0,0 },
    { 1452,func_00222630,0 },
    { 1453,func_00222630,1 },
    { 1454,func_00222630,2 },
    { 1455,func_00222630,3 },
    { 1456,func_00222630,4 },
    { 1457,func_00222630,5 },
    { 1458,func_00222630,6 },
    { 1459,func_00222630,7 },
    { 1460,func_00222630,8 },
    { 1461,func_00222630,9 },
    { 1462,func_00222690,0 },
    { 1463,func_00222690,1 },
    { 1464,func_00222690,2 },
    { 1465,func_00222690,3 },
    { 847,func_001D1A70,0 },
    { 848,func_001D1AB0,0 },
    { 1692,func_001D1B98,0 },
    { 1693,func_001D1BF0,0 },
    { 1694,func_001D1CC8,0 },
    { 1695,func_001D1E60,0 },
    { 1696,func_001D1EF8,0 },
    { 1697,func_001D1EF8,1 },
    { 1698,func_001D1EF8,2 },
    { 1700,func_00222140,0 },
    { 1704,func_002226F0,0 },
    { 1702,func_00222750,0 },
    { 1478,func_0017C7A8,0 },
    { 1479,func_0017C848,0 },
    { 1480,func_0017C8A8,0 },
    { 849,func_0025F628,0 },
    { 850,func_0025F720,0 },
    { 1481,func_0017C9B0,1 },
    { 1482,func_0017C9B0,0 },
    { 0x5CB,func_0025EFF8,D_00349CC8 },
    { 1110,func_00284F38,0 },
    { 1111,func_00284FC8,0 },
    { 1112,func_00285220,0 },
    { 851,func_00186E28,0 },
    { 1960,func_0021A7B8,0 },
    { 1961,func_0021A7B8,1 },
    { 1962,func_0021A7B8,2 },
    { 1963,func_0021A7B8,3 },
    { 1964,func_0021A818,0 },
    { 1965,func_0025F018,4691776 },
    { 1966,func_0025F018,4691780 },
    { 1010,func_001A01F8,1010 },
    { 1011,func_001A01F8,1011 },
    { 1013,func_001A01F8,1013 },
    { 1014,func_001A01F8,1014 },
    { 1015,func_001A01F8,1015 },
    { 1012,func_0025F018,4691784 },
    { 1016,func_001A01F8,1016 },
    { 1017,func_001A01F8,1017 },
    { 1018,func_001A01F8,1018 },
    { 1019,func_001A01F8,1019 },
    { 1020,func_001A01F8,1020 },
    { 1021,func_001A01F8,1021 },
    { 1022,func_001A01F8,1022 },
    { 1023,func_001A01F8,1023 },
    { 1024,func_001A01F8,1024 },
    { 1025,func_001A01F8,1025 },
    { 1026,func_001A01F8,1026 },
    { 1027,func_001A01F8,1027 },
    { 1028,func_001A01F8,1028 },
    { 1029,func_001A01F8,1029 },
    { 1030,func_001A01F8,1030 },
    { 1031,func_001A01F8,1031 },
    { 1032,func_001A01F8,1032 },
    { 1033,func_001A01F8,1033 },
    { 1034,func_001A01F8,1034 },
    { 1035,func_001A01F8,1035 },
    { 917,func_001F58E8,0 },
    { 918,func_001F58E8,1 },
    { 919,func_001F58E8,2 },
    { 920,func_001F58E8,3 },
    { 921,func_001F58E8,4 },
    { 922,func_001F58E8,5 },
    { 923,func_001F58E8,6 },
    { 924,func_001F58E8,7 },
    { 925,func_001F58E8,8 },
    { 926,func_001F58E8,9 },
    { 927,func_001F58E8,10 },
    { 928,func_001F58E8,11 },
    { 929,func_001F58E8,12 },
    { 852,func_00223078,0 },
    { 853,func_00223148,0 },
    { 1484,func_0017C9B8,0 },
    { 1485,func_0017C9D8,0 },
    { 1486,func_0017C9F8,0 },
    { 1487,func_0017CA18,0 },
    { 1488,func_0017CB18,0 },
    { 1489,func_0017CBB0,0 },
    { 1490,func_0017CC20,0 },
    { 1491,func_0017CC88,0 },
    { 1498,func_0017CDE0,0 },
    { 999,func_00285110,0 },
    { 998,func_00285198,0 },
    { 1499,func_0017C950,0 },
    { 1500,func_0017CFC0,0 }
}; }
template<int cb, int c, int *pcRef, POOLSTATE *pstate>
class CPoolRef
{
public:
    CPoolRef()
    {
        if (++*pcRef == 1)
            new (pstate) POOLSTATE(cb, c, 16);
    }
};

CPoolRef<16, 2048, &D_0036AE78, &D_004D2AD8> g_ref16;
CPoolRef<24, 1024, &D_0036AE7C, &D_004D2BB0> g_ref24;
CPoolRef<24, 256, &D_0036AE80, &D_004D2C88> g_ref24Small;
CPoolRef<28, 1024, &D_0036AE84, &D_004D2D60> g_ref28;
CPoolRef<12, 256, &D_0036AE88, &D_004D2E38> g_ref12;
CPoolRef<24, 256, &D_0036AE8C, &D_004D2F10> g_ref24Other;

