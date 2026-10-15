// SLY3_CFLAGS: -Os -G0
struct Q;
struct QueryContextPrefix { char opaque[0xF0]; int endpoint_count; };
struct QueryCache {
    unsigned int x_bits[4];
    unsigned int y_bits[4];
    int generation;
    int first_x;
    int last_x;
    int first_y;
    int last_y;
    char unused34[0xC];
};
void *func_00292034(void *destination, int value, unsigned int bytes);

void func_001EDD18(struct Q *source, void *storage)
{
    struct QueryContextPrefix *context = (struct QueryContextPrefix *)source;
    struct QueryCache *cache = (struct QueryCache *)storage;
    int first, second;
    func_00292034(cache, 0, sizeof(*cache));
    first = context->endpoint_count - 2;
    cache->first_x = cache->last_x = first;
    second = context->endpoint_count - 2;
    cache->generation = -1;
    cache->first_y = cache->last_y = second;
}
