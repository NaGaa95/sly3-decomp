// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions
typedef int OrientationPackedWord __attribute__((mode(TI)));
class CRef {
public:
    short tag,word2;
    union { int word; float real; void *pointer; } payload;
    CRef(int kind) { InitTag(kind); }
    CRef(const CRef &);
    void InitTag(int kind);
    void Decref();
    ~CRef() { Decref(); }
};
struct OrientationRow { float xyz[3]; unsigned int raw_w; } __attribute__((aligned(16)));
struct OrientationMatrix { OrientationRow rows[3]; };
struct OrientationUpReference { unsigned char prefix[4]; OrientationPackedWord *vector; };
extern OrientationPackedWord D_00317550;
extern "C" OrientationMatrix func_0011CBF0(OrientationPackedWord direction,
                                           OrientationPackedWord up);
static inline OrientationPackedWord Difference(OrientationPackedWord *second,
                                               OrientationPackedWord *first)
{
    OrientationPackedWord a=*first;
    OrientationPackedWord b=*second;
    asm("vsub.xyzw %0,%0,%1" : "+j"(b) : "j"(a));
    return b;
}
extern "C" CRef func_00124F28(int unused_count,CRef *arguments,void *unused_frame)
{
    OrientationPackedWord *up;
    if(arguments[2].tag==0)
        up=&D_00317550;
    else
        up=((OrientationUpReference *)arguments[2].payload.pointer)->vector;
    union { OrientationPackedWord packed; } direction;
    direction.packed=Difference((OrientationPackedWord *)arguments[1].payload.pointer,
                                (OrientationPackedWord *)arguments[0].payload.pointer);
    CRef result(0x19);
    OrientationMatrix *matrix=(OrientationMatrix *)result.payload.pointer;
    *matrix=func_0011CBF0(direction.packed,*up);
    matrix->rows[2].raw_w=0;
    matrix->rows[1].raw_w=0;
    matrix->rows[0].raw_w=0;
    return result;
}
