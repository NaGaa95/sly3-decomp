// SLY3_CFLAGS: -Os -G0
#include "heap_frame_api.h"

struct PathSample { float point[4]; float direction[4]; };
struct PathSetupPath { char unaccessed[0x170]; void *regions; };
struct PathSetupTemplate { char unaccessed[0x44]; unsigned int word44; };
struct PathSetupEntry {
    int kind, key;
    struct PathSetupPath *path;
    struct PathSetupTemplate *object;
    unsigned int word10;
    int sample_count;
    struct PathSample *samples;
    unsigned int unaccessed1C[2];
};
struct PathSetupOwner {
    char unaccessed[0x3C];
    unsigned int tagged;
    int count;
    struct PathSetupEntry *entries;
    unsigned int unaccessed48;
    int output_count;
    void *output;
};
struct PathSetupAllocation { int bytes, alignment; };
extern char D_00475480[];
void func_001C7DC8(void *receiver);
void *func_0017E1B8(void *game, int flags, int key, void *context);
void func_00231948(struct PathSetupPath *path);
struct PathSetupTemplate *func_00150690(int type, void *owner, int key, int parent);
void *func_001973B8(struct PathSetupTemplate *object, int key, int first,
                  int second, int third, int last);
float func_0022DFD8(struct PathSetupPath *path);
void *func_002320A0(void *regions, float parameter);
void func_0022E330(struct PathSetupPath *path, void *point, void *direction,
                  float parameter);
void *func_001D25B0(struct PathSetupAllocation *request);
void *func_001D24D0(struct PathSetupAllocation *request, void *allocation);
void *func_001D2538(struct PathSetupAllocation *request);
void func_001C9118(void *receiver, int state);

static inline struct PathSetupAllocation *allocation_request(
    struct PathSetupAllocation *request, int bytes, int alignment)
{
    request->bytes = bytes;
    request->alignment = alignment;
    return request;
}

void func_00198A50(struct PathSetupOwner *owner)
{
    int i;
    unsigned char frame[16];
    struct PathSetupAllocation allocation;
    unsigned int flags;
    func_001C7DC8(owner);
    for (i = 0; i < owner->count; ++i) {
        struct PathSetupEntry *entry = &owner->entries[i];
        switch (entry->kind) {
        case 1:
            {
                struct PathSetupPath *path;
                struct PathSetupTemplate *object;
                int j, capacity;
                struct PathSetupAllocation *request;
                path = func_0017E1B8(D_00475480, 5, entry->key, 0);
                entry->path = path;
                func_00231948(path);
                object = func_00150690(0x86, 0, 0x322, -1);
                func_001973B8(object, entry->key, 1, -1, -1, 1);
                entry->word10 = object->word44;
                entry->object = object;
                capacity = (int)(func_0022DFD8(entry->path) * 0.001f);
                func_001D2770(frame);
                request = &allocation;
                entry->sample_count = 0;
                entry->samples = func_001D25B0(
                    allocation_request(request, capacity * 32, 16));
                for (j = 0; j < capacity; ++j) {
                    float parameter = (float)j * 1000.0f;
                    if (!func_002320A0(path->regions, parameter)) {
                        struct PathSample *sample = &entry->samples[entry->sample_count++];
                        func_0022E330(path, sample->point, sample->direction, parameter);
                    }
                }
                {
                    struct PathSample *previous = entry->samples;
                    entry->samples = func_001D24D0(
                        allocation_request(&allocation, entry->sample_count * 32, 16),
                        previous);
                }
                func_001D2798(frame, 2);
            }
            break;
        case 0:
        case 2:
            entry->path = func_0017E1B8(D_00475480, 5, entry->key, 0);
            break;
        }
    }
    owner->output = func_001D2538(
        allocation_request(&allocation, owner->output_count * 48, 16));
    func_001C9118(owner, 1);
    flags = owner->tagged;
    if ((flags ^ 1) & 1)
        *(unsigned int *)flags |= 2;
    else
        owner->tagged = flags | 2;
}
