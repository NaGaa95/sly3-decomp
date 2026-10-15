#ifndef SLY3_PRIVATE_INSTANCE_APPLY804_H
#define SLY3_PRIVATE_INSTANCE_APPLY804_H
#include "instance_selection.h"
#include "bis.h"

struct INSTANCE_APPLY_RESOURCE {
    int references,reserved4;
    INSTANCE_APPLY_RESOURCE *child;
};
struct INSTANCE_APPLY_BINDING {
    int kind,reserved4;
    INSTANCE_APPLY_RESOURCE *resource;
    int byte_count;
    void *data;
    SCENE_OBJECT *object;
};
struct INSTANCE_APPLY_OWNER {
    char reserved0[0xC];
    SCENE_VIRTUAL_ENTRY *vtable;
    SCENE_OBJECT *parent;
    char reserved14[0x34-0x14];
    float scale;
    char reserved38[0x40-0x38];
    void *channel;
    char reserved44[0x50-0x44];
    MATRIX4 matrix;
    char reserved90[0xD0-0x90];
    INSTANCE_SELECTION_TABLE *table;
    int mode;
    INSTANCE_SELECTION_ENTRY *head;
    int binding_count;
    INSTANCE_APPLY_BINDING *bindings;
};
struct INSTANCE_APPLY_CONTEXT;
struct INSTANCE_APPLY_CONTEXT_LIST {
    INSTANCE_APPLY_CONTEXT *first,*last;
    int member_offset;
};
struct INSTANCE_APPLY_CONTEXT {
    int handle;
    INSTANCE_APPLY_CONTEXT *parent;
    int query_key;
    INSTANCE_APPLY_CONTEXT *hash_next;
    SCENE_OBJECT *object;
    INSTANCE_APPLY_CONTEXT *sibling_next;
    INSTANCE_APPLY_CONTEXT_LIST children;
    int reserved24;
};
struct INSTANCE_APPLY_GAME {
    char reserved[0x4630];
    INSTANCE_SELECTION_TABLE *tables;
    INSTANCE_APPLY_CONTEXT *root;
};
struct INSTANCE_APPLY_DESCRIPTOR {
    int kind;
    unsigned int flags;
    char reserved8[0x28-8];
};
struct INSTANCE_APPLY_STREAM {
    char base[0x30];
    void *vtable;
    int pending_byte_count;
    void *raw_data;
};
struct INSTANCE_APPLY_WORK {
    int handle;
    SCENE_OBJECT *found,*child;
    SCENE_OBJECT **cursor;
};
struct INSTANCE_APPLY_REFERENCE_PREFIX {
    INSTANCE_APPLY_RESOURCE *resource;
};
extern "C" {
    extern INSTANCE_APPLY_GAME D_00475480;
    extern INSTANCE_APPLY_DESCRIPTOR D_0032CA80[];
    void func_001FB710(INSTANCE_APPLY_OWNER *,INSTANCE_SELECTION_ENTRY *);
    int func_001FA5A8(int table,int row);
    INSTANCE_APPLY_CONTEXT *func_001FA640(INSTANCE_APPLY_CONTEXT *,int,const int *);
    int func_0017DEC0(void *,int flags,int key,SCENE_OBJECT *,INSTANCE_APPLY_CONTEXT *,int capacity,SCENE_OBJECT **);
    INSTANCE_APPLY_STREAM *func_00119A00(INSTANCE_APPLY_STREAM *);
    void func_00119A80(INSTANCE_APPLY_STREAM *,int byte_count,void *data,int flags);
    void func_00119A38(INSTANCE_APPLY_STREAM *,int flags);
    void func_00150AE8(SCENE_OBJECT *,INSTANCE_APPLY_DESCRIPTOR *,unsigned int,INSTANCE_APPLY_STREAM *);
    void func_002BAA50(INSTANCE_APPLY_RESOURCE **,INSTANCE_APPLY_RESOURCE *);
    void func_001FC3A0(INSTANCE_APPLY_GAME *,INSTANCE_APPLY_OWNER *,SCENE_OBJECT *);
}
inline void ApplyInstanceScale(SCENE_OBJECT *object,float scale) {
    SCENE_VIRTUAL_ENTRY *v=&object->vtable[46];
    ((void (*)(void *,float))v->Simple)((char *)object+v->delta,scale);
}
inline void ApplyInstanceContext(SCENE_OBJECT *object,SCENE_OBJECT *parent,void *channel) {
    SCENE_VIRTUAL_ENTRY *v=&object->vtable[10];
    v->Change((char *)object+v->delta,parent,channel,0);
}
inline void ApplyInstanceMatrix(SCENE_OBJECT *object,const MATRIX4 *matrix) {
    SCENE_VIRTUAL_ENTRY *v=&object->vtable[42];
    ((void (*)(void *,const MATRIX4 *))v->Simple)((char *)object+v->delta,matrix);
}
inline void ApplyInstanceQuery(INSTANCE_APPLY_OWNER *owner,SCENE_OBJECT ***cursor) {
    SCENE_VIRTUAL_ENTRY *v=&owner->vtable[3];
    ((void (*)(void *,int,void *,int,SCENE_OBJECT ***,int))v->Simple)
        ((char *)owner+v->delta,17,0,1,cursor,0);
}
#define APPLY_OFF(t,m) ((unsigned int)&((t *)0)->m)
typedef char instance_apply_layout[
    (sizeof(void *)==4 && sizeof(INSTANCE_SELECTION_TABLE)==0x6C &&
     sizeof(INSTANCE_APPLY_CONTEXT)==40 && sizeof(INSTANCE_APPLY_CONTEXT_LIST)==12 &&
     sizeof(INSTANCE_APPLY_BINDING)==0x18 && sizeof(INSTANCE_APPLY_DESCRIPTOR)==0x28 &&
     sizeof(INSTANCE_APPLY_STREAM)==0x3C && sizeof(CBinaryInputStream)==0x34 &&
     sizeof(INSTANCE_APPLY_WORK)==0x10 &&
     APPLY_OFF(INSTANCE_APPLY_OWNER,vtable)==0xC &&
     APPLY_OFF(INSTANCE_APPLY_OWNER,parent)==0x10 &&
     APPLY_OFF(INSTANCE_APPLY_OWNER,scale)==0x34 &&
     APPLY_OFF(INSTANCE_APPLY_OWNER,channel)==0x40 &&
     APPLY_OFF(INSTANCE_APPLY_OWNER,matrix)==0x50 &&
     APPLY_OFF(INSTANCE_APPLY_OWNER,table)==0xD0 &&
     APPLY_OFF(INSTANCE_APPLY_OWNER,mode)==0xD4 &&
     APPLY_OFF(INSTANCE_APPLY_OWNER,head)==0xD8 &&
     APPLY_OFF(INSTANCE_APPLY_OWNER,binding_count)==0xDC &&
     APPLY_OFF(INSTANCE_APPLY_OWNER,bindings)==0xE0 &&
     APPLY_OFF(INSTANCE_APPLY_GAME,tables)==0x4630 &&
     APPLY_OFF(INSTANCE_APPLY_GAME,root)==0x4634 &&
     APPLY_OFF(INSTANCE_APPLY_BINDING,resource)==8 &&
     APPLY_OFF(INSTANCE_APPLY_BINDING,byte_count)==0xC &&
     APPLY_OFF(INSTANCE_APPLY_BINDING,data)==0x10 &&
     APPLY_OFF(INSTANCE_APPLY_BINDING,object)==0x14 &&
     APPLY_OFF(INSTANCE_APPLY_CONTEXT,object)==0x10 &&
     APPLY_OFF(INSTANCE_APPLY_CONTEXT,children)==0x18 &&
     APPLY_OFF(INSTANCE_APPLY_DESCRIPTOR,flags)==4 &&
     APPLY_OFF(INSTANCE_APPLY_STREAM,vtable)==0x30 &&
     APPLY_OFF(INSTANCE_APPLY_STREAM,pending_byte_count)==0x34 &&
     APPLY_OFF(INSTANCE_APPLY_STREAM,raw_data)==0x38) ? 1 : -1];
#undef APPLY_OFF
#endif
