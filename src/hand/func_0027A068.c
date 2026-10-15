// Release the stored resource through its original collection and reset the object selection.
// Reference algorithm: src/hand/func_0012E6A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
struct S { char prefix[0x358]; void *resource; };
void func_001F3C80(struct S *object);
void func_001CBAA0(void *global,void *resource);
void func_0027C860(struct S *object,int selection);
void func_0027A068(struct S *object)
{
    func_001F3C80(object);
    if(object->resource) { func_001CBAA0(D_00475480,object->resource);object->resource=0; }
    func_0027C860(object,0);
}
