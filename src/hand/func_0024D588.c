// Run the inherited update and notify the owner, when present, with both explicit receiver and child arguments.
// Reference algorithm: src/hand/func_0021BBD0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0xDC]; void *owner; };
void func_001C7DC8(struct S *p);
void func_0013BD00(void *owner, struct S *p);
void func_0024D588(struct S *p)
{
    func_001C7DC8(p);
    if (p->owner)
        func_0013BD00(p->owner, p);
}
