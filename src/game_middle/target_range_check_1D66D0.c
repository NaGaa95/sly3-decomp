// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int RangePacked __attribute__((mode(TI)));
struct RangeMethod { short delta, reserved; void *function; };
struct RangeTable { unsigned char prefix[0x120]; struct RangeMethod query; struct RangeMethod unusedSlot128; struct RangeMethod velocity; };
struct RangeObject { unsigned char prefix[0xC]; struct RangeTable *table; };
struct RangeSelf {
    unsigned char prefix0[0xC];
    struct RangeTable *table;
    unsigned char gap10[0x130 - 0x10];
    float minRange;
    float maxRange;
    unsigned char gap138[0x200 - 0x138];
    int state;
};
extern char D_00475480[];
struct RangeObject *func_001F4C40(void *game, RangePacked position);
float func_001205C8(RangePacked vector);
void func_001D6608(struct RangeSelf *self, float angle);

static inline RangePacked range_difference(RangePacked left, RangePacked right)
{
    RangePacked result;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(result) : "j"(left), "j"(right));
    return result;
}
static inline RangePacked range_dot(RangePacked a, RangePacked b)
{
    RangePacked product, one;
    __asm__("vmul.xyz %0,%2,%3
	vaddw.x %1,$vf0,$vf0w
	vadday.x $ACC,%0,%0y
	vmaddz.x %0,%1,%0z"
            : "=j"(product), "=&j"(one) : "j"(a), "j"(b));
    return product;
}
static inline RangePacked range_sqrt_x(RangePacked value)
{
    RangePacked root;
    __asm__("vsqrt $Q,%1x
	vwaitq
	vaddq.x %0,$vf0,$Q" : "=j"(root) : "j"(value));
    return root;
}
static inline RangePacked range_length(RangePacked a)
{
    return range_sqrt_x(range_dot(a, a));
}
static inline float range_x(RangePacked value)
{
    float x;
    __asm__("qmfc2.ni %0,%1" : "=r"(x) : "j"(value));
    return x;
}

int func_001D66D0(struct RangeSelf *self)
{
    RangePacked delta[1];
    RangePacked position;
    int result = self->state;
    struct RangeMethod *method = &self->table->query;
    struct RangeObject *other;
    float length;
    position = *(RangePacked *)((char *)((void *(*)(void *))method->function)((char *)self + method->delta) + 0x30);
    other = func_001F4C40(D_00475480, position);
    if (!other)
        return result;
    method = &other->table->query;
    delta[0] = range_difference(*(RangePacked *)((char *)((void *(*)(void *))method->function)((char *)other + method->delta) + 0x30), position);
    length = range_x(range_length(delta[0]));
    if (self->maxRange < length)
        return result;
    if (self->minRange < length) {
        method = &other->table->velocity;
        if (range_x(range_length(((RangePacked (*)(void *))method->function)((char *)other + method->delta))) < 150.0f)
            return result;
    }
    func_001D6608(self, func_001205C8(delta[0]));
    return 3;
}
