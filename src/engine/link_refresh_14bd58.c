// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct M4 { qword r[4]; } M4;
struct LinkNode { qword m[4]; unsigned char gap40[0xA4 - 0x40]; int stamp; };
struct LinkSelf {
    unsigned char prefix[0xC]; struct LinkNode *first; struct LinkNode *second;
    unsigned char gap14[0x130 - 0x14]; unsigned char taskB[4]; unsigned char taskA[4];
    unsigned char gap138[0x140 - 0x138]; qword firstTarget;
    unsigned char gap150[0x150 - 0x150]; qword secondTarget;
};
struct LinkGame { unsigned char prefix[0x44F4]; int generation; };
extern struct LinkGame D_00475480;
void func_001309D8(void *task);
M4 func_0028B230(void *node, qword target);
void func_0014BD58(struct LinkSelf *self)
{
    struct LinkNode *node;
    int generation;
    func_001309D8(self->taskA);
    func_001309D8(self->taskB);
    node = self->first;
    if(node) {
        M4 matrix = func_0028B230(node, self->firstTarget);
        *(M4 *)node->m = matrix;
        generation = ++D_00475480.generation;
        self->first->stamp = generation;
    }
    node = self->second;
    if(node) {
        M4 matrix = func_0028B230(node, self->secondTarget);
        *(M4 *)node->m = matrix;
        generation = ++D_00475480.generation;
        self->second->stamp = generation;
    }
}
