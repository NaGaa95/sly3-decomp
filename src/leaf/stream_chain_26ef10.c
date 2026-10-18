// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct Matrix3 { Qword row[3]; };
struct Chain;
struct Entry;
struct Owner;
struct Object {
    struct Matrix3 matrix;
    char gap30[0x40];
    Qword position;
    char gap80[0x28];
    struct Entry *entry;
};
struct VirtualEntry { short delta, unused; struct Object *(*get)(void *,int); };
struct Owner { char prefix[0xC]; struct VirtualEntry *methods; };
struct Entry {
    struct Matrix3 matrix;
    Qword position,world,unused50;
    struct Chain *chain;
    struct Object *object;
    int unused68,unused6C;
};
struct Chain {
    int count;
    struct Entry *entries;
    int kind;
    float first,second,third,fourth;
    int unused1C;
    Qword axis,endpoint,unused40;
};
struct Hook {
    int kind;
    struct Owner *owner;
    struct Object *object;
    int order,next,flags;
    void *methods;
    struct Entry *entry;
};
struct Request { int bytes,alignment; };
extern char D_00367C40[];
int func_00119128(void *);
int func_00118FF8(void *);
float func_00119260(void *);
void func_001192D8(void *,Qword *);
int func_00119178(void *);
void *func_001D2538(struct Request *);
struct Hook *func_0014BE38(int);
struct Hook *func_002BBC38(struct Hook *);
void func_0028ECE0(struct Owner *,struct Object *,struct Hook *);
Qword func_0028E910(struct Object *,struct Object *,Qword);
Qword func_0028E990(struct Object *,struct Object *,Qword);
static inline void *Allocate(int bytes)
{
    struct Request request;
    request.bytes=bytes;
    request.alignment=16;
    return func_001D2538(&request);
}
void func_0026EF10(struct Owner *owner,void *stream)
{
    int count=func_00119128(stream);
    int i,j;
    struct Entry *entry;
    for(i=0;i<count;i++) {
        struct Chain *chain=(struct Chain *)Allocate(sizeof(struct Chain));
        chain->kind=func_00118FF8(stream);
        chain->first=func_00119260(stream);
        chain->second=func_00119260(stream);
        chain->third=func_00119260(stream);
        chain->fourth=func_00119260(stream);
        func_001192D8(stream,&chain->axis);
        func_001192D8(stream,&chain->endpoint);
        chain->count=func_00119128(stream);
        chain->entries=(struct Entry *)Allocate(chain->count*sizeof(struct Entry));
        for(j=0;j<chain->count;j++) {
            struct Hook *hook;
            entry=&chain->entries[j];
            entry->chain=chain;
            {
                struct VirtualEntry *method=&owner->methods[55];
                entry->object=method->get((char *)owner+method->delta,func_00119178(stream));
            }
            entry->matrix=entry->object->matrix;
            hook=func_0014BE38(0x20);
            func_002BBC38(hook);
            hook->methods=D_00367C40;
            hook->kind=3;
            hook->owner=owner;
            hook->object=entry->object;
            hook->order=-1;
            hook->entry=entry;
            hook->flags=17;
            func_0028ECE0(owner,entry->object,hook);
            entry->object->entry=entry;
        }
        for(j=0;j<chain->count;j++) {
            entry=&chain->entries[j];
            if(j<chain->count-1)
                entry->position=func_0028E910(0,entry->object,chain->entries[j+1].object->position);
            else if(j>0)
                entry->position=func_0028E990(((struct Entry *)((char *)entry-0x70))->object,entry->object,((struct Entry *)((char *)entry-0x70))->position);
            else
                entry->position=chain->endpoint;
            entry->world=func_0028E910(entry->object,0,entry->position);
        }
    }
}
