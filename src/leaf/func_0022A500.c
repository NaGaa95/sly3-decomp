// SLY3_CFLAGS: -Os -G0
// Resolve a parameter chain node: look up its two resource ids, take its start value (or accumulate the chained scalar
// parameters when the start is zero) and follow the chain of 11-bit parameter indices (tag bits 20..30) until a kind 0x45
// node is found, which is resolved the same way and returned (0 when the chain ends without one).
struct PARAMETER_DATA {
    unsigned char unknown00[0x28];
    float accumulated;
    int unknown2C;
    void *resolvedA;
    void *resolvedB;
    unsigned char unknown38[0x50 - 0x38];
    float start;
    int idA;
    int idB;
};
struct PARAMETER {
    union { unsigned int word; struct { unsigned char kind; unsigned char flags; unsigned short reserved; } fields; } tag;
    int unknown4;
    struct PARAMETER_DATA *data;
    float alternateValue;
};
struct PARAMETER_TABLE { unsigned char unknown[0x44]; struct PARAMETER *entries; };
struct PARAMETER_CONTEXT { unsigned char unknown[0x14]; struct PARAMETER_TABLE *table; };
void *func_002267E8(struct PARAMETER_CONTEXT *context, int id);
void func_00226AE8(struct PARAMETER_CONTEXT *context, int key);
float func_0022A670(struct PARAMETER_CONTEXT *context, struct PARAMETER *parameter);
static inline struct PARAMETER *NextParameter(struct PARAMETER_CONTEXT *context, struct PARAMETER *parameter)
{
    unsigned int index = (parameter->tag.word >> 20) & 0x7FF;
    struct PARAMETER_TABLE *table = context->table;
    return index ? &table->entries[index] : 0;
}
struct PARAMETER *func_0022A500(struct PARAMETER_CONTEXT *context, struct PARAMETER *head)
{
    struct PARAMETER *found;
    struct PARAMETER *current;
    int sumChain;
    head->data->resolvedA = func_002267E8(context, head->data->idA);
    head->data->resolvedB = func_002267E8(context, head->data->idB);
    if (head->data->start == 0.0f) {
        sumChain = 1;
        head->data->accumulated = 0.0f;
    } else {
        head->data->accumulated = head->data->start;
        sumChain = 0;
    }
    found = 0;
    for (current = NextParameter(context, head); current; current = NextParameter(context, current)) {
        if (current->tag.fields.kind == 0x45) {
            current->data->resolvedA = func_002267E8(context, current->data->idA);
            current->data->resolvedB = func_002267E8(context, current->data->idB);
            found = current;
            break;
        }
        if (current->tag.fields.kind == 0x18)
            func_00226AE8(context, (int)current->data);
        if (sumChain)
            head->data->accumulated += func_0022A670(context, current);
    }
    return found;
}
