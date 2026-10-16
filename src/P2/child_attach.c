// SLY3_CFLAGS: -Os -G0
struct Method { short delta,unused; void (*method)(void); };
struct Parent;
struct Child { char unknown_0[0xC]; struct Method *methods; char unknown_10[0x13C-0x10]; struct Parent *parent; };
struct Parent { char unknown_0[0x1A8]; struct Child *child; };
void func_00215958(struct Parent *parent);
void func_002158F0(struct Parent *parent,struct Child *child)
{
    struct Child *previous=parent->child;
    if(previous==child)
        return;
    if(previous)
        ((void (*)(void *))previous->methods[54].method)((char *)previous+previous->methods[54].delta);
    parent->child=child;
    if(child)
        child->parent=parent;
    func_00215958(parent);
}
