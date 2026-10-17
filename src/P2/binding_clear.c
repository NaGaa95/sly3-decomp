// SLY3_CFLAGS: -Os -G0
struct Binding {
    unsigned char prefix[0x194];
    int index;
    void *resource;
    void *object;
};
void func_001FC090(void *, void *);
void func_001F2950(struct Binding *binding)
{
    if (binding->resource && binding->object)
        func_001FC090(binding->resource, binding->object);
    binding->object = 0;
    binding->resource = 0;
    binding->index = 0;
}
