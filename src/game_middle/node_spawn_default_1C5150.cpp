// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/vector_intrinsics.h"

struct SpawnRow { float xyz[3]; unsigned int raw_w; } __attribute__((aligned(16)));
struct SpawnMatrix { SpawnRow rows[3]; };
struct SpawnMethod { short adjustment, word2; void (*function)(void *self, SpawnMatrix *matrix); };
struct SpawnTable { unsigned char prefix[0x118]; SpawnMethod apply; };
struct SpawnNode {
    unsigned char prefix[0xC];
    SpawnTable *methods;
    unsigned char gap10[0x20 - 0x10];
    SpawnNode *next;
    unsigned char gap24[0x150 - 0x24];
    int active;
};
extern "C" {
extern SpawnNode *D_004784D0;
extern qword D_00317550;
SpawnNode *func_00150690(int type, void *owner, int key, int parent);
SpawnMatrix func_0011CBF0(qword direction, qword up);
void func_001C5510(void *node, float value);
void func_001C5530(void *node, float value);

void func_001C5150(void)
{
    SpawnNode *node = D_004784D0;
    while (node && node->active)
        node = node->next;
    if (node)
        return;
    node = func_00150690(4, 0, 0x1A7, -1);
    {
        SpawnMatrix matrix;
        union { qword packed; } direction;
        direction.packed = PackVectorXYZ(-0.2f, 0.3f, -1.0f);
        matrix = func_0011CBF0(direction.packed, D_00317550);
        SpawnMethod *method = &node->methods->apply;
        method->function((char *)node + method->adjustment, &matrix);
    }
    func_001C5510(node, 120.0f);
    func_001C5530(node, 240.0f);
}
}
