// SLY3_CFLAGS: -Os -G0
struct Method { short delta,unused; void (*method)(void); };
struct Node { struct Node *unused; int unknown_4; int unknown_8; struct Method *methods; struct Node *next; int unknown_14; int id; };
struct Registry { struct Node *head; };
struct Node *func_0021DC30(struct Registry *registry,int id);
void func_0021DC60(struct Registry *registry,int id,struct Node *replacement)
{
    struct Node *previous=func_0021DC30(registry,id);
    if(previous==replacement)
        return;
    if(replacement)
        ((void (*)(void *,int,void *))replacement->methods[9].method)((char *)replacement+replacement->methods[9].delta,0,previous);
    if(previous)
        ((void (*)(void *,int,void *))previous->methods[9].method)((char *)previous+previous->methods[9].delta,1,replacement);
}
