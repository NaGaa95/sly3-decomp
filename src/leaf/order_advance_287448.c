// SLY3_CFLAGS: -Os -G0
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef struct VirtualEntry { short adjustment; short reserved; void *(*call)(void *); } VirtualEntry;
struct Position { unsigned char gap0[0x30]; Quadword value; };
struct Queue {
    unsigned char gap0[0xC];
    VirtualEntry *vtable;
    unsigned char gap10[0x218 - 0x10];
    void *spaceInput;
    int index;
    unsigned char gap220[8];
    int count;
    int ids[1];
};
extern char D_00474FF0[];
extern char D_0036C700[];
int func_00248858(void *, int);
int func_0011E8F0(int, int);
void func_002485D8(void *, int, int, int);
void *memmove(void *, const void *, unsigned int);
void func_00173778(void *, Quadword, int, void **);
void func_001854C8(void *, int, void *);
static inline void Swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
void func_00287448(struct Queue *self)
{
    if (self->count > 0) {
        int first = self->ids[0];
        if (!func_00248858(D_00474FF0, first)) {
            int count = self->count;
            if (self->index == count) {
                int i;
                for (i = 0; i < self->count; i++) {
                    int j = func_0011E8F0(0, self->count - 1);
                    Swap(&self->ids[i], &self->ids[j]);
                }
                if (self->ids[0] == first) {
                    int last = self->count - 1;
                    self->ids[0] = self->ids[last];
                    self->ids[last] = first;
                }
                self->index = 0;
            } else {
                memmove(self->ids, &self->ids[1], (count - 1) * 4);
                self->ids[self->count - 1] = first;
                self->index = self->index + 1;
            }
            func_002485D8(D_00474FF0, self->ids[0], 0, 0);
        }
    }
    {
        VirtualEntry *entry = &self->vtable[36];
        struct Position *position = (struct Position *)entry->call((char *)self + entry->adjustment);
        func_00173778(self->spaceInput, position->value, (int)self, 0);
    }
    func_001854C8(D_0036C700, 0x61, self);
}
