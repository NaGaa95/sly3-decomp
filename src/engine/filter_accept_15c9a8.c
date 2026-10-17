// SLY3_CFLAGS: -Os -G0
struct FilterPair { int key; int flag; };
struct FilterItem { unsigned char prefix[0x10]; int id; };
struct FilterSelf {
    unsigned char prefix[0x148];
    int countB;
    struct FilterPair pairs[4];
    unsigned char gap16C[0x18C-0x16C];
    int countC;
    int listC[0x26];
    int countA;
    int listA[8];
};
int func_0013B500(void *object, int kind);
int func_0015C9A8(struct FilterSelf *self, struct FilterItem *item, int unused2, int unused3, int key)
{
    int i, j, k;
    for(i = 0; i < self->countA; i++) {
        if(self->listA[i] == item->id) return 0;
    }
    if(self->countB > 0) {
        for(j = 0; j < self->countB; j++) {
            struct FilterPair *pair = &self->pairs[j];
            if(pair->flag && pair->key == key) break;
        }
        if(j >= self->countB) return 0;
    }
    if(self->countC > 0) {
        for(k = 0; k < self->countC; k++) {
            if(func_0013B500((void *)key, self->listC[k])) break;
        }
        if(k >= self->countC) return 0;
    }
    return 1;
}
