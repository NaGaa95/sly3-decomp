// SLY3_AS: gnu-2.9
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Moves the event cursor of an actor to event `id` (same routine as Sly 2 func_001BAF18): 0x6DA = start, 0x6DB = end, -1 =
// stay, otherwise the event with that id. Going forward plays the item lists of the events passed, going backward undoes
// them in reverse order (the sound start/stop and the paired item kinds are swapped).
typedef struct VTE { short d; short pad; void (*pfn)(); } VTE;
typedef struct SO { char pad[0xC]; VTE *vt; } SO;
typedef struct I { int kind; int value; } I;
typedef struct E { int id; int unknown4; int actionCount; I *actions; } E;
typedef struct P {
    char pad0[0x138];
    int marker;
    int current;
    int eventCount;
    E *events;
} P;
extern char D_00475480[];
SO *func_0017E1B8(void *g, int k, int v, P *p);
void func_0023FE38(P *p, int v);
void func_0023FEC0(P *p, int v);
void func_00240000(P *p, int v);
void func_00240080(P *p, int v);

void func_001E50B0(P *p, int id)
{
    int iTarget = p->current;
    int cur, j, k;

    if (id == 0x6DA) {
        iTarget = 0;
    } else if (id == 0x6DB) {
        iTarget = p->eventCount;
    } else if (id != -1) {
        for (j = 0; j < p->eventCount; j++) {
            if (p->events[j].id == id) {
                iTarget = j;
                break;
            }
        }
    }
    cur = p->current;
    if (p->current == iTarget) return;
    if (p->current < iTarget) {
        do {
            E *pe;
            p->current = cur + 1;
            pe = &p->events[cur];
            for (k = 0; k < pe->actionCount; k++) {
                I *pi = &pe->actions[k];
                SO *ps = 0;
                if ((0x43 >> pi->kind) & 1) {
                    ps = func_0017E1B8(D_00475480, 1, pi->value, p);
                    if (!ps) continue;
                }
                switch ((unsigned int)pi->kind) {
                case 0:
                    ((void (*)(void *))ps->vt[8].pfn)((char *)ps + ps->vt[8].d);
                    break;
                case 1:
                    ((void (*)(void *))ps->vt[9].pfn)((char *)ps + ps->vt[9].d);
                    break;
                case 2:
                    func_0023FE38(p, pi->value);
                    break;
                case 3:
                    func_0023FEC0(p, pi->value);
                    break;
                case 4:
                    func_00240000(p, pi->value);
                    break;
                case 5:
                    func_00240080(p, pi->value);
                    break;
                }
            }
            cur = p->current;
        } while (cur < iTarget);
        p->marker = 0;
    } else if (iTarget < p->current) {
        do {
            E *pe;
            p->current--;
            pe = &p->events[p->current];
            k = pe->actionCount;
            while (k-- > 0) {
                I *pi = &pe->actions[k];
                SO *ps = 0;
                if ((0x43 >> pi->kind) & 1) {
                    ps = func_0017E1B8(D_00475480, 1, pi->value, p);
                    if (!ps) continue;
                }
                switch ((unsigned int)pi->kind) {
                case 0:
                    ((void (*)(void *))ps->vt[9].pfn)((char *)ps + ps->vt[9].d);
                    break;
                case 1:
                    ((void (*)(void *))ps->vt[8].pfn)((char *)ps + ps->vt[8].d);
                    break;
                case 2:
                    func_0023FEC0(p, pi->value);
                    break;
                case 3:
                    func_0023FE38(p, pi->value);
                    break;
                case 4:
                    func_00240080(p, pi->value);
                    break;
                case 5:
                    func_00240000(p, pi->value);
                    break;
                }
            }
        } while (iTarget < p->current);
        p->marker = 0;
    } else {
        p->marker = 0;
    }
}
