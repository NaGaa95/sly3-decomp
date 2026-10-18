// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class QueryReference {
public:
    CRef value;
    QueryReference() { value.tag=-1; }
    QueryReference(const QueryReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~QueryReference() { Drop(); }
};
struct ReferenceContext { char prefix[4]; EvalFrame *frame; };
struct Property;
extern "C" {
Property *func_00249CF8(ReferenceContext *,int);
QueryReference func_00249D98(ReferenceContext *,Property *);
int func_0012C7D0(EvalFrame *,int,CRef *);
QueryReference func_0024AB90(ReferenceContext *context,int key)
{
    if(key<0x718)
        return func_00249D98(context,func_00249CF8(context,key));
    QueryReference reference;
    func_0012C7D0(context->frame,key,&reference.value);
    return reference;
}
}
typedef char OwningReferenceSize[(sizeof(QueryReference)==8)?1:-1];
