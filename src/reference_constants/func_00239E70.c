// Complete original function, inputs and emitted data independently reviewed.
// Query the actual requested scalar identifier through the bounded record list.
struct Request {
    char prefix[0x24];
    void *list;
    char padding[0x34-0x28];
    int requested_index;
};
int func_00239B80(void *list, int index);
int func_00239E70(void *record) {
    struct Request *request = record;
    return func_00239B80(request->list, request->requested_index);
}
