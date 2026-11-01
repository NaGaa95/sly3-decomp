// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct DL { void *head, *tail; int offset; };
struct DLI { DL *list; void **next; int offset; DLI *outer; };
struct ENTRY { int a, b, c; };
struct TYPE { char pad[0xA4]; int g; };
struct SHAPE { TYPE *type; char pad4[0x14]; unsigned long flags; char pad20[0x5C]; int capacity; char pad7C2[4]; void *tree; char pad88[0x38]; int link; };
struct XP { qword position, other, normal; char pad30[0x10]; float fraction; char pad44[0x1C]; };
struct RVE { short delta, pad; int (*fn)(void *, SHAPE *, qword, qword, qword); };
struct RIP { char pad0[0x14]; float start; char pad18[0x58]; qword position; qword extra; char pad90[0x58]; RVE *vt; };
struct NODE;
struct STATE { char pad0[0x20]; qword origin; float radius; DL shapes; char pad40[0x20]; void *subject; NODE *nodes; char pad68[8]; unsigned long flags; };
struct OBJ { char padDC[0xDC]; STATE *state; };
struct NODE { int pad; NODE *next; char pad8[4]; OBJ *object; };
struct PVE { short delta, pad; void (*fn)(void *); };
struct P { char padC[0xC]; PVE *vt; char pad10[0xCC]; STATE *state; char padE0[0x50]; int mode; DL rips; };
struct CLOCK { float t, dt; };
struct REQ { int cb, align; };
struct FRAME { int a[4]; };
extern "C" {
extern DLI *D_0036AE94;
extern CLOCK D_0036BB98;
FRAME *func_001D2770(FRAME *);
void func_001D2798(FRAME *, int);
void *func_001D25B0(const REQ *);
int func_00119C20(void *, int, qword, float, int *, ENTRY **);
int func_00164A98(SHAPE *, ENTRY *, qword, qword, int, XP *);
int func_0013B500(void *, int);
void func_0018B1E0(SHAPE *);
int func_0011B0F0(DL *);
void func_0020B578(P *);
}
union PHASE { REQ request; DLI rip; };
static inline void Init(DLI *it, DL *list) { it->list = list; it->next = (void **)list; it->offset = list->offset; it->outer = D_0036AE94; D_0036AE94 = it; }
static inline void *Next(DLI *it) { void *p = *it->next; it->next = (void **)((char *)p + it->offset); return p; }
static inline void SetAlign(REQ *r, int a) { r->align = a; }
static inline int Min(int a, int b) { return a <= b ? a : b; }
extern "C" void func_0020B578(P *p)
{
    if (p->mode == 1) {
        NODE *node;
        for (node = p->state->nodes; node; node = node->next) {
            if (node->object->state->flags & 4) continue;
            int special = func_0013B500(node->object->state->subject, 0x65);
            DLI shapes;
            Init(&shapes, &node->object->state->shapes);
            SHAPE *shape;
            while ((shape = (SHAPE *)Next(&shapes)) != 0) {
                if ((shape->flags & 0x10000) && !special) continue;
                {
                    FRAME frame;
                    func_001D2770(&frame);
                    PHASE phase;
                    XP contacts[4];
                    int remaining;
                    ENTRY *entries;
                    entries = 0;
                    if (!(shape->flags & 0x20000)) {
                        remaining = Min(0x1555, shape->capacity);
                        phase.request.cb = remaining * 12;
                        SetAlign(&phase.request, 16);
                        entries = (ENTRY *)func_001D25B0(&phase.request);
                        if (shape->link != shape->type->g) func_0018B1E0(shape);
                        if (func_00119C20(shape->tree, 0x7FFFFFFF, p->state->origin, p->state->radius, &remaining, &entries) != 2) {
                            func_001D2798(&frame, 2);
                            continue;
                        }
                        entries--;
                    }
                    Init(&phase.rip, &p->rips);
                    RIP *rip;
                    for (rip = (RIP *)Next(&phase.rip); rip; rip = (RIP *)Next(&phase.rip)) {
                        if (D_0036BB98.t <= rip->start) continue;
                        int count = func_00164A98(shape, entries, rip->extra, rip->position, 4, contacts);
                        int i = 0;
                        if (i < count) do {
                            XP *hit = &contacts[i];
                            if (hit->fraction != 0.0f && rip->vt[7].fn((char *)rip + rip->vt[7].delta, shape, hit->position, hit->normal, rip->position)) break;
                            i++;
                        } while (i < count);
                    }
                    D_0036AE94 = phase.rip.outer;
                    func_001D2798(&frame, 2);
                }
            }
            D_0036AE94 = shapes.outer;
        }
        if (func_0011B0F0(&p->rips)) p->vt[9].fn((char *)p + p->vt[9].delta);
    }
}
