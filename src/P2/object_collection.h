#ifndef SLY3_P2_OBJECT_COLLECTION_H
#define SLY3_P2_OBJECT_COLLECTION_H
#include "scene.h"
// The pure virtual base establishes a vptr at0; derived capacity/count/values
// are at4/8/C. Both original24-byte zero-RTTI tables have one Append slot.
class OBJECT_COLLECTION_BASE {
public:
    OBJECT_COLLECTION_BASE();
    virtual void Append(int count,SCENE_OBJECT **values)=0;
};
class OBJECT_COLLECTION : public OBJECT_COLLECTION_BASE {
public:
    int capacity,count;
    SCENE_OBJECT **values;
    OBJECT_COLLECTION();
    virtual void Append(int count,SCENE_OBJECT **values);
};
#endif
