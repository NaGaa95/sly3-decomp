// Forward the real resource/receiver pointers and caller-owned output pointer.
void func_00239808(void *, void *, int, int, int, void **);
void func_002397E8(void *resource, void *receiver, int identifier, int mode, void **output)
{
    func_00239808(resource, receiver, identifier, mode, 4, output);
}
