// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "../P2/bis.h"
#include "../P2/heap.h"
#include "heap_frame_api.h"
struct ModelTransform { char prefix[0x40]; MATRIX4 matrix; };
struct ModelDescriptor { char channel, segments; char flags; char kind; char pad4[4]; void *chain; char padC[4]; int words; };
union ModelEntryFlags { unsigned int word; struct { unsigned int pad : 12, feature : 1, rest : 19; } bits; };
struct ModelEntry {
    int value;
    ModelTransform *transform;
    MATRIX4 *parent;
    ModelEntryFlags flags;
    char *data;
    unsigned int base;
    char pad18[12];
    void *sphere;
};
struct ModelSphere { float center[3], radius, limit; unsigned int metadata; };
struct ModelMethod { short delta, unused; ModelTransform *(*method)(void *, int); };
struct ModelOwner { char prefix[0xC]; ModelMethod *methods; };
struct ModelLoader { ModelOwner *owner; };
struct ModelLink { short first, second; unsigned char kind, pad; };
struct ModelLinkSet { int group, pad4; ModelLink *links; };
struct ModelBinding { int count; ModelLinkSet *sets; };
struct ModelFace {
    int count, pad4;
    unsigned int flags;
    char padC[8];
    int *indices;
    char pad18[16];
    int first, second, pad30, kind;
    char pad38[12];
};
typedef char ModelDescriptorSize[(sizeof(ModelDescriptor) == 20) ? 1 : -1];
typedef char ModelEntrySize[(sizeof(ModelEntry) == 40) ? 1 : -1];
typedef char ModelSphereSize[(sizeof(ModelSphere) == 24) ? 1 : -1];
typedef char ModelFaceSize[(sizeof(ModelFace) == 68) ? 1 : -1];
typedef char ModelLinkSize[(sizeof(ModelLink) == 6) ? 1 : -1];
typedef char ModelLinkSetSize[(sizeof(ModelLinkSet) == 12) ? 1 : -1];
extern "C" {
void *func_001D2470(ALLOCREQ *request);
void *func_001D24D0(ALLOCREQ *request, void *old);
MATRIX4 *func_0011D558(MATRIX4 *out, const MATRIX4 *first, const MATRIX4 *second);
ModelBinding *func_001929B0(ModelLoader *loader, CBinaryInputStream *stream);
}
static __inline__ ALLOCREQ *allocation_request(ALLOCREQ *request, int bytes, int alignment)
{
    request->cb = bytes;
    request->cbAlign = alignment;
    return request;
}
static __inline__ ModelTransform *ReadModelTransform(ModelOwner *owner, CBinaryInputStream *stream)
{
    ModelMethod *entry = &owner->methods[55];
    void *adjusted = (char *)owner + entry->delta;
    int index = stream->S16Read();
    return entry->method(adjusted, index);
}
extern "C" void func_0018F7B0(ModelLoader *loader, const ModelDescriptor *sourceDescriptor, const ModelEntry *sourceEntry, const ModelSphere *sourceSphere,
                              ModelDescriptor *descriptor, ModelEntry *entry, ModelSphere *sphere, int groups, const int *counts, ModelFace **faces,
                              CBinaryInputStream *stream)
{
    MATRIX4 matrix;
    ALLOCREQ request;
    unsigned char frame[16];
    ModelBinding *binding;
    stream->S8Read(); /* two header bytes of the record are read and ignored */
    stream->S8Read();
    *descriptor = *sourceDescriptor;
    *entry = *sourceEntry;
    if(sphere) {
        *sphere = *sourceSphere;
        sphere->metadata = stream->U32Read();
    }
    entry->transform = ReadModelTransform(loader->owner, stream);
    if(entry->flags.word & 0x2000) stream->ReadMatrix4(&matrix);
    else {
        entry->parent = (MATRIX4 *)func_001D2470(allocation_request(&request, sizeof(MATRIX4), 16));
        stream->ReadMatrix4(entry->parent);
    }
    entry->value = stream->S32Read();
    entry->flags.bits.feature = stream->S8Read();
    func_001D2770(frame);
    binding = func_001929B0(loader, stream);
    int descriptorFlags = descriptor->flags;
    if(!(descriptorFlags & 3) && descriptor->kind == 0) {
        char *old = entry->data;
        char *data;
        unsigned int delta;
        data = (char *)func_001D24D0(allocation_request(&request, descriptor->words << 4, 16), old);
        delta = (unsigned int)data - (unsigned int)old;
        entry->data = data;
        entry->base += delta;
        if(entry->flags.word & 0x2000) {
            MATRIX4 product, temp;
            func_0011D558(&temp, &entry->transform->matrix, &matrix);
            product = temp;
            CopyAb(entry->data + 0x14, &product, sizeof(MATRIX4));
        }
        if(binding) {
            for(int g = 0; g < groups; g++) {
                int count = counts[g];
                ModelFace *set = faces[g];
                for(int i = 0; i < count; i++) {
                    ModelFace *face = &set[i];
                    if(face->flags & 0x20) {
                        unsigned int base = entry->base;
                        unsigned short *first = (unsigned short *)(face->first + base);
                        unsigned short *second = (unsigned short *)(face->second + base);
                        unsigned char *kind = (unsigned char *)(face->kind + base);
                        ModelLinkSet *links; /* the set of group g; the original leaves it unassigned when the binding has no sets */
                        for(int k = 0; k < binding->count; k++) {
                            links = &binding->sets[k];
                            if(links->group == g) break;
                        }
                        for(int j = 0; j < face->count; j++) {
                            int index = face->indices[j];
                            first[j] = links->links[index].first;
                            second[j] = links->links[index].second;
                            kind[j] = links->links[index].kind;
                        }
                    }
                }
            }
        }
    }
    func_001D2798(frame, 2);
}
