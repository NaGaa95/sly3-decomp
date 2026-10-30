// SLY3_CFLAGS: -Os -G0
extern char D_00353C90[] __asm__("_vt$17OBJECT_COLLECTION");
void func_002BC5A0(void *p) __asm__("__22OBJECT_COLLECTION_BASE");
struct S { void *vt; int a, b, c; };
struct S *func_00151A38(struct S *s)
{
    func_002BC5A0(s);
    s->vt = D_00353C90;
    s->a = 0;
    s->b = 0;
    s->c = 0;
    return s;
}
