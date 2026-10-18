// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct NoticeNode {
    unsigned char prefix[0x6C]; void *owner;
    unsigned char gap70[8]; NoticeNode *next;
};
struct NoticeList { void *first,*last; int linkOffset; };
struct NoticeIterator;
extern "C" {
extern NoticeNode *D_004794B8;
extern void *D_004794C4;
extern NoticeList D_00479B98;
extern NoticeIterator *D_0036AE94;
extern unsigned char D_0036BD20[],D_004BC230[];
void func_001855F0(int transported_unused,int event);
void func_00171AA0(void *self,int event,void *payload);
void func_00189DF8(NoticeNode *self,unsigned int event,unsigned int payload);
void func_001772D8(void *self,int event,int payload);
void func_00186730(void *self,int event,int payload);
void func_002849A8(void *self,int event,void *payload);
}
struct NoticeIterator {
    NoticeList *list;
    void **cursor;
    int linkOffset;
    NoticeIterator *previous;
    NoticeIterator(NoticeList *items)
        : list(items),cursor((void **)items),linkOffset(items->linkOffset),previous(D_0036AE94)
    {
        D_0036AE94=this;
    }
    ~NoticeIterator() { D_0036AE94=previous; }
    void *Next()
    {
        void *value=*cursor;
        cursor=(void **)((unsigned int)value+(unsigned int)linkOffset);
        return value;
    }
};
extern "C" void func_001854C8(void *context,int event,void *payload)
{
    func_001855F0((int)context,event);
    func_00171AA0(D_0036BD20,event,payload);
    for(NoticeNode *node=D_004794B8;node;node=node->next) {
        if(node->owner==D_004794C4)
            func_00189DF8(node,(unsigned int)event,(unsigned int)payload);
    }
    NoticeIterator iterator(&D_00479B98);
    void *object;
    while((object=iterator.Next())!=0)
        func_001772D8(object,event,(int)payload);
    if(D_004794C4) func_00186730(D_004794C4,event,(int)payload);
    func_002849A8(D_004BC230,event,payload);
}

#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char IntSize[(sizeof(int)==4)?1:-1];
typedef char NodeOwner[(MEMBER_OFFSET(NoticeNode,owner)==0x6C)?1:-1];
typedef char NodeNext[(MEMBER_OFFSET(NoticeNode,next)==0x78)?1:-1];
typedef char ListSize[(sizeof(NoticeList)==12)?1:-1];
typedef char ListOffset[(MEMBER_OFFSET(NoticeList,linkOffset)==8)?1:-1];
typedef char IteratorSize[(sizeof(NoticeIterator)==16)?1:-1];
typedef char IteratorList[(MEMBER_OFFSET(NoticeIterator,list)==0)?1:-1];
typedef char IteratorCursor[(MEMBER_OFFSET(NoticeIterator,cursor)==4)?1:-1];
typedef char IteratorOffset[(MEMBER_OFFSET(NoticeIterator,linkOffset)==8)?1:-1];
typedef char IteratorPrevious[(MEMBER_OFFSET(NoticeIterator,previous)==12)?1:-1];
