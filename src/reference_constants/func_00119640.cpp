// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Read raw tree indices and resolve them into the original geometry/node arrays.
#include "archive_collision_types.h"
extern "C" unsigned int func_001190A8(void *stream);
extern "C" unsigned int func_00119048(void *stream);
extern "C" void *func_001D2538(ALLOCREQ *request);
extern "C" char D_00341DD0[];
extern "C" void func_00119640(void *stream,CollisionGeometry *geometry,CollisionTree *tree)
{
    int i;
    ALLOCREQ request;
    tree->nodeCount=func_001190A8(stream);
    tree->metadata4=func_001190A8(stream);
    tree->metadata8=func_001190A8(stream);
    request.cb=tree->nodeCount*sizeof(CollisionTreeNode);
    request.cbAlign=16;
    tree->nodes=(CollisionTreeNode *)func_001D2538(&request);
    for(i=0;i<tree->nodeCount;i++) {
        CollisionTreeNode *node=&tree->nodes[i];
        unsigned int surfaceIndex=func_00119048(stream);
        if(surfaceIndex==0xFFFF) {
            node->surface=D_00341DD0;
        } else {
            unsigned int childIndex;
            node->surface=&geometry->surfaces[surfaceIndex];
            childIndex=func_001190A8(stream);
            if(childIndex!=0xFFFFFFFF) node->child0=&tree->nodes[childIndex];
            childIndex=func_001190A8(stream);
            if(childIndex!=0xFFFFFFFF) node->child4=&tree->nodes[childIndex];
        }
    }
}
