#ifndef SLY3_RECORD_GAIN_TYPES_H
#define SLY3_RECORD_GAIN_TYPES_H
/* Consumed record views only. Complete native helpers prove20/24/48-byte
   strides; no complete animation/owner class is asserted by these views. */
typedef struct ID_RECORD {
    char opaque[0x10]; int identifier;
} ID_RECORD;
typedef struct ACTIVITY_RECORD {
    char opaque0[8]; short index;
    char opaqueA[0x18-0xA];
} ACTIVITY_RECORD;
typedef struct GAIN_GROUP {
    unsigned short idCount, activityCount;
    ID_RECORD *ids;
    ACTIVITY_RECORD *activities;
    char opaqueC[0x30-0xC];
} GAIN_GROUP;
typedef struct GAIN_GROUPS_VIEW {
    char opaque0[0x70]; unsigned short count; short padding;
    GAIN_GROUP *groups;
} GAIN_GROUPS_VIEW;
typedef char IdRecordStride[(sizeof(ID_RECORD)==20)?1:-1];
typedef char ActivityRecordStride[(sizeof(ACTIVITY_RECORD)==24)?1:-1];
typedef char GainGroupStride[(sizeof(GAIN_GROUP)==48)?1:-1];
typedef char GainGroupsPrefix[(sizeof(GAIN_GROUPS_VIEW)==0x78)?1:-1];

#endif
