// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
#include "heap_frame_api.h"
}
class PropertyReference {
public:
    CRef value;
    PropertyReference() { value.tag = -1; }
    PropertyReference(const PropertyReference &) __asm__("func_0012AF00");
    PropertyReference &operator=(const PropertyReference &) __asm__("func_0012B3B0");
    void Drop() __asm__("func_0012BC20");
    ~PropertyReference() { Drop(); }
};
class PropertyHeapFrame {
public:
    PropertyHeapFrame() __asm__("func_001D2770");
    ~PropertyHeapFrame() { func_001D2798(this,2); }
};
struct PropertyPath { int count; short *indices; };
struct PropertyTrie;
extern "C" {
extern PropertyTrie D_004793C8;
extern unsigned char D_00468D30[];
void func_00127220(ScriptNode *,PropertyPath *);
PropertyReference func_0021C338(PropertyTrie *,PropertyPath *,unsigned char *);
PropertyReference func_0021C528(PropertyTrie *,PropertyPath *,const CRef *,unsigned char *);
}

extern "C" PropertyReference func_001272E8(int unused_count,CRef *arguments,EvalFrame *unused_frame)
{
    PropertyReference result;
    PropertyHeapFrame frame;
    PropertyPath path;
    func_00127220((ScriptNode *)arguments[0].payload.pointer,&path);
    result = func_0021C338(&D_004793C8,&path,D_00468D30);
    return result;
}

extern "C" PropertyReference func_00127398(int unused_count,CRef *arguments,EvalFrame *unused_frame)
{
    PropertyReference result;
    PropertyHeapFrame frame;
    PropertyPath path;
    func_00127220((ScriptNode *)arguments[0].payload.pointer,&path);
    result = func_0021C528(&D_004793C8,&path,&arguments[1],D_00468D30);
    return result;
}
