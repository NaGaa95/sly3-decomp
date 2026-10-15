// Store the explicit owner pointer used by the original object callers.
void func_001A9878(void *object, void *owner)
{
    *(void **)((char *)object + 0x134) = owner;
}
