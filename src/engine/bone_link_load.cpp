// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "../P2/bis.h"
#include "../P2/heap.h"
struct BoneLinkRecord;
struct BoneLinkBone {
    unsigned char prefix[0xA8];
    BoneLinkRecord *link;
};
struct BoneLinkRecord {
    void *parent;
    BoneLinkBone *child;
    int word8,wordC;
};
struct BoneLinkMethod { short delta,unused; void (*method)(); };
struct BoneLinkOwner {
    unsigned char prefix[12];
    BoneLinkMethod *methods;
};
typedef char BoneLinkRecordSize16[(sizeof(BoneLinkRecord)==16)?1:-1];
extern unsigned char D_0034A160[];
extern "C" void *func_001D2538(ALLOCREQ *);
extern "C" void func_0028F068(void *,void *,int);
static __inline__ BoneLinkBone *ReadBoneLinkTarget(BoneLinkOwner *owner,
                                                 CBinaryInputStream *stream)
{
    BoneLinkMethod *entry=&owner->methods[55];
    void *adjusted=(char *)owner+entry->delta;
    int index=stream->S16Read();
    return ((BoneLinkBone *(*)(void *,int))entry->method)(adjusted,index);
}
extern "C" void func_00182808(void *receiver,CBinaryInputStream *stream)
{
    BoneLinkOwner *owner=(BoneLinkOwner *)receiver;
    int count=stream->S8Read();
    for(int i=0;i<count;++i) {
        ALLOCREQ request;
        request.cb=16;
        request.cbAlign=16;
        BoneLinkRecord *link=(BoneLinkRecord *)func_001D2538(&request);
        link->parent=ReadBoneLinkTarget(owner,stream);
        if(!link->parent)
            link->parent=D_0034A160;
        link->child=ReadBoneLinkTarget(owner,stream);
        link->word8=stream->S8Read();
        link->wordC=stream->S8Read();
        link->child->link=link;
        func_0028F068(owner,link->child,16);
    }
}
