// SLY3_CFLAGS: -Os -G0
// GCC 2.95 virtual entries contain a signed this adjustment and a callable address.
// The observed object vtable is at offset 12; slots 53 and 42 are recovered
// directly from the original signed-short and function-pointer loads.
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef struct Matrix { Quadword rows[4]; } Matrix;
typedef struct RuntimeObject RuntimeObject;
typedef struct VirtualEntry { short adjustment; short reserved; void (*call)(); } VirtualEntry;
struct RuntimeObject {
    unsigned char opaque0[12]; VirtualEntry *vtable;
    void *owner; int resource; unsigned char opaque1[40];
    void *parent; int state; unsigned char opaque2[8]; Matrix matrix;
};
typedef struct ObjectList { int opaque0[2]; int count; RuntimeObject **items; } ObjectList;
extern void func_0028C210(void *parent);
extern void func_0028C238(void *parent);
extern void func_00151D80(void *owner, void *stream, ObjectList *list);
extern int func_00119178(void *stream);
extern void func_00119340(void *stream, Matrix *out);
extern int func_001190A8(void *stream);
extern void func_001C9198(RuntimeObject *object, int argument);
extern void func_00290078(RuntimeObject *object);
void func_00290438(RuntimeObject *object, void *stream) {
    int value = func_00119178(stream);
    VirtualEntry *entry = &object->vtable[53];
    object->parent = ((void *(*)(void *,int))entry->call)((char *)object + entry->adjustment,value);
    func_00119340(stream,&object->matrix);
    func_00290078(object);
    func_001C9198(object,func_001190A8(stream));
}
void func_002904B0(RuntimeObject *object, void *stream, ObjectList *list) {
    int i=0;
    func_0028C210(object->parent);
    func_00151D80(object->owner,stream,list);
    func_0028C238(object->parent);
    for (; i < list->count; ++i) {
        RuntimeObject *child = list->items[i];
        VirtualEntry *entry = &child->vtable[42];
        ((void (*)(void *,Matrix *))entry->call)((char *)child + entry->adjustment,&object->matrix);
    }
}
