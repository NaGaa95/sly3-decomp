// SLY3_CFLAGS: -Os -G0
struct Rectangle {
    int x;
    int y;
    int width;
    int height;
};
struct ConstructedObject {
    unsigned char prefix[0xC];
    void *vtable;
    unsigned char gap10[0x5C];
    int link6C;
    unsigned char gap70[0x4C];
    int slots[10];
};
extern unsigned char D_003674D0[];
void func_002B52F0(void *object);
void func_0011AD60(void *record, int size);
void func_002643D0(void *object, struct Rectangle *rectangle);
void *func_002606A0(struct ConstructedObject *object)
{
    unsigned int i;
    struct Rectangle rectangle;
    func_002B52F0(object);
    object->link6C = -1;
    object->vtable = D_003674D0;
    for (i = 0; i < 10; i++)
        object->slots[i] = -1;
    func_0011AD60((char *)object + 0xF4, 0x68);
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.width = 0x280;
    rectangle.height = 0x1E0;
    func_002643D0(object, &rectangle);
    return object;
}
