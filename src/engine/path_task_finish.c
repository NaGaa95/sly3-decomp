// SLY3_CFLAGS: -Os -G0
#include "path_task_api.h"
#include "resource_attachment_api.h"
struct PathTaskMatrix { PathTaskPacked row[4]; };
struct PathTaskMethod {
    short delta, padding;
    union {
        void (*method)(void *);
        struct PathTaskMatrix *(*matrix)(void *);
    } call;
};
struct PathTaskObject { char unaccessed[0xC]; struct PathTaskMethod *table; };
struct PathTaskLink { char unaccessed[0x1C]; int word1C; float time20; };
struct PathTaskRecord {
    struct PathTaskObject *object;
    unsigned int unaccessed4;
    float time;
    struct PathTaskLink *link;
    int mode;
    char unaccessed14[0xC];
    PathTaskPacked point;
};
struct PathTaskOwner {
    char unaccessed[0x48];
    int active_count;
    char unaccessed4C[0x90-0x4C];
    float delay90, delay94;
};
struct PathTaskClock { float now; };
extern struct PathTaskClock D_0036BB98;
extern char D_00475480[];
void *func_001FC118(void *object);
void func_001FC0E0(void *resource, void *object);
void *func_001F4AD0(void *unused, int index);
void *func_00165B28(void *game);

void func_00199118(void *owner_address, void *record_address, int mode, int flags)
{
    struct PathTaskOwner *owner = owner_address;
    struct PathTaskRecord *record = record_address;
    func_0013BD88(record->object, (int)owner);
    record->mode = mode;
    switch (mode) {
    case 0:
        {
            struct PathTaskObject *object = record->object;
            struct PathTaskMethod *method;
            void *resource;
            record->time = D_0036BB98.now;
            method = &object->table[9];
            method->call.method((char *)object + method->delta);
            resource = func_001FC118(record->object);
            if (resource)
                func_001FC0E0(resource, record->object);
        }
        if ((flags ^ 1) & 1)
            record->link->time20 = D_0036BB98.now;
        break;
    case 2:
        record->time = D_0036BB98.now;
        if ((flags ^ 1) & 1)
            record->link->time20 = D_0036BB98.now;
        break;
    case 1:
        record->time = D_0036BB98.now + owner->delay90;
        record->point = func_00199270(owner);
        if ((flags ^ 1) & 1)
            record->link->time20 = D_0036BB98.now + owner->delay94;
        break;
    }
    record->object = 0;
    record->link->word1C = 0;
    record->link = 0;
    --owner->active_count;
}

static inline PathTaskPacked path_task_position(struct PathTaskObject *object)
{
    struct PathTaskMethod *method = &object->table[36];
    return method->call.matrix((char *)object + method->delta)->row[3];
}

PathTaskPacked func_00199270(void *unused_owner)
{
    if (func_001F4AD0(D_00475480, 0))
        return path_task_position(func_001F4AD0(D_00475480, 0));
    return path_task_position(func_00165B28(D_00475480));
}
