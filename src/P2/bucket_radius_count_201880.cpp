// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
struct BucketChunk {
    qword points[2][0x84];
    int active;
    int count;
    unsigned char gap1088[8];
    BucketChunk *next;
};
struct BucketOwner { unsigned char prefix[0x50]; BucketChunk *first; };
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); }
};
extern "C" void func_002BC3D8(void *object, int flags);
struct BucketScope {
    qword pad;
    ~BucketScope() { func_002BC3D8(this, 2); }
};
static inline qword BucketDifference(qword left, qword right)
{
    qword result;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(result) : "j"(left), "j"(right));
    return result;
}
static inline qword BucketDot(qword value)
{
    qword product, one;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "=j"(product), "=&j"(one) : "j"(value));
    return product;
}
static inline float BucketFloat(qword bits)
{
    float value;
    __asm__("mtc1 %1,%0" : "=f"(value) : "r"(bits));
    return value;
}
static inline float BucketLow(qword value)
{
    float x;
    __asm__("qmfc2.ni %0,%1" : "=r"(x) : "j"(value));
    return x;
}
extern "C" int func_00201880(BucketOwner *self, qword point, float radius)
{
    VU_FLOAT limit(radius * radius);
    BucketScope scope;
    BucketChunk *chunk;
    int total = 0;
    for (chunk = self->first; chunk; chunk = chunk->next) {
        qword *p = chunk->points[chunk->active];
        int i;
        for (i = 0; i < chunk->count; i++) {
            if (BucketLow(BucketDot(BucketDifference(point, p[i]))) <= BucketFloat(limit.q))
                total++;
        }
    }
    return total;
}
