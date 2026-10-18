// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct FocusGraphNode {
    unsigned char prefix[0x6C]; FocusGraphNode *parent;
    unsigned char gap70[0x84-0x70]; int prerequisite;
    unsigned char gap88[0x90-0x88]; int childCount; FocusGraphNode **children;
    unsigned char gap98[0xF0-0x98]; int parentFirst,parentSecond;
    unsigned char gapF8[0xFC-0xF8]; int first,second,visits,depth,crossParentDepth;
};
class FocusGraphGuard {
public:
    FocusGraphNode *link,*object;
    int linkFirst,objectFirst,linkSecond,objectSecond;
    FocusGraphGuard(FocusGraphNode *target,int first,int second)
    {
        link=target->parent;
        object=target;
        if(object) {
            objectFirst=object->first;
            object->first=first;
            objectSecond=object->second;
            object->second=second;
        }
        if(link) {
            linkFirst=link->parentFirst;
            link->parentFirst=first;
            linkSecond=link->parentSecond;
            link->parentSecond=second;
        }
    }
    ~FocusGraphGuard()
    {
        if(link) {
            link->parentFirst=linkFirst;
            link->parentSecond=linkSecond;
        }
        if(object) {
            object->first=objectFirst;
            object->second=objectSecond;
        }
    }
};
static inline int Max(int a,int b) { return a<b?b:a; }
extern "C" void func_00188B08(FocusGraphNode *self,int *count,FocusGraphNode **output,int depth,int crossParentDepth)
{
    self->visits++;
    self->depth=Max(depth,self->depth);
    self->crossParentDepth=Max(crossParentDepth,self->crossParentDepth);
    depth=self->depth;
    crossParentDepth=self->crossParentDepth;
    if(self->visits>=self->prerequisite) {
        output[(*count)++]=self;
        depth++;
        for(int i=0;i<self->childCount;i++) {
            FocusGraphNode *child=self->children[i];
            FocusGraphGuard guard(child,self->first,self->second);
            int childCrossParentDepth=crossParentDepth;
            if(self->parent && child->parent!=self->parent) childCrossParentDepth++;
            func_00188B08(child,count,output,depth,childCrossParentDepth);
        }
    }
}
#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char RealGuardSize[(sizeof(FocusGraphGuard)==24)?1:-1];
typedef char ParentOffset[(MEMBER_OFFSET(FocusGraphNode,parent)==0x6C)?1:-1];
typedef char PrerequisiteOffset[(MEMBER_OFFSET(FocusGraphNode,prerequisite)==0x84)?1:-1];
typedef char ChildCountOffset[(MEMBER_OFFSET(FocusGraphNode,childCount)==0x90)?1:-1];
typedef char ChildrenOffset[(MEMBER_OFFSET(FocusGraphNode,children)==0x94)?1:-1];
typedef char ParentFirstOffset[(MEMBER_OFFSET(FocusGraphNode,parentFirst)==0xF0)?1:-1];
typedef char ParentSecondOffset[(MEMBER_OFFSET(FocusGraphNode,parentSecond)==0xF4)?1:-1];
typedef char FirstOffset[(MEMBER_OFFSET(FocusGraphNode,first)==0xFC)?1:-1];
typedef char SecondOffset[(MEMBER_OFFSET(FocusGraphNode,second)==0x100)?1:-1];
typedef char VisitsOffset[(MEMBER_OFFSET(FocusGraphNode,visits)==0x104)?1:-1];
typedef char DepthOffset[(MEMBER_OFFSET(FocusGraphNode,depth)==0x108)?1:-1];
typedef char CrossDepthOffset[(MEMBER_OFFSET(FocusGraphNode,crossParentDepth)==0x10C)?1:-1];
