#ifndef SLY3_PRIVATE_ANIMATION_RECORD_LOOKUP_API_H
#define SLY3_PRIVATE_ANIMATION_RECORD_LOOKUP_API_H
// Actual kind11 records use an integer key at8. Other unaccessed record
// words stay opaque. The first float at0 is consumed by the value wrapper.
struct LookupRecord20 {
    float value0;
    int kind4;
    int key8;
    unsigned char unusedC[8];
};
struct LookupLibrary {
    unsigned char unused0[0x90];
    int count90;
    struct LookupRecord20 *records94;
};
#ifdef __cplusplus
extern "C" {
#endif
struct LookupRecord20 *func_00136880(struct LookupLibrary *library, int key);
float func_001368E0(struct LookupLibrary *library, int key);
#ifdef __cplusplus
}
#endif
#endif
