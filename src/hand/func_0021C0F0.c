// Sum the original ten-byte records, compare their stored identifier and checksum, and clear the expanded 0x6800-byte cache only when they change.
// Reference algorithm: src/hand/func_001D7C80.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct B { int c; unsigned char *pb; };
struct Q { char pad[0x6800]; int n5400; int n5404; };
void *func_00292034(void *p, int n, int cb);
static inline int Sum(unsigned int n, unsigned char *pb) { int sum = 0; while (n) { sum += *pb++; n--; } return sum; }
void func_0021C0F0(struct B *p, struct Q *q) {
    int sum = Sum(p->c * 10, p->pb);
    int n = *(unsigned short *)(p->pb + p->c * 10 - 6);
    if (n == q->n5400 && sum == q->n5404) return;
    func_00292034(q, 0, 0x6800);
    q->n5400 = n;
    q->n5404 = sum;
}
