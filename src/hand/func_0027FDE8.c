// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct G;
extern struct G D_00475480;
extern char D_00389AC0[];
struct CLOCK {
    float t;
    float timeout184;
};
extern struct CLOCK D_0036BB98;
struct RECORD64 {
    char opaque[64];
};
struct STATE_VIEW {
    char pad[0xDC];
    struct BSP_NODE *volumeDC;
    char pad1[0x128-0xE0];
    int state;
    float stateStartTime;
    char request130[64];
    int recordCount;
    struct RECORD64 *records;
    int option178;
    int requestIndex17C;
    float deadline180;
    float timeout184;
};
void func_001C8168(struct STATE_VIEW *p);
void func_001DBD08(void *records, struct RECORD64 *b);
void func_00289070(struct G *p, void *records, int b, int recordCount, int d);
void *func_001F4AD0(struct G *pg, int slot);
struct MATRIX4 {
    qword row[4];
};
typedef char MatrixPrefix64[(sizeof(struct MATRIX4) == 64) ? 1 : -1];
typedef char StatePrefix188[(sizeof(struct STATE_VIEW) == 0x188) ? 1 : -1];

struct VE {
    short delta,padding;
    const struct MATRIX4 *(*matrix)(void *);
};
struct MATRIX_OWNER {
    char prefix[12];
    struct VE *table;
};
static __inline__ qword Position(void *p) {
    struct MATRIX_OWNER *owner=p;
    struct VE *entry=&owner->table[36];
    return entry->matrix((char *)p+entry->delta)->row[3];
}
qword func_001C9428(void *source, struct STATE_VIEW *p, qword q);
struct BSP_NODE;
struct BSP_NODE *func_00119C90(struct BSP_NODE *p, unsigned int limit, qword q);
void func_0027FC08(struct STATE_VIEW *p, int state);
void func_0027FCC8(struct STATE_VIEW *p);
void func_0027FDE8(struct STATE_VIEW *p) {
    func_001C8168(p);
    switch (p->state) {
        case 4: if (0.0f < p->deadline180 && p->deadline180 <= D_0036BB98.t) {
            int i;
            for (i = 0; i < p->recordCount; i++) func_001DBD08(D_00389AC0, &p->records[i]);
            func_00289070(&D_00475480, p->request130, p->option178, 0, p->requestIndex17C);
            p->deadline180 = 0.0f;
            func_0027FC08(p, 5);
        }
        break;
        case 0: case 1: case 3: {
            void *pj = func_001F4AD0(&D_00475480, 0);
            union {
                qword q;
            }
            u;
            int f;
            if (!pj) return;
            u.q = func_001C9428(0, p, Position(pj));
            f = func_00119C90(p->volumeDC, 0x7FFFFFFF, u.q) != 0;
            switch (p->state) {
                case 3: if (f) func_0027FCC8(p);
                break;
                case 1: if (f) func_0027FC08(p, 0);
                else if (D_0036BB98.t - p->stateStartTime > p->timeout184) func_0027FC08(p, 3);
                break;
                case 0: if (!f) func_0027FC08(p, 1);
                break;
            }
            break;
        }
        case 2: break;
    }
}
