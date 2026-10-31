// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Created { unsigned char pad0[4]; void *list; };
struct Registry { unsigned char pad0[0x134]; unsigned char items[0x10]; };
extern char D_00475480[];
extern int D_00479CBC;
struct Registry *func_0020AFC0(void *world, int zero);
int func_0020B970(void);
void *func_0020BB90(unsigned int bytes);
void *func_0020BBD8(unsigned int bytes);
void func_0020BDB0(struct Created *object);
void func_0011AF60(void *list, void *object);
void *func_002BEC40(void *storage);
void *func_002BEC58(void *storage);
void *func_002BEC90(void *storage);
void *func_002BECC8(void *storage);
void *func_002BED00(void *storage);
void *func_002BED38(void *storage);
void *func_002BED70(void *storage);
void *func_002BEDA8(void *storage);
void *func_002BEDE0(void *storage);
void *func_002BEE18(void *storage);
void *func_002BEE50(void *storage);
// Create a registered object of the requested type (0..10): allocate from the type's pool, run its constructor, link it into the registry list.
struct Created *func_0020B9C0(void *world, int type, void *list)
{
    struct Created *object;
    if (!list) {
        struct Registry *registry = func_0020AFC0(D_00475480, 0);
        if (!registry)
            return 0;
        list = registry->items;
    }
    if (!(type == 5 || D_00479CBC || func_0020B970()))
        return 0;
    object = 0;
    switch (type) {
    case 6: object = (struct Created *)func_002BEC40(func_0020BB90(0xF0)); break;
    case 2: object = (struct Created *)func_002BEC58(func_0020BB90(0x100)); break;
    case 9: object = (struct Created *)func_002BEC90(func_0020BB90(0x100)); break;
    case 7: object = (struct Created *)func_002BECC8(func_0020BB90(0x100)); break;
    case 5: object = (struct Created *)func_002BED00(func_0020BBD8(0x110)); break;
    case 3: object = (struct Created *)func_002BED38(func_0020BB90(0x100)); break;
    case 8: object = (struct Created *)func_002BED70(func_0020BB90(0x110)); break;
    case 4: object = (struct Created *)func_002BEDE0(func_0020BB90(0xF0)); break;
    case 0: object = (struct Created *)func_002BEDA8(func_0020BB90(0x100)); break;
    case 1: object = (struct Created *)func_002BEE18(func_0020BB90(0x100)); break;
    case 10: object = (struct Created *)func_002BEE50(func_0020BB90(0x110)); break;
    }
    if (object) {
        func_0020BDB0(object);
        object->list = list;
        func_0011AF60(list, object);
    }
    return object;
}
