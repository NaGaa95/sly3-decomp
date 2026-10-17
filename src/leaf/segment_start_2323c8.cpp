// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct LookupNode;
struct SegmentOwner { unsigned char prefix[0x130]; void *root; void *segment; unsigned char segmentState[8]; void *lookupOwner; LookupNode *receiver; unsigned char gap148[0x28]; int sourceMode; int mode; unsigned char gap178[4]; float time; };
extern "C" {
void func_001FC968(void *object);
void func_00137588(void *segment,void *root,float time,float scale,int flags,void *state);
LookupNode *func_00239A10(void *owner,void *receiver);
void func_00232A38(void *object,int mode);
void func_002323C8(SegmentOwner *object)
{
    func_001FC968(object);
    object->mode=object->sourceMode;
    func_00137588(object->segment,object->root,0.0f,0.0f,8,object->segmentState);
    object->receiver=func_00239A10(object->lookupOwner,object);
    object->time=0.0f;
    func_00232A38(object,0);
}
}
