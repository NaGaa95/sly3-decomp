// SLY3_CFLAGS: -Os -G0
#include "resource_attachment_api.h"
typedef int Qword __attribute__((mode(TI)));
struct VirtualEntry {
    short adjustment, reserved;
    void (*method)(void *);
};
struct CancelEntry {
    short adjustment, reserved;
    void (*method)(void *, int);
};
struct Command {
    char prefix[0xC];
    struct VirtualEntry *table;
    char opaque10[0x20];
    int value30;
    char opaque34[0xC];
    Qword value40;
};
struct Owner {
    char prefix[0xC];
    struct CancelEntry *table;
};
void func_00238568(void *list);
void func_00154F50(struct Owner *owner, int value, Qword extra)
{
    owner->table[99].method((char *)owner + owner->table[99].adjustment, 0);
    func_00238568((char *)owner + 0x29C);
    if(value) {
        struct Command *command = func_00238690((char *)owner + 0x29C, 0xF5);
        struct VirtualEntry *entry;
        command->value30 = value;
        command->value40 = extra;
        entry = command->table + 8;
        entry->method((char *)command + entry->adjustment);
    }
}
