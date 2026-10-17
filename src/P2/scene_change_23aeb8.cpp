// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-gcse
#include "scene.h"
#include "mat.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
struct ChangeNode {
    MATRIX4 local;
    MATRIX4 world;
    char pad80[0xA0 - 0x80];
    ChangeNode *parent;
    int generation;
    char padA8[0x100 - 0xA8];
};
struct ChangeOwner {
    char prefix[0x40];
    int count;
    ChangeNode *nodes;
    char pad48[0x128 - 0x48];
    unsigned long flags;
};
struct ChangeEntry {
    short delta;
    short pad;
    void *call;
};
struct ChangeState {
    char prefix[0xC];
    ChangeEntry *vtable;
    ChangeOwner *owner;
    char pad14[0x28 - 0x14];
    SCENE_PACKED_STATE flags;
    char pad30[0x40 - 0x30];
    int count;
    ChangeNode *nodes;
    void *firstBounds;
    void *secondBounds;
    ChangeNode *attached;
};
struct ChangeGlobals { char prefix[0x44F4]; int generation; };
extern "C" ChangeGlobals D_00475480;
extern "C" void *func_00292034(void *, int, unsigned int);
extern "C" MATRIX4 *func_0011D558(MATRIX4 *, const MATRIX4 *, const MATRIX4 *);
extern "C" void func_0011D768(MATRIX4 *, const MATRIX4 *);
extern "C" void func_001C7A30(ChangeState *, void *, void *, int);
extern "C" void func_0023DF78(void *);
extern "C" void func_0028F260(void *, void *);
extern "C" void func_0023C8F8(void *);
extern "C" void func_0023B310(void *);
extern "C" void func_0023B550(void *);
extern "C" void func_00241F00(void *, int);
extern "C" void func_0023AEB8(ChangeState *self, ChangeState *owner, ChangeNode *parent, int flags)
{
    MATRIX4 world;
    MATRIX4 accumulated;
    MATRIX4 combined;
    MATRIX4 product;
    MATRIX4 inverseFirst;
    MATRIX4 inverseCombined;
    MATRIX4 inverseAccumulated;
    Quadword firstResult, secondResult;
    if (flags & 0x13) {
        int inherited = self->flags.fields.inherited;
        if (inherited) {
            world = *(MATRIX4 *)((char *)self->attached + 0x40);
        } else {
            func_00292034(&world, 0, 0x40);
            world.mat[0][0] = world.mat[1][1] = world.mat[2][2] = world.mat[3][3] = 1.0f;
            for (ChangeNode *node = self->attached; node; node = node->parent) {
                func_0011D558(&accumulated, &node->local, &world);
                world = accumulated;
            }
        }
    }
    int wantFirst = flags & 4;
    if (wantFirst) {
        ChangeEntry *entry = &self->vtable[38];
        firstResult = ((Quadword (*)(void *))entry->call)((char *)self + entry->delta);
    }
    int wantSecond = flags & 8;
    if (wantSecond) {
        ChangeEntry *entry = &self->vtable[39];
        secondResult = ((Quadword (*)(void *))entry->call)((char *)self + entry->delta);
    }
    int span;
    ChangeNode *base;
    if (self->owner) {
        span = self->owner->count;
        base = self->owner->nodes;
    } else {
        span = 1;
        base = 0;
    }
    ChangeNode *newParent = parent ? parent : owner ? owner->attached : 0;
    for (int i = 0; i < self->count; ++i) {
        ChangeNode *node = &self->nodes[i];
        int index = node->parent - base;
        if (index >= 0 && index < span)
            node->parent = newParent;
    }
    func_001C7A30(self, owner, parent, flags);
    if (flags & 1) {
        ChangeEntry *entry = &self->vtable[34];
        ((void (*)(void *, Quadword))entry->call)((char *)self + entry->delta, *(Quadword *)&world.mat[3][0]);
    }
    if (flags & 2) {
        ChangeEntry *entry = &self->vtable[35];
        ((void (*)(void *, MATRIX4 *))entry->call)((char *)self + entry->delta, &world);
    }
    if (flags & 0x10) {
        MATRIX4 *matrix = &accumulated;
        func_00292034(matrix, 0, 0x40);
        matrix->mat[0][0] = matrix->mat[1][1] = matrix->mat[2][2] = matrix->mat[3][3] = 1.0f;
        for (ChangeNode *node = self->attached; node != self->nodes; node = node->parent) {
            func_0011D558(&product, &node->local, matrix);
            accumulated = product;
        }
        MATRIX4 *other = &combined;
        func_00292034(other, 0, 0x40);
        other->mat[0][0] = other->mat[1][1] = other->mat[2][2] = other->mat[3][3] = 1.0f;
        for (ChangeNode *node = self->nodes->parent; node; node = node->parent) {
            func_0011D558(&product, &node->local, other);
            combined = product;
        }
        MATRIX4 *inverseOne = &inverseCombined;
        MATRIX4 *first = &inverseFirst;
        MATRIX4 *result = &product;
        ChangeNode *target = self->nodes;
        func_0011D768(inverseOne, &combined);
        func_0011D558(first, inverseOne, &world);
        MATRIX4 *inverseTwo = &inverseAccumulated;
        func_0011D768(inverseTwo, &accumulated);
        func_0011D558(result, first, inverseTwo);
        target->local = product;
        int generation = ++D_00475480.generation;
        self->nodes->generation = generation;
        ChangeEntry *update = &self->vtable[20];
        ((void (*)(void *))update->call)((char *)self + update->delta);
        func_0023DF78(self);
        func_0028F260(self, self->secondBounds);
        func_0023C8F8(self);
    }
    if (wantFirst) {
        ChangeEntry *entry = &self->vtable[40];
        ((void (*)(void *, Quadword))entry->call)((char *)self + entry->delta, firstResult);
    }
    if (wantSecond) {
        ChangeEntry *entry = &self->vtable[41];
        ((void (*)(void *, Quadword))entry->call)((char *)self + entry->delta, secondResult);
    }
    func_0023B310(self);
    func_0023B550(self);
    if (self->owner && !(self->owner->flags & 8))
        func_00241F00(self, 0);
}
