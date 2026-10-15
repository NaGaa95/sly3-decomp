// Return the retained object written by the six-input constructor helper.
void func_00239808(void *, void *, int, int, int, void **);
void *func_002399F0(void *resource, void *receiver, int identifier, int mode, int mask)
{
    void *retained;
    func_00239808(resource, receiver, identifier, mode, mask, &retained);
    return retained;
}
