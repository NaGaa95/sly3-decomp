// Registered slot33 getter following the complete original 292-byte loader.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ParticleListView { char prefix[0xD0]; int count; void *objects; };
extern "C" int func_00179FD0(ParticleListView *collection, void **objects)
{
    *objects = collection->objects;
    return collection->count;
}
