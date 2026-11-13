// SLY3_CFLAGS: -Os -G0
// func_001FCCE8: constructor of the emitter base object. It copies two default parameter blocks (0x60 and 0x90 bytes)
// into the object with func_001D24D0. The blocks are guarded function statics in the original (the guard words and the
// objects live at D_00468C50/D_00468BF0 and D_00468CF0/D_00468C60). They hold the non-constant vectors D_00317560,
// D_00317530 and D_00317550, so g++ builds each one in a memset stack temp and block-copies it into the static.
// The two unions in the second block (a CLQ g0 + x*(g1 + x*g2) and a float[4] view) are what orders the constant stores
// (store_constructor emits a clobber for a union initializer).
typedef int qword __attribute__((mode(TI)));

typedef union {
    struct { float g0, g1, g2, gUnused; } g;
    float ag[4];
} CLQ;

typedef union {
    struct { float g0, g4, g8, gC; } g;
    float ag[4];
} G4V;

typedef struct {
    qword first;
    int x10[8];
    qword second;
    int x40[4];
    short s50, s52;
    int x54[3];
} EMIT_DEFAULT_A;

typedef struct {
    int x00[2];
    float f08;
    int x0C;
    qword v10;
    float f20;
    int x24[3];
    CLQ clq30;
    G4V v40;
    int x50[6];
    float f68, f6C;
    int x70;
    float f74, f78;
    int x7C;
    short s80, s82;
    int x84[3];
} EMIT_DEFAULT_B;

typedef struct {
    int bytes, alignment;
} COPYREQ;

typedef struct {
    int word0, word4;
    short word8;
    unsigned char gapA[6];
    void *copyA, *copyB;
    void *tag;
} EMITBASE;

extern EMIT_DEFAULT_A D_00468BF0;
extern int D_00468C50;
extern EMIT_DEFAULT_B D_00468C60;
extern int D_00468CF0;
extern qword D_00317560, D_00317530, D_00317550;
extern unsigned char D_00361508[];
void *func_001D24D0(COPYREQ *request, void *source);

EMITBASE *func_001FCCE8(EMITBASE *self, int a, int b)
{
    self->tag = D_00361508;
    if (!D_00468C50) {
        D_00468BF0 = (EMIT_DEFAULT_A){ D_00317560, {0}, D_00317530, {0}, 1, 1 };
        D_00468C50 = 1;
    }
    if (!D_00468CF0) {
        D_00468C60 = (EMIT_DEFAULT_B){ {0}, -1500.0f, 0, D_00317550, 25.0f, {0},
                                       {{1.0f, 0.0f, -1.0f}}, {{750.0f, 750.0f}}, {0},
                                       -1.0f, 1.0f, 0, 1.0f, 1.0f, 0, 1, 1 };
        D_00468CF0 = 1;
    }
    self->word0 = a;
    self->word4 = b;
    self->word8 = 1;
    {
        COPYREQ request;
        request.bytes = 0x60;
        request.alignment = 0x10;
        self->copyA = func_001D24D0(&request, &D_00468BF0);
        request.bytes = 0x90;
        request.alignment = 0x10;
        self->copyB = func_001D24D0(&request, &D_00468C60);
    }
    return self;
}

