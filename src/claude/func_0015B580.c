// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta,reserved; void (*call)(void *); };
int func_0011B0C0(void *, void *);
void func_0011B028(void *, void *);

void func_0015B580(char *p, char *object)
{
    void *list = p + 0x3E90;
    if (func_0011B0C0(list, object)) {
        struct VirtualEntry *table = *(struct VirtualEntry **)(object + 0x14);
        table[3].call(object + table[3].delta);
        func_0011B028(list, object);
    }
}
