// Allocate one of the twelve original record kinds, initialize its dispatch pointer and type-specific fields.
// Native base constructor has a real receiver; allocator size is caller-derived and deliberately unused by the fixed pool helper.
// Bytes4..13 and unaccessed tails stay opaque; no virtual method signatures or external table bytes are invented.
// dispatch18 is the actual ABI data field; method asm name binds the original constructor, with no instruction assembly.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Actual base receiver and dispatch pointer at18; all12 source constructor sizes decoded from originals.
extern unsigned char D_00351CE8[];
extern unsigned char D_003511B8[];
extern unsigned char D_00351138[];
extern unsigned char D_00367C40[];
extern unsigned char D_003510F8[];
extern unsigned char D_003510B8[];
extern unsigned char D_00351078[];
extern unsigned char D_0035BAA0[];
extern unsigned char D_00351038[];
extern unsigned char D_00350FF8[];
extern unsigned char D_003534E0[];
extern unsigned char D_00351178[];
extern "C" void *func_0014BE38(unsigned int cb);
extern "C" void *func_00292034(void *pv, int b, unsigned int cb);
struct MATRIX4 {
    float m[4][4];
};
struct CBase {
    int k;
    unsigned char opaque4[0x10];
    int mode14;
    void *dispatch;
    CBase() asm("func_002BBC38");
    void *operator new(unsigned int cb) {
        return func_0014BE38(cb);
    }
};
struct C0 : CBase {
    unsigned char tail[16];
    C0() {
        dispatch = D_00351CE8;
        k = 0;
    }
};
struct C1 : CBase {
    int x;
    unsigned char tail[16];
    C1() {
        dispatch = D_003511B8;
        k = 1;
        x = 2;
    }
};
struct C2 : CBase {
    unsigned char tail[100];
    C2() {
        dispatch = D_00351138;
        k = 2;
    }
};
struct C3 : CBase {
    unsigned char tail[4];
    C3() {
        dispatch = D_00367C40;
        k = 3;
    }
};
struct C4 : CBase {
    unsigned char tail[12];
    C4() {
        dispatch = D_003510F8;
        k = 4;
    }
};
struct C5 : CBase {
    unsigned char tail[20];
    C5() {
        dispatch = D_003510B8;
        k = 5;
    }
};
struct C6 : CBase {
    unsigned char pad1C[4];
    MATRIX4 mat;
    C6() {
        dispatch = D_00351078;
        k = 6;
        MATRIX4 *pm = &mat;
        func_00292034(pm, 0, sizeof(*pm));
        pm->m[0][0] = pm->m[1][1] = pm->m[2][2] = pm->m[3][3] = 1.0f;
    }
};
struct C7 : CBase {
    unsigned char tail[4];
    C7() {
        dispatch = D_0035BAA0;
        k = 7;
    }
};
struct C8 : CBase {
    unsigned char tail[36];
    C8() {
        dispatch = D_00351038;
        k = 8;
    }
};
struct C9 : CBase {
    unsigned char tail[20];
    C9() {
        dispatch = D_00350FF8;
        k = 9;
        mode14 = 0x15;
    }
};
struct C10 : CBase {
    unsigned char tail[20];
    C10() {
        dispatch = D_003534E0;
        k = 10;
    }
};
struct C11 : CBase {
    unsigned char tail[68];
    C11() {
        dispatch = D_00351178;
        k = 11;
    }
};
extern "C" CBase *func_001306F0(int k);
CBase *func_001306F0(int k) {
    CBase *p;
    switch (k) {
        case 0: p = new C0;
        break;
        case 1: p = new C1;
        break;
        case 11: p = new C11;
        break;
        case 2: p = new C2;
        break;
        case 3: p = new C3;
        break;
        case 4: p = new C4;
        break;
        case 5: p = new C5;
        break;
        case 6: p = new C6;
        break;
        case 7: p = new C7;
        break;
        case 8: p = new C8;
        break;
        case 9: p = new C9;
        break;
        case 10: p = new C10;
        break;
        default: p = 0;
        break;
    }
    return p;
}
