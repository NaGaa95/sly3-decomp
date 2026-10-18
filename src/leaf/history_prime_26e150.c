// SLY3_CFLAGS: -Os -G0 -ffast-math -fno-exceptions
typedef int Quad __attribute__((mode(TI)));
struct HistoryMatrix { Quad r[4]; };
struct HistorySample { float t; float g; char pad[8]; struct HistoryMatrix m; };
struct HistoryMethods { char pad[0x120]; short d; short pd; struct HistoryMatrix *(*matrix)(void *); };
struct HistoryOwner { char pad[0xC]; struct HistoryMethods *vt; char pad10[0x12C]; int count; struct HistorySample *array; int index; int idle; };
extern struct HistoryClock { float t; float dt; } D_0036BB98;
static inline int Wrap(int index, int count)
{
    return index % count;
}
void func_0026E150(struct HistoryOwner *p)
{
    float t = D_0036BB98.t;
    struct HistoryMatrix m = *p->vt->matrix((char *)p + p->vt->d);
    int n = p->count;
    int i = n + Wrap(0, n);
    t -= i * 0.016666668f;
    for (i--; i >= 0; i--) {
        struct HistorySample *e = &p->array[p->index];
        p->index = (p->index + 1) % p->count;
        e->t = t;
        e->g = 0.0f;
        t += 0.016666668f;
        e->m = m;
    }
    p->idle = 0;
}
