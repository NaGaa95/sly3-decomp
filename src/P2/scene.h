#ifndef SLY3_P2_SCENE_H
#define SLY3_P2_SCENE_H

// Provisional names; ownership fields, list strides and64-bit state slots are
// recovered from reset, callback execution and deferred queue methods.
struct SCENE_OBJECT;
struct SCENE_VIRTUAL_ENTRY {
    short delta,pad;
    union {
        void (*Simple)(void *);
        void (*Parent)(void *,SCENE_OBJECT *,SCENE_OBJECT *);
        void (*Change)(void *,SCENE_OBJECT *,void *,int);
        int (*Children)(void *,SCENE_OBJECT ***);
        void *(*Query)(void *);
        void (*Message)(void *,int,SCENE_OBJECT *);
    };
};
struct SCENE_CALLBACK { void (*function)(SCENE_OBJECT *,void *);void *argument;SCENE_CALLBACK *next; };
struct SCENE_LIST { SCENE_OBJECT *first,*last; int memberOffset; };
struct SCENE_HANDLE { SCENE_OBJECT *object; };
union SCENE_PACKED_STATE {
    unsigned long value;
    struct {
        unsigned long low:32;
        unsigned long tag:8;
        unsigned long unknown40:4;
        long state44:4;
        long state48:4;
        unsigned long detached:1;
        unsigned int flag53:1;
        unsigned int unknown54:1;
        unsigned long registered:1;
        unsigned int inherited:1;
        unsigned int queued:1;
        unsigned int pending:1;
        unsigned long unknown59:1;
        unsigned long queried:1;
        unsigned long unknown61:3;
    } __attribute__((packed)) fields;
} __attribute__((packed,aligned(8)));
struct SCENE_OBJECT {
    char prefix[0xC]; SCENE_VIRTUAL_ENTRY *vtable;
    SCENE_OBJECT *owner; SCENE_HANDLE *handle;
    char pad18[8];SCENE_OBJECT *next,*previous; SCENE_PACKED_STATE flags;
    SCENE_CALLBACK *callbacks;float time34;void *context;int field3C;
    char pad40[0x54-0x40];SCENE_LIST children;SCENE_OBJECT *anchor;
};
struct SCENE_GLOBAL_LIST { SCENE_LIST list;SCENE_OBJECT *anchor; };

inline void CallScene(SCENE_OBJECT *object,int slot) {
    SCENE_VIRTUAL_ENTRY *entry=&object->vtable[slot];
    entry->Simple((char *)object+entry->delta);
}
inline int SceneChildren(SCENE_OBJECT *object,SCENE_OBJECT ***children) {
    SCENE_VIRTUAL_ENTRY *entry=&object->vtable[33];
    return entry->Children((char *)object+entry->delta,children);
}
inline void *SceneQuery(SCENE_OBJECT *object) {
    if(object->flags.fields.queried) {
        SCENE_VIRTUAL_ENTRY *entry=&object->vtable[26];
        return entry->Query((char *)object+entry->delta);
    }
    return 0;
}

#endif
