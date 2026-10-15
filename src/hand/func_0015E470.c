// Advance the five actual controller states until unchanged or externally suspended.
// The five-entry GNU C label table has the original eight-byte alignment; no neighboring constants are emitted.
// Actor peer+3AC, nullable request argument and cached resource are real pointers proved by complete producers/consumers.
// SLY3_CFLAGS: -Os -G0
// Explicit real Actor pointers and nullable request pointer; actual cached pointer107C producer256828 and dereferencing consumer15F050 prove returnedpointer/receiver44 store.
struct ACTOR {
    char opaque0[0x3AC];
    struct ACTOR *peer3AC;
};
struct P {
    char pad[0x10];
    struct ACTOR *x10;
    char opaque14[4];
    void *x18;
    char pad2[0x30 - 0x1C];
    int state;
    char opaque34[8];
    int desiredIndex;
    int candidateIndex;
    void *pendingResource;
};
void func_002389A0(void);
void func_0015E690(struct P *p);
int func_00238AA8(struct P *p);
int func_00254B80(void *p);
int func_0015E628(struct P *p);
int func_0015EC20(struct P *p);
void *func_001A3BA8(struct ACTOR *, struct ACTOR *, void *);
void func_0015F050(struct P *p, int k);
void func_0015EF88(struct P *p);
int func_001D8AC0(void *p);
int func_00238AD0(struct P *p);
void func_0015E470(struct P *p) {
    int s;
    func_002389A0();
    func_0015E690(p);
    for (;;) {
        if (func_00238AA8(p)) break;
        s = p->state;
        {
            static void *const labels[5] __attribute__((aligned(8))) = {
                &&state_0,&&state_1,&&state_2,&&state_3,&&state_4
            };
            if ((unsigned)s >= 5) goto state_done;
            goto *labels[s];
            state_0: if (func_00254B80(p->x10)) {
                func_0015F050(p, 4);
            }
            else if (func_0015E628(p)) {
                func_0015F050(p, 2);
            }
            else {
                int v = func_0015EC20(p);
                p->candidateIndex = v;
                if (v == p->desiredIndex) {
                    void *r = func_001A3BA8(p->x10, p->x10->peer3AC, 0);
                    p->pendingResource = r;
                    if (r) func_0015F050(p, 3);
                }
                else {
                    func_0015EF88(p);
                }
            }
            goto state_done;
            state_1: if (func_00254B80(p->x10)) func_0015F050(p, 4);
            else if (func_0015E628(p)) func_0015F050(p, 2);
            else if (func_001D8AC0(p->x18)) func_0015F050(p, 0);
            else func_001A3BA8(p->x10, p->x10->peer3AC, 0);
            goto state_done;
            state_2: if (func_00254B80(p->x10)) func_0015F050(p, 4);
            else if (func_00238AD0(p)) func_0015F050(p, 0);
            goto state_done;
            state_3: if (func_00254B80(p->x10)) func_0015F050(p, 4);
            else if (func_00238AD0(p)) func_0015F050(p, 0);
            goto state_done;
            state_4: if (!func_00254B80(p->x10)) func_0015F050(p, 0);
            goto state_done;
            state_done:;
        }
        if (s == p->state) break;
    }
}
