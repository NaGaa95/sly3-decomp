// SLY3_CFLAGS: -Os -G0 -fno-exceptions
typedef int QueryPackedWord __attribute__((mode(TI)));
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
struct VectorQueryFrame;
struct VectorQueryPosition { unsigned char prefix[0x80]; QueryPackedWord position; };
struct VectorQueryObject { unsigned char prefix[0xD8]; VectorQueryPosition *transform; };
struct VectorQueryWrapper { unsigned char prefix[4]; VectorQueryObject *object; };
union VectorQueryCarrier {
    struct { float xyz[3]; unsigned char unassigned_wordC[4]; } value;
    QueryPackedWord packed;
};
extern "C" CRef func_0012BAE8(CRef *reference);
extern "C" QueryPackedWord func_00212480(QueryPackedWord first,QueryPackedWord second,
                                         QueryPackedWord position,float parameter);
extern "C" CRef func_00124958(int unused_count,CRef *arguments,VectorQueryFrame *unused_frame)
{
    VectorQueryCarrier position;
    position.value.xyz[0]=0.0f;
    position.value.xyz[1]=0.0f;
    position.value.xyz[2]=-1750.0f;
    if(arguments[3].tag) {
        VectorQueryObject *object=((VectorQueryWrapper *)arguments[3].payload.pointer)->object;
        if(object && object->transform)
            position.packed=object->transform->position;
    }
    CRef result(0x18);
    QueryPackedWord *output=(QueryPackedWord *)result.payload.pointer;
    *output=func_00212480(*(QueryPackedWord *)arguments[0].payload.pointer,
                        *(QueryPackedWord *)arguments[1].payload.pointer,
                        position.packed,func_0012BAE8(&arguments[2]).payload.real);
    return result;
}
