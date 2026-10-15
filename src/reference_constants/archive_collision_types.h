#ifndef SLY3_PRIVATE_COLLISION_TYPES_H
#define SLY3_PRIVATE_COLLISION_TYPES_H
#include "../../src/P2/heap.h"
struct CollisionEdge;
struct CollisionSurface {
    float normal[3];
    float planeDistance;
    CollisionEdge *edges;
    CollisionEdge *incoming;
    unsigned int unused18;
    unsigned int firstVertex;
};
struct CollisionEdge {
    unsigned short vertices[2];
    unsigned short surfaces[2];
    CollisionEdge *next;
    CollisionEdge *otherNext;
};
struct CollisionGeometry {
    int positionCount;
    qword *positions;
    int surfaceCount;
    CollisionSurface *surfaces;
    int edgeCount;
    CollisionEdge *edges;
};
struct CollisionTreeNode {
    CollisionTreeNode *child0;
    CollisionTreeNode *child4;
    void *surface;
};
struct CollisionTree {
    int nodeCount;
    int metadata4;
    int metadata8;
    CollisionTreeNode *nodes;
};
typedef char CollisionSurfaceSize[(sizeof(CollisionSurface)==32)?1:-1];
typedef char CollisionEdgeSize[(sizeof(CollisionEdge)==16)?1:-1];
typedef char CollisionGeometrySize[(sizeof(CollisionGeometry)==24)?1:-1];
typedef char CollisionTreeNodeSize[(sizeof(CollisionTreeNode)==12)?1:-1];
typedef char CollisionTreeSize[(sizeof(CollisionTree)==16)?1:-1];
#endif
