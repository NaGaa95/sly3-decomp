// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef struct VirtualEntry { short adjustment; short reserved; void (*call)(void *, ...); } VirtualEntry;
struct Spawned { unsigned char gap0[0x26C]; int word26C; };
struct Template { unsigned char gap0[4]; int enabled; };
struct Prop { unsigned char gap0[0xC]; VirtualEntry *vtable; };
struct Spawner { unsigned char gap0[0x54]; int count; struct Prop **props; };
int func_0011E8F0(int, int);
void *func_001FBE30(void *, int);
void func_002172C8(void *, int);
void func_002159D8(void *, int);
void func_002171E8(void *, int);
void *func_0021B320(struct Spawner *self, struct Template *template, Quadword *position, void *orientation, int enabled)
{
    int order[8];
    void *result = 0;
    int i, j, k;
    for (i = 0; i < self->count; i++)
        order[i] = i;
    for (j = 0; j < self->count; j++) {
        int partner = func_0011E8F0(0, self->count - 1);
        int swap = order[j];
        order[j] = *(int *)((char *)order + partner * 4);
        *(int *)((char *)order + partner * 4) = swap;
    }
    for (k = 0; k < self->count; k++) {
        struct Prop *prop = self->props[order[k]];
        VirtualEntry *entry = &prop->vtable[34];
        entry->call((char *)prop + entry->adjustment, *position);
        entry = &prop->vtable[35];
        entry->call((char *)prop + entry->adjustment, orientation);
        result = func_001FBE30(prop, 0);
        if (result) {
            ((struct Spawned *)result)->word26C = enabled;
            func_002172C8(result, template->enabled);
            func_002159D8(result, 2);
            func_002171E8(result, 1);
            return result;
        }
    }
    return result;
}
