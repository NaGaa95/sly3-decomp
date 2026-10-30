// SLY3_CFLAGS: -Os -G0
int func_0011B0C0(void *, void *);
void func_0011B028(void *, void *);

void func_0015AD18(char *p, char *object)
{
    void *list;
    list = p + 0x3DF8;
    if (func_0011B0C0(list, object))
        func_0011B028(list, object);
    {
        void *list2 = p + 0x3DE8;
        if (func_0011B0C0(list2, object)) {
            if (*(char **)(p + 0x3DF4) == object)
                *(char **)(p + 0x3DF4) = *(char **)(object + 4);
            func_0011B028(list2, object);
        }
    }
}
