/* Recovered prefixes and constructor helpers; original class identities and
 * fields outside these accessed prefixes remain unknown. */
#ifndef RECORD_CONSTRUCT_H
#define RECORD_CONSTRUCT_H

struct OBJECT_PREFIX
{
    void *pvTable;
};

struct OBJECT_WITH_PREFIX
{
    unsigned char unknown[0x70];
    OBJECT_PREFIX object;
};

struct OBJECT_WITH_NESTED_PREFIX
{
    unsigned char unknown[0x180];
    OBJECT_WITH_PREFIX nested;
};

extern "C" OBJECT_PREFIX *func_002BE7E0(OBJECT_PREFIX *p);
extern "C" OBJECT_PREFIX *func_002BE748(OBJECT_PREFIX *p);
extern "C" OBJECT_WITH_PREFIX *func_002BE780(OBJECT_WITH_PREFIX *p);
extern "C" OBJECT_WITH_NESTED_PREFIX *func_002BE7B0(OBJECT_WITH_NESTED_PREFIX *p);

#endif
