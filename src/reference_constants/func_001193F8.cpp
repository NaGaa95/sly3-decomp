// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Read collision positions/surfaces and link the original16-byte edge records.
// Reuse the native temporary for allocation parameters and later vertex indices.
#include "archive_collision_types.h"
extern "C" unsigned int func_00119048(void *stream);
extern "C" unsigned int func_00118FF8(void *stream);
extern "C" float func_00119260(void *stream);
extern "C" void func_001192D8(void *stream,void *position);
extern "C" void *func_001D2470(ALLOCREQ *request);
extern "C" void *func_001D2538(ALLOCREQ *request);
extern "C" void func_00119E20(CollisionSurface *surface,qword position0,qword position1,qword position2);
extern "C" void func_001193F8(void *stream,CollisionGeometry *geometry)
{
    union { ALLOCREQ allocation; unsigned int vertexIndices[3]; } scratch;
    CollisionEdge *nextEdge;
    {
        geometry->positionCount=func_00119048(stream);
        scratch.allocation.cb=geometry->positionCount*sizeof(qword);
        scratch.allocation.cbAlign=16;
        geometry->positions=(qword *)func_001D2470(&scratch.allocation);
        for(int positionIndex=0;positionIndex<geometry->positionCount;positionIndex++) func_001192D8(stream,&geometry->positions[positionIndex]);
        geometry->surfaceCount=func_00119048(stream);
        scratch.allocation.cb=geometry->surfaceCount*sizeof(CollisionSurface);
        scratch.allocation.cbAlign=16;
        geometry->surfaces=(CollisionSurface *)func_001D2538(&scratch.allocation);
        geometry->edgeCount=func_00119048(stream);
        scratch.allocation.cb=geometry->edgeCount*sizeof(CollisionEdge);
        scratch.allocation.cbAlign=16;
        geometry->edges=(CollisionEdge *)func_001D2538(&scratch.allocation);
        nextEdge=geometry->edges;
    }
    for(int i=0;i<geometry->surfaceCount;i++) {
        CollisionSurface *surface=&geometry->surfaces[i];
        scratch.vertexIndices[0]=func_00119048(stream);
        scratch.vertexIndices[1]=func_00119048(stream);
        scratch.vertexIndices[2]=func_00119048(stream);
        func_00119E20(surface,geometry->positions[scratch.vertexIndices[0]],geometry->positions[scratch.vertexIndices[1]],geometry->positions[scratch.vertexIndices[2]]);
        surface->firstVertex=scratch.vertexIndices[0];
        for(int j=3;j>=0;j--) func_00119260(stream);
        int edgeCount=func_00118FF8(stream);
        for(int k=0;k<edgeCount;k++) {
            CollisionEdge *edge=nextEdge++;
            edge->vertices[0]=func_00119048(stream);
            edge->vertices[1]=func_00119048(stream);
            edge->surfaces[0]=i;
            edge->surfaces[1]=func_00119048(stream);
            if(k==0) surface->edges=edge;
            else (edge-1)->next=edge;
            CollisionSurface *other=&geometry->surfaces[edge->surfaces[1]];
            edge->otherNext=other->incoming;
            other->incoming=edge;
        }
    }
}
