// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "scene.h"
#include "vector_intrinsics.h"
struct ActorMatrix { qword row[4]; };
struct Actor { char prefix[0xC]; SCENE_VIRTUAL_ENTRY *table; char gap10[0x238]; float height; };
extern "C" {
void func_001F3C48(Actor *actor);
void func_00215640(Actor *actor);
void func_002194B0(Actor *actor);
void func_00213F08(Actor *actor)
{
    SCENE_VIRTUAL_ENTRY *entry;
    ActorMatrix *matrix;
    func_001F3C48(actor);
    func_00215640(actor);
    func_002194B0(actor);
    entry = &actor->table[36];
    matrix = ((ActorMatrix *(*)(void *))entry->Simple)((char *)actor + entry->delta);
    actor->height = PackedVectorZ(matrix->row[3]);
}
}
