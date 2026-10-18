// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct Object {
    char prefix[0x44];
    int identifier;
    char gap48[0xC];
    int kind;
    Object *next;
};
struct VirtualEntry { short delta,unused; int (*test)(void *,Object *); };
struct Collection;
struct Self {
    char prefix[0xC];
    VirtualEntry *methods;
    char gap10[0x1070];
    float deadline;
    char gap1084[0x4C];
    Collection *collection;
};
struct Record { int identifier,unused,state; float time,changed; };
struct Game { char prefix[0x4784]; Object *first; };
struct Clock { float time,delta; };
extern "C" {
extern Game D_00475480;
extern Clock D_0036BB98;
int func_00254818(Self *);
int func_00255C38(Self *,Object *,Object *);
Record *func_00170528(Collection *,int);
void func_00170410(Collection *,Record *,int);
void func_002BF740(void *,int);
}
class SelectionScope {
public:
    ~SelectionScope() { func_002BF740(this,2); }
};
extern "C" Object *func_00256090(Self *self,Object *fallback)
{
    if(!func_00254818(self))
        return fallback;
    SelectionScope scope;
    Object *best=fallback;
    for(Object *object=D_00475480.first;object;object=object->next) {
        VirtualEntry *method=&self->methods[98];
        if(method->test((char *)self+method->delta,object))
            if(!best||func_00255C38(self,object,best)<0)
                best=object;
    }
    if(best&&best->kind==4) {
        Record *record=func_00170528(self->collection,best->identifier);
        if(record) {
            if(!record->state) {
                func_00170410(self->collection,record,2);
                self->deadline=D_0036BB98.time+2.0f;
            }
            return fallback;
        }
    }
    return best;
}
