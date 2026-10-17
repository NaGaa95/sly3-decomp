// SLY3_CFLAGS: -Os -G0
struct TestEntry { short delta; short pad; int (*method)(void *,void *); };
struct TestObject { unsigned char prefix[0xC]; struct TestEntry *table; };
int func_0013B500(void *object,int identifier);
int func_00170BC8(void *self,struct TestObject *object)
{
    return func_0013B500(object,0x33) ? object->table[120].method((char *)object+object->table[120].delta,self)!=0 : 0;
}
