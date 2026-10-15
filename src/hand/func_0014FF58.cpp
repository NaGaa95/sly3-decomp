// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "../../src/P2/heap.h"
#include "../../src/P2/bis.h"

struct ArchiveHierarchyNode {
    VECTOR4 vector;
    ArchiveHierarchyNode *firstLink;
    ArchiveHierarchyNode *secondLink;
    int firstEndpoint;
    int secondEndpoint;
};
typedef char ArchiveHierarchyNodeSize[(sizeof(ArchiveHierarchyNode)==32)?1:-1];
struct ArchiveHierarchyGame {
    byte beforeHierarchy[0x4D8C];
    int nodeCount;
    ArchiveHierarchyNode *nodes;
    int endpointCount;
    ArchiveHierarchyNode *endpoints;
};
struct ArchiveSerializedHierarchyNode {
    float vector[4];
    short firstLink;
    short secondLink;
};
typedef char ArchiveSerializedHierarchyNodeSize[(sizeof(ArchiveSerializedHierarchyNode)==20)?1:-1];

extern "C" {
extern byte D_0036BC10[];
int func_00169150(void *selection,int identity);
void *func_001D2538(ALLOCREQ *request);

void func_0014FF58(ArchiveHierarchyGame *game,CBinaryInputStream *stream)
{
    int groupCount=stream->U8Read();
    if(groupCount>0) {
        int remaining=groupCount;
        do {
            int identity=stream->S32Read();
            int nodeCount=stream->U16Read();
            if(!func_00169150(D_0036BC10,identity)) {
                stream->Skip(nodeCount*sizeof(ArchiveSerializedHierarchyNode));
            } else {
                game->nodeCount=nodeCount;
                ALLOCREQ request;
                request.cb=game->nodeCount*sizeof(ArchiveHierarchyNode);
                request.cbAlign=16;
                game->nodes=(ArchiveHierarchyNode *)func_001D2538(&request);
                game->endpointCount=0;
                for(int index=0;index<game->nodeCount;++index) {
                    ArchiveHierarchyNode *node=game->nodes+index;
                    stream->ReadVector4(&node->vector);
                    int first=stream->S16Read();
                    if(first>=0) node->firstLink=game->nodes+first;
                    else node->firstEndpoint=game->endpointCount++;
                    int second=stream->S16Read();
                    if(second>=0) node->secondLink=game->nodes+second;
                    else node->secondEndpoint=game->endpointCount++;
                }
                request.cb=game->endpointCount*sizeof(ArchiveHierarchyNode);
                request.cbAlign=16;
                game->endpoints=(ArchiveHierarchyNode *)func_001D2538(&request);
            }
        } while(--remaining);
    }
}
}
