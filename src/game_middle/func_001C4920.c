// SLY3_CFLAGS: -Os -G0 -ffast-math
// Collect the ids (0..248) that match any entry of the include list and no entry of the exclude list, then look up
// the first collected id.
struct Collection {
    char pad00[0x44];
    int x44;
    int x48;
    int count;
    int ids[1];
};
extern char D_00475480[];
int func_0013BEC8(int id, int key);
int *func_0017DBD0(void *table, int id);
void func_001C4920(struct Collection *p, int includeCount, int *include, int excludeCount, int *exclude)
{
    int id, i, j;
    p->count = 0;
    for (id = 0; id < 249; id++) {
        for (i = 0; i < includeCount; i++)
            if (func_0013BEC8(id, include[i]))
                break;
        if (i >= includeCount)
            continue;
        for (j = 0; j < excludeCount; j++)
            if (func_0013BEC8(id, exclude[j]))
                break;
        if (j < excludeCount)
            continue;
        p->ids[p->count++] = id;
    }
    p->x44 = 0;
    p->x48 = *func_0017DBD0(D_00475480, p->ids[0]);
}
