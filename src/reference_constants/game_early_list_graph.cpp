// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Move ready nodes, then repeatedly process the node with the lowest negative cost.
// GRAPH_VIEW names the accessed prefix; the caller constructs the full graph.
struct LIST {
    void *head;
    void *tail;
    int linkOffset;
};
struct ITERATOR {
    LIST *list;
    void **nextLink;
    int linkOffset;
    ITERATOR *previous;
};
struct GRAPH_NODE {
    int state;
    char gap4[0x10-4];
    float cost;
    char gap14[0x20-0x14];
    GRAPH_NODE *next;
    GRAPH_NODE *previous;
};
struct GRAPH_VIEW {
    char prefix[0xC];
    LIST completed;
    char gap18[0x30-0x18];
    LIST pending;
    int completedCount;
};
struct EmptyCleanup {
    char unused;
};
typedef char CheckIterator16[(sizeof(ITERATOR)==16)?1:-1];
typedef char CheckGraphNode40[(sizeof(GRAPH_NODE)==40)?1:-1];
extern ITERATOR *D_0036AE94;
extern "C" {
    void func_0011B028(LIST *,void *);
    void func_0011AF60(LIST *,void *);
    void func_0011B4B0(GRAPH_VIEW *,GRAPH_NODE *);
    void func_002BA690(void *,int);
}
static inline void InitIterator(ITERATOR *iterator,LIST *list) {
    iterator->list=list;
    iterator->nextLink=(void **)list;
    iterator->linkOffset=list->linkOffset;
    iterator->previous=D_0036AE94;
    D_0036AE94=iterator;
}
static inline void *Next(ITERATOR *iterator) {
    void *node=*iterator->nextLink;
    iterator->nextLink=(void **)((unsigned int)node+iterator->linkOffset);
    return node;
}
extern "C" void func_0011B968(GRAPH_VIEW *graph) {
    ITERATOR iterator;
    GRAPH_NODE *node;
    InitIterator(&iterator,&graph->pending);
    while ((node=(GRAPH_NODE *)Next(&iterator))!=0) {
        if (node->state==1) {
            func_0011B028(&graph->pending,node);
            func_0011AF60(&graph->completed,node);
            graph->completedCount++;
        }
    }
    func_0011B4B0(graph,0);
    D_0036AE94=iterator.previous;
    for (;;) {
        GRAPH_NODE *best=0;
        float minimum=-0.01f;
        EmptyCleanup cleanup;
        for (GRAPH_NODE *candidate=(GRAPH_NODE *)graph->pending.head;candidate;candidate=candidate->next) {
            if (candidate->cost<minimum) {
                minimum=candidate->cost;
                best=candidate;
            }
        }
        func_002BA690(&cleanup,2);
        if (!best) break;
        func_0011B4B0(graph,best);
    }
}
