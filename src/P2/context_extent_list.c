// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct SentinelExtentView {
    char prefix[0x1A8];
    float extent;
};

void func_001C7DC8(void *receiver);
float func_0022F998(void *receiver);

void func_00203638(void *receiver) {
    struct SentinelExtentView *p = (struct SentinelExtentView *)receiver;
    int unresolved;

    func_001C7DC8(receiver);
    unresolved = 1;
    if (p->extent != 1250.0f)
        unresolved = 0;
    if (unresolved != 0)
        p->extent = func_0022F998(receiver) + 1250.0f;
}

typedef struct DL { void *pvFirst; void *pvLast; int ibDle; } DL;
extern unsigned char D_00475480[];
void func_0011AF60(DL *list, void *owner);
void func_0011B028(DL *list, void *owner);

void func_002036A0(void *owner) {
    func_0011AF60((DL *)(D_00475480 + 0x4670), owner);
}

void func_002036C8(void *owner) {
    func_0011B028((DL *)(D_00475480 + 0x4670), owner);
}
