// SLY3_CFLAGS: -Os -G0
struct StoredPair { char unknown_0[0x1A4]; int first; float second; };
void func_00282F68(struct StoredPair *object,int first,float second)
{
    object->first = first;
    object->second = second;
}
