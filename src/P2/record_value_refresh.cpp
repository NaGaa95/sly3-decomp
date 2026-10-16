// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct RecordOwner { SCENE_OBJECT *unknown_0; SCENE_OBJECT *owner; };
struct ObjectView { unsigned char prefix[0x458]; float value; };
struct ObjectRecord { SCENE_OBJECT *object; float value; RecordOwner *link; };
struct RecordList { unsigned char prefix[0x4C]; int count; ObjectRecord *records; };
static inline int Inherited(SCENE_OBJECT *object){ return object->flags.fields.inherited; }
extern "C" void func_0021AB48(RecordList *list,ObjectRecord *record);
extern "C" void func_0021ADF8(RecordList *list)
{
    for(int i=0;i<list->count;i++) {
        ObjectRecord *record=&list->records[i];
        SCENE_OBJECT *object=record->object;
        if(object) {
            if(!Inherited(object) || !Inherited(record->link->owner))
                func_0021AB48(list,record);
            else
                record->value=((ObjectView *)object)->value;
        }
    }
}
