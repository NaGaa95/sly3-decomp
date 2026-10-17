// SLY3_CFLAGS: -Os -G0 -fno-exceptions
typedef int Qword __attribute__((mode(TI)));
struct PickEntry { short delta; short pad; unsigned char *(*method)(void *); };
struct PickObject { unsigned char prefix[0xC]; PickEntry *table; };
struct PickOwner { unsigned char prefix[0xC]; PickEntry *table; unsigned char gap10[0xDC - 0x10]; void *context; };
struct PickSelf { unsigned char prefix[0x10]; PickOwner *owner; };
struct Candidate { int status; PickObject *object; };
typedef int (*RayFilter)(void *context, void *record);
extern "C" {
extern unsigned char D_00475480[];
Candidate func_00253EE8(void *owner);
void *func_001D2770(void *receiver);
void func_001D2798(void *receiver, int flags);
int func_0025CEC8(void *context, void *record);
void func_0025CF18(void *game, Qword start, Qword end, RayFilter filter, void *context, int *count, void ***records);
void *func_00165000(int flags, Qword start, Qword end, int count, void **records, void *output);
}
extern "C" PickObject *func_001342B8(PickSelf *self)
{
    Candidate found = func_00253EE8(self->owner);
    if(found.status <= 0) {
        if(found.status >= -1) return 0;
    }
    PickObject *object = found.object;
    Qword start = *(Qword *)(self->owner->table[36].method((unsigned char *)self->owner + self->owner->table[36].delta) + 0x30);
    Qword end = *(Qword *)(object->table[36].method((unsigned char *)object + object->table[36].delta) + 0x30);
    void *frame;
    int count;
    void **records;
    func_001D2770(&frame);
    func_0025CF18(D_00475480, start, end, func_0025CEC8, self->owner->context, &count, &records);
    if(func_00165000(0, start, end, count, records, 0)) {
        func_001D2798(&frame, 2);
        return 0;
    }
    func_001D2798(&frame, 2);
    return object;
}
