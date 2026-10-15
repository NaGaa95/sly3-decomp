#ifndef SLY3_P2_SCENE_MODE_H
#define SLY3_P2_SCENE_MODE_H
#include "scene.h"
#include "mat.h"
// Provisional derived scene layout, with only original accessed fields named.
struct SCENE_MODE_RECORD { char prefix[0x4C];MATRIX3 *rotation; };
struct SCENE_MODE_INPUT { char prefix[8];float value; };
struct SCENE_MODE_OBJECT {
    SCENE_OBJECT scene;
    char prefix68[0x130-sizeof(SCENE_OBJECT)];
    int index130;SCENE_MODE_INPUT *input134;
    char prefix138[0x190-0x138];
    SCENE_MODE_RECORD *record190,*record194;void *observer198;
    void *transitions19C[6];
    int state1B4;float time1B8;void *transition1BC,*token1C0;
    int phase1C4,unknown1C8;float time1CC;
    int active1D0;float time1D4;char prefix1D8[8];
    int state1E0;float angles1E4[3];SCENE_OBJECT *selected1F0;
    float value1F4,value1F8,elapsed1FC,duration200,value204;
    int unknown208,modes20C[3];char prefix218[8];MATRIX3 rotation220;
    void *result250,*owner254,*event258,*token25C;
};
struct SCENE_MODE_FIELD { int flags,identifier,offset; };
#endif
