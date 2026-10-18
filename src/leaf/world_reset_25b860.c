// SLY3_CFLAGS: -Os -G0
struct PoolState { int blockSize; int blockCount; int alignment; void *free; int allocated; void *block; };
struct Method { short delta, unused; void (*method)(void *); };
struct Object { unsigned char prefix[0xC]; struct Method *methods; };
struct World {
    unsigned char gap0000[0x3F00];
    int word3F00;
    unsigned char gap3F04[4];
    int word3F08;
    unsigned char gap3F0C[4];
    struct Object **begin;
    struct Object **end;
    unsigned char gap3F18[0x47C4 - 0x3F18];
    struct PoolState pool0, pool1, pool2;
    unsigned char gap480C[0xC];
    struct PoolState pool3, pool4, pool5;
    unsigned char gap4860[4];
    struct PoolState pool6, pool7;
    unsigned char gap4894[0x4DFC - 0x4894];
    void *word4DFC;
};
typedef char PoolStateIs24[(sizeof(struct PoolState) == 24) ? 1 : -1];
typedef char PointerIs4[(sizeof(void *) == 4) ? 1 : -1];
extern unsigned char D_004BC230[];
extern unsigned char D_0046F540[];
void func_0011E230(struct PoolState *pool);
void func_0025B130(struct World *world);
void func_0025B0A8(struct World *world);
void func_002499C0(struct World *world);
void func_001FB150(struct World *world);
void func_0025CA70(struct World *world);
void func_0025CD00(struct World *world);
void func_00173C10(struct World *world);
void func_001C5150(struct World *world);
void func_00165748(struct World *world);
void func_001ED9B8(struct World *world);
void func_0025DD00(struct World *world);
void func_001B7000(struct World *world);
void func_00283970(void *singleton);
void func_0021D8B0(void *singleton);
void func_0015DE78(struct World *world);
void func_001EDB48(void *value);
void func_0025B860(struct World *world)
{
    func_0011E230(&world->pool0);
    func_0011E230(&world->pool1);
    func_0011E230(&world->pool2);
    func_0011E230(&world->pool3);
    func_0011E230(&world->pool4);
    func_0011E230(&world->pool5);
    func_0011E230(&world->pool6);
    func_0011E230(&world->pool7);
    func_0025B130(world);
    func_0025B0A8(world);
    func_002499C0(world);
    func_001FB150(world);
    func_0025CA70(world);
    func_0025CD00(world);
    func_00173C10(world);
    func_001C5150(world);
    func_00165748(world);
    func_001ED9B8(world);
    func_0025DD00(world);
    func_001B7000(world);
    func_00283970(D_004BC230);
    func_0021D8B0(D_0046F540);
    for (;;) {
        struct Object **cursor;
        func_0015DE78(world);
        if (world->end == world->begin)
            break;
        for (cursor = world->begin; cursor < world->end;) {
            struct Object *object = *cursor++;
            struct Method *method = &object->methods[17];
            method->method((char *)object + method->delta);
        }
        world->end = world->begin;
    }
    world->end = 0;
    world->begin = 0;
    world->word3F08 = 0;
    world->word3F00 = 0;
    func_001EDB48(world->word4DFC);
}
