// Per-frame update of the dialog: prime the sub-panel on first use (with its state specific hint sound), then map the pad buttons to state changes and refresh the panel.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct { short d; short pad; void *pfn; } VTE;
typedef struct Sub {
    char pad0[0xC];
    VTE *vt;
    char pad10[0x48 - 0x10];
    int count;
} Sub;
typedef struct Dialog {
    char pad0[0xC];
    VTE *vt;
    char pad10[0x1C - 0x10];
    void *controller;
    char pad20[0x34 - 0x20];
    Sub *sub;
    char pad38[0x50 - 0x38];
    int state;
    char pad54[4];
    int count;
    char pad5C[0x124 - 0x5C];
    int flag;
} Dialog;
typedef struct { char pad[0x50]; int value; } Probe;
extern char D_004BC230[];
extern Probe *D_004BC244;
void func_0021EBE0(Dialog *);
int func_00260D10(void);
void func_00261070(Sub *, int);
void func_00261050(Sub *, int);
int func_002852B0(void *);
int func_002835D0(Probe *);
void func_00262450(Sub *, int);
int func_001A7A80(void *, int, float);
void func_002214F0(Dialog *, int);
void func_0021EC30(Dialog *);
void func_00221400(Dialog *);
#define VCALL(o, n) ((void (*)(void *))(o)->vt[n].pfn)((char *)(o) + (o)->vt[n].d)
void func_00220E80(Dialog *self)
{
    func_0021EBE0(self);
    if (self->state == -1) return;
    if (!self->controller) return;
    if (!self->sub->count) {
        if (!func_00260D10()) return;
        func_00261070(self->sub, 1);
        func_00261050(self->sub, 2);
        VCALL(self->sub, 18);
        switch (self->state) {
        case 1:
            if (!func_002852B0(D_004BC230))
                func_00262450(self->sub, 0x576);
            break;
        case 2: {
            int probe = D_004BC244 ? D_004BC244->value : -1;
            if (probe == 0)
                func_00262450(self->sub, func_002835D0(D_004BC244) ? 0x5D5 : 0x5D6);
            break;
        }
        }
    }
    if (func_001A7A80(self->controller, 0x800, 0.0f)) {
        func_002214F0(self, -1);
        return;
    }
    switch (self->state) {
    case 0:
        if (func_001A7A80(self->controller, 0x10, 0.0f)) {
            func_002214F0(self, -1);
            return;
        }
        if (self->count && func_001A7A80(self->controller, 0xF0, 0.0f)) {
            func_002214F0(self, 1);
            return;
        }
        break;
    case 1:
        if (!self->flag && func_001A7A80(self->controller, 0x10, 0.0f)) {
            func_002214F0(self, -1);
            return;
        }
        if (!func_002852B0(D_004BC230) && func_001A7A80(self->controller, 0xF0, 0.0f)) {
            func_002214F0(self, 0);
            return;
        }
        break;
    case 2:
        if (func_001A7A80(self->controller, 0x10, 0.0f)) {
            func_002214F0(self, -1);
            return;
        }
        break;
    }
    func_0021EC30(self);
    func_00221400(self);
}
