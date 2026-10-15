// Check the ten-byte record block identifier and byte checksum against the original expanded cache fields.
// Reference algorithm: src/hand/func_001D7D30.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct B { int c; unsigned char *pb; };
struct Q { char pad[0x6800]; int n5400; int n5404; };
static inline int Sum(unsigned int n, unsigned char *pb) { int sum = 0; while (n) { sum += *pb++; n--; } return sum; }
int func_0021C198(struct B *p, struct Q *q) {
    int sum = Sum(p->c * 10, p->pb);
    return *(unsigned short *)(p->pb + p->c * 10 - 6) == q->n5400 && sum == q->n5404;
}
