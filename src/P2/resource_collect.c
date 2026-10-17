// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
extern int D_0036DBE0;
void *func_001F4AD0(void *, int);
int func_0013B500(void *, int);
void *func_0017E1B8(void *, int, int, void *);
void *func_001FBE30(void *, int);
void func_001FC060(void *, void *);
void func_001FC090(void *, void *);
int func_001F8280(void *query, int mode, int limit, void **out)
{
    void *resource;
    void *item;
    int index;
    int count;
    int key;
    if (limit == 0)
        return 0;
    if ((D_0036DBE0 ^ 2) == 0)
        return 0;
    switch (mode) {
    case 0x67: {
        void *controller = func_001F4AD0(D_00475480, 0);
        if (controller && func_0013B500(controller, 0x3C))
            return 0;
        key = 0x30A;
        break;
    }
    case 0x69:
        key = 0x30B;
        break;
    default:
        return 0;
    }
    resource = func_0017E1B8(query, 5, key, 0);
    if (!resource)
        return 0;
    count = 0;
    for (index = 0; index < limit; index++) {
        item = func_001FBE30(resource, 0);
        if (!item)
            break;
        func_001FC060(resource, item);
        out[count++] = item;
    }
    for (index = 0; index < count; index++)
        func_001FC090(resource, out[index]);
    return count;
}
