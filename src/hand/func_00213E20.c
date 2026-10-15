// Apply the inherited update and remove the explicit object in the original global doubly linked list.
// Reference algorithm: src/hand/func_0014B1A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00479BEC[];
void func_0023CE08(void *object);
void func_0011B028(void *list, void *object);
void func_00213E20(void *object)
{
    func_0023CE08(object);
    func_0011B028(D_00479BEC, object);
}
