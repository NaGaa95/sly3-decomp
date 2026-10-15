// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions

struct DL { void *pvFirst, *pvLast; int ibDle; };
union OwnerBinding {
    DL list;
    void *object;
    void **slot;
};
struct OwnerSettings {
    char prefix[0xD8];
    int mode;
    char reservedDC[0xC];
    OwnerBinding binding;
};
struct OwnerEntry { short delta, reserved; void (*method)(void *); };
struct BoundOwner { char prefix[0xC]; OwnerEntry *table; };

extern "C" void func_0011B028(DL *list, void *object);

extern "C" void func_001FE8C8(void *settings, void *object)
{
    OwnerSettings *ownerSettings = (OwnerSettings *)settings;
    switch (ownerSettings->mode) {
    case 1:
    case 3:
        ownerSettings->binding.object = 0;
        break;
    case 2:
        *ownerSettings->binding.slot = 0;
        break;
    case 0:
        func_0011B028(&ownerSettings->binding.list, object);
        break;
    }
    OwnerEntry *entry = &((BoundOwner *)object)->table[2];
    entry->method((char *)object + entry->delta);
}
