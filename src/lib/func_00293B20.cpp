// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0 -fno-exceptions
template <int Way>
static __inline__ unsigned int ReadIndexedCacheTag(unsigned int index)
{
    unsigned int tag;
    __asm__ volatile("sync\n\tcache 0x10,%2(%1)\n\tsync\n\tmfc0 %0,$28"
                     : "=r"(tag) : "r"(index),"i"(Way) : "memory");
    return tag;
}

template <int Way>
static __inline__ void IndexedCacheOperation14(unsigned int index)
{
    __asm__ volatile("sync\n\tcache 0x14,%1(%0)\n\tsync"
                     : : "r"(index),"i"(Way) : "memory");
}

static __inline__ void CacheBarrier(void)
{
    __asm__ volatile("sync" : : : "memory");
}

extern "C" void func_00293B20(unsigned int lower,unsigned int upper)
{
    for (int index = 0; index < 0x1000; index += 0x40) {
        unsigned int address = (ReadIndexedCacheTag<0>(index) & 0xFFFFF000U) + index;
        if (lower <= address && address <= upper)
            IndexedCacheOperation14<0>(index);
        address = (ReadIndexedCacheTag<1>(index) & 0xFFFFF000U) + index;
        if (lower <= address && address <= upper)
            IndexedCacheOperation14<1>(index);
        CacheBarrier();
    }
}
