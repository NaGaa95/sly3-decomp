// Reset the inherited object and apply the original global selection and flags to its stored owner.
// Reference algorithm: src/hand/func_0013CFD8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { int reserved; int selection; int flags; };
extern struct R D_0036DBE0;
struct S { void *owner; };
void func_00169E40(struct S *object);
void func_00167AB0(void *owner,int first,int second,int selection,int flags);
void func_00279AB0(struct S *object)
{
    func_00169E40(object);
    func_00167AB0(object->owner,0,0,D_0036DBE0.selection,D_0036DBE0.flags);
}
