// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-gcse
struct LoadRequest { int bytes; int alignment; };
struct LoadMatrix { float f[16]; };
struct LoadNode {
    struct LoadMatrix matrix;
    int word40;
    struct LoadNode *next;
    int word48;
    int word4C;
    float float50;
    int count54;
    void *data58;
};
struct LoadItem {
    struct LoadMatrix matrix;
    int word40;
    struct LoadItem *next;
};
struct LoadOwner {
    unsigned char prefix00[0x18];
    int slotCount;
    unsigned char gap1C[0xA8 - 0x1C];
    struct LoadMatrix matrix;
    int pending;
    struct LoadNode *nodes;
    struct LoadItem *items;
    struct LoadMatrix *basis;
    int valueCount;
    int *values;
    int *slotOf;
    unsigned char gap104[0x1E4 - 0x104];
    int mapCount;
    int map[6];
    unsigned char gap200[0x238 - 0x200];
    unsigned char sub238[16];
};
extern int D_0036B120;
int func_00118FF8(void *stream);
int func_00119178(void *stream);
int func_00119128(void *stream);
int func_001191E0(void *stream);
float func_00119260(void *stream);
void func_00118DA0(void *stream, int bytes, void *destination);
void func_00119948(void *stream, void *destination);
void *func_001D2538(struct LoadRequest *request);
void *func_001D2470(struct LoadRequest *request);
void func_00290E68(int pending);
int func_002908F0(void);
void *func_00292034(void *destination, int value, unsigned int bytes);
int func_00245FE8(void *matrix, int count);
void func_002BF360(void *destination, int value);
static inline int SameMatrix(const struct LoadMatrix *a, const struct LoadMatrix *b)
{
    if (a == b)
        return 1;
    if (!b)
        return 0;
    return ((((const int *)a)[2] ^ ((const int *)a)[14]) ^ (((const int *)b)[2] ^ ((const int *)b)[14])) == 0;
}
void func_00246F58(struct LoadOwner *self, void *stream)
{
    struct LoadMatrix matrix;
    struct LoadRequest request;
    struct LoadRequest *pointer;
    struct LoadRequest *pointer2;
    struct LoadRequest *pointer3;
    int value, i, k, rows, found, nodeCount, n, itemCount;
    struct LoadNode *nodes;
    struct LoadItem *items;
    func_00119948(stream, &matrix);
    if (!SameMatrix(&matrix, &self->matrix)) {
        self->matrix = matrix;
        if (self->pending) {
            func_00290E68(self->pending);
            while (func_002908F0()) {
            }
            self->pending = 0;
        }
    }
    {
        int count = func_00119178(stream);
        pointer = &request;
        request.bytes = count * 4;
        pointer->alignment = 16;
        self->valueCount = count;
        self->values = (int *)func_001D2538(pointer);
        for (i = 0; i < self->valueCount; ++i) {
            int *slot = self->values + i;
            *slot = func_00119128(stream);
        }
    }
    {
        int count = func_00119178(stream);
        int i;
        self->slotCount = count;
        request.bytes = count * 4;
        pointer->alignment = 16;
        self->slotOf = (int *)func_001D2470(pointer);
        func_00292034(self->slotOf, -1, self->slotCount * 4);
        for (i = 0; i < self->valueCount; ++i)
            self->slotOf[func_00119178(stream)] = i;
    }
    self->mapCount = func_00119178(stream);
    if (self->mapCount > 0) {
        request.bytes = 0x40;
        pointer->alignment = 16;
        self->basis = (struct LoadMatrix *)func_001D2538(pointer);
        func_00119948(stream, self->basis);
        value = func_00245FE8(self->basis, 4);
        func_002BF360(self->sub238, value);
    }
    {
        int *slot = self->map;
        func_00292034(slot, -1, 0x18);
        for (i = 0; i < self->mapCount; ++i, ++slot)
            *slot = func_00119178(stream);
    }
    rows = func_00118FF8(stream);
    k = 0;
    found = 0;
    for (; k < rows; ++k)
        if (func_00118FF8(stream) == D_0036B120)
            found = k;
    nodeCount = func_001191E0(stream);
    pointer2 = &request;
    request.bytes = nodeCount * 0x5C;
    pointer2->alignment = 16;
    nodes = (struct LoadNode *)func_001D2538(pointer2);
    for (n = 0; n < nodeCount; ++n) {
        struct LoadNode *node = &nodes[n];
        int r;
        node->word40 = func_00119178(stream);
        node->word48 = func_00119178(stream);
        for (r = 0; r < rows; ++r) {
            struct LoadMatrix local;
            int a;
            float b;
            func_00119948(stream, &local);
            a = func_00119128(stream);
            b = func_00119260(stream);
            if (r == found) {
                node->matrix = local;
                node->word4C = a;
                node->float50 = b;
            }
        }
        node->count54 = func_001191E0(stream);
        request.bytes = node->count54 * 8;
        pointer2->alignment = 16;
        node->data58 = func_001D2470(pointer2);
        func_00118DA0(stream, node->count54 * 8, node->data58);
        node->next = self->nodes;
        self->nodes = node;
    }
    itemCount = func_001191E0(stream);
    pointer3 = &request;
    request.bytes = itemCount * 0x48;
    pointer3->alignment = 16;
    items = (struct LoadItem *)func_001D2538(pointer3);
    for (i = 0; i < itemCount; ++i) {
        struct LoadItem *item = &items[i];
        item->word40 = func_00119178(stream);
        func_00119948(stream, item);
        item->next = self->items;
        self->items = item;
    }
}
