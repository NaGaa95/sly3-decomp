// Actual pointer-valued input node lookup, with the caller's concrete opaque types.
struct INPUT_PRIORITY_NODE;
struct INPUT_CONTROLLER_RESOLVED;
struct InputLookupFields {
    char prefix[0xE8];
    int count;
    struct INPUT_CONTROLLER_RESOLVED *pointer;
};
struct INPUT_CONTROLLER_RESOLVED *func_001662A8(struct INPUT_PRIORITY_NODE *node) {
    struct InputLookupFields *fields=(struct InputLookupFields *)node;
    struct INPUT_CONTROLLER_RESOLVED *result=0;
    if(fields->count>0)result=fields->pointer;
    return result;
}
