// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int OriginVector __attribute__((mode(TI)));
typedef union { OriginVector raw; float lanes[4]; } OriginCarrier;
struct OriginMatrix { OriginVector rows[4]; };
struct OriginMethod { short delta, reserved; struct OriginMatrix *(*call)(void *); };
struct OriginObject {
    unsigned char unaccessed00[0xC];
    struct OriginMethod *methods;
    unsigned char unaccessed10[0xC4];
    struct OriginObject *related;
};
extern OriginVector D_00317550;
int func_0013B500(void *, int);
static inline struct OriginMatrix *origin_matrix(struct OriginObject *object)
{
    struct OriginMethod *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
static inline OriginVector origin_offset(OriginVector position)
{
    OriginCarrier scale;
    OriginVector result;
    float amount = 80.0f;
    __asm__("qmtc2.ni %1,%0" : "=j"(scale.raw) : "r"(amount));
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x"
            : "=j"(result) : "j"(position), "j"(D_00317550), "j"(scale.raw));
    return result;
}
OriginVector func_0016FD78(struct OriginObject *receiver)
{
    if (!receiver->related)
        return origin_matrix(receiver)->rows[3];
    if (func_0013B500(receiver->related, 0x3A))
        return origin_offset(origin_matrix(receiver->related)->rows[3]);
    return origin_matrix(receiver->related)->rows[3];
}
