// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t, dt; };
extern struct CLOCK D_0036BB98;
void func_00238A38(void *object);
void func_002389C0(void *object);
void func_00238AB8(void *object);
struct KindObject { unsigned char prefix[0x30]; int kind; float stamp; int word38; int word3C; };
void func_001599E0(struct KindObject *object, int kind)
{
    int old = object->kind;
    if(kind == old) return;
    if(old < 5) {
        if(old >= 2) func_00238A38(object);
    }
    object->kind = kind;
    object->stamp = D_0036BB98.t;
    switch(kind) {
    case 2: case 3: case 4:
        func_002389C0(object);
        object->word3C = 1;
        break;
    case -1:
        func_00238AB8(object);
        break;
    }
}
