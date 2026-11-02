// SLY3_CFLAGS: -Os -G0 -ffast-math
// Find the entry of a candidate list that scores best (smallest value) against the query, copy it to *out and remove it
// from the list; returns 0 when the list yields no candidate.
typedef int qword __attribute__((mode(TI)));
struct Entry { qword a, b; };
struct List { int x0; int count; int pad[2]; struct Entry e[1]; };
struct Object;
extern char D_00475480[];
int func_0017E208(void *game, int a, int b, int c, int max, struct Object **out);
float func_001C07E8(struct List *list, struct Entry *e, void *query, int n, struct Object **objects);
void func_00291F38(void *dst, void *src, int n);
static inline void MoveEntries(struct Entry *dest, struct Entry *src, unsigned size)
{
    func_00291F38(dest, src, size);
}
int func_001C0B70(struct List *list, struct Entry *out, void *query)
{
    struct Object *objects[16];
    struct Entry *e;
    int n, best, i;
    float bestScore;
    n = func_0017E208(D_00475480, 0x505, 0x32, 0, 16, objects);
    bestScore = 3.4028235e+38f;
    best = -1;
    i = 0;
    e = list->e;
    for (; i < list->count; e++, i++) {
        float score = func_001C07E8(list, e, query, n, objects);
        if (score < bestScore) {
            bestScore = score;
            best = i;
            *out = *e;
            if (bestScore == 0.0f)
                break;
        }
    }
    if (best == -1)
        return 0;
    MoveEntries(&list->e[best], &list->e[best + 1], (list->count - best) * sizeof(struct Entry) - sizeof(struct Entry));
    list->count--;
    return 1;
}
