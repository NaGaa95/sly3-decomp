// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
class SlotReference {
public:
    CRef value;
    SlotReference() { value.tag = -1; }
    void Drop() __asm__("func_0012BC20");
    ~SlotReference() { Drop(); }
};
struct SlotEntry {
    short delta, padding;
    union {
        const char *(*path)(void *);
        void (*call)(void *);
    } method;
};
struct SlotRecord { int id, mode; float since; };
struct SlotOwner {
    unsigned char prefix[0xC];
    SlotEntry *table;
    unsigned char gap10[0x1108 - 0x10];
    void *word1108;
    unsigned char gap110C[0x1250 - 0x110C];
    SlotRecord slots[3];
};
extern "C" {
extern const char D_00320590[], D_00320598[];
int func_00271448(char *buffer, const char *format, ...);
SlotReference func_0021CE38(const char *path, ...);
int func_0021F410(int id);
int func_00173560(int id);
void func_00172C30(void *owner, int value);
void func_001547F8(SlotOwner *self)
{
    int i;
    for(i = 0; i < 3; i++) {
        char name[16];
        int id, converted;
        func_00271448(name, D_00320590, i);
        {
            SlotReference reference = func_0021CE38(self->table[117].method.path((char *)self + self->table[117].delta), D_00320598, name, 0);
            id = reference.value.payload.integer;
        }
        if(!func_0021F410(id)) id = 0;
        self->slots[i].id = id;
        converted = func_00173560(id);
        if(converted != -1 && self->word1108) func_00172C30(self->word1108, converted);
    }
    self->table[119].method.call((char *)self + self->table[119].delta);
}
}
