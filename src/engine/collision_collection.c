// SLY3_CFLAGS: -Os -G0
struct CollectionAllocationRequest {
    int bytes, alignment;
};
struct CollisionCollection {
    int capacity;
    char unused04[0x4C];
    int first_count;
    void **first_objects;
    int second_count;
    void **second_objects;
    void *records;
    void *previous;
};
extern void *D_0036AEAC;
void *func_0011B290(void *receiver, int capacity);
void *func_001D2670(struct CollectionAllocationRequest *request);
struct CollisionCollection *func_001757D0(struct CollisionCollection *collection,
    int first_count, void **first_objects, int second_count, void **second_objects)
{
    struct CollectionAllocationRequest request;
    func_0011B290(collection, (int)(2u*(unsigned int)first_count));
    collection->first_count=first_count;
    collection->first_objects=first_objects;
    collection->second_count=second_count;
    collection->second_objects=second_objects;
    request.alignment=0x10;
    request.bytes=(int)(0x60u*(unsigned int)collection->capacity);
    collection->records=func_001D2670(&request);
    collection->previous=D_0036AEAC;
    D_0036AEAC=collection;
    return collection;
}
