// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t,dt; };
extern struct CLOCK D_0036BB98;
struct EngineExpiryEntry { short delta,padding; void (*fn)(void *); };
struct EngineExpirySubject { unsigned char prefix[0xC]; struct EngineExpiryEntry *table; unsigned char gap[0x4C-0x10]; float a,b,c,d; };
void func_001C8168(void *subject);
void func_0017D1D8(struct EngineExpirySubject *subject)
{
    func_001C8168(subject);
    if(D_0036BB98.t-subject->d>subject->a+subject->b+subject->c) subject->table[9].fn((char *)subject+subject->table[9].delta);
}
