// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct KeySet {
    unsigned char pad[0x40];
    int result;
    int count;
    int *keys;
};
int func_00186200(struct KeySet *set, int key)
{
    int i;
    int count = set->count;
    if (count == 0) {
        return set->result;
    }
    for (i = 0; i < count; i++) {
        if (key == set->keys[i]) {
            return set->result;
        }
    }
    return 0;
}
