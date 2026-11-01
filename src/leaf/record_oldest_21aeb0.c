// Find a free record in the pool, or else the record with the oldest time stamp (older than one time unit ago); returns null when the pool is empty.
// SLY3_CFLAGS: -Os -G0 -ffast-math
struct Rec { void *handle; float time; int pad; };
struct Pool { char pad[0x4C]; int count; struct Rec *recs; };
extern float D_0036BB98;
struct Rec *func_0021AEB0(struct Pool *p) {
    float oldest = D_0036BB98 - 1.0f;
    struct Rec *best = 0;
    int i = 0;
    struct Rec *r;
    goto test;
next:
    i++;
test:
    if (i >= p->count) goto done;
    r = &p->recs[i];
    if (r->handle == 0) goto found;
    if (best != 0 && best->handle == 0) goto next;
    if (oldest <= r->time) goto next;
    oldest = r->time; best = r;
    goto next;
found:
    best = r;
done:
    return best;
}
