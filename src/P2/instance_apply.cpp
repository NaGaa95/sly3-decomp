// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Acquire an instance entry, restore its resources, and apply its child state.
#include "instance_apply.h"

extern "C" INSTANCE_SELECTION_ENTRY *
func_001FBB08(INSTANCE_APPLY_OWNER *owner,int minimum)
{
    INSTANCE_APPLY_STREAM stream;
    INSTANCE_APPLY_WORK work;
    INSTANCE_SELECTION_ENTRY *entry=
        func_001FBA28((INSTANCE_SELECTION_OWNER *)owner,minimum);
    if(!entry)
        return 0;
    if(entry->owner)
        func_001FB710((INSTANCE_APPLY_OWNER *)entry->owner,entry);
    entry->owner=(SCENE_OBJECT *)owner;
    entry->next=owner->head;
    owner->head=entry;
    *(MATRIX4 *)entry->matrix=owner->matrix;
    int row=func_001FB5D8((INSTANCE_SELECTION_OWNER *)owner,entry);
    work.handle=func_001FA5A8(owner->table-D_00475480.tables,row);
    INSTANCE_APPLY_CONTEXT *context=
        func_001FA640(D_00475480.root,1,&work.handle);

    for(int i=0;i<owner->binding_count;i++) {
        INSTANCE_APPLY_BINDING *binding=&owner->bindings[i];
        if(binding->kind==7)
            continue;
        if(binding->kind==8) {
            work.found=context->object;
            if(!work.found)
                continue;
        } else if(func_0017DEC0(&D_00475480,0xA05,binding->kind,0,
                                context,1,&work.found)!=1) {
            continue;
        }
        binding->object=work.found;
        func_00119A00(&stream);
        func_00119A80(&stream,binding->byte_count,binding->data,0);
        int index;
        while((index=((CBinaryInputStream *)&stream)->S16Read())>=0) {
            INSTANCE_APPLY_DESCRIPTOR *descriptor=&D_0032CA80[index];
            func_00150AE8(work.found,descriptor,descriptor->flags&0x2031,&stream);
        }
        if(binding->resource && owner->mode!=2) {
            func_002BAA50(&binding->resource->child,
                ((INSTANCE_APPLY_REFERENCE_PREFIX *)work.found)->resource);
            func_002BAA50(
                &((INSTANCE_APPLY_REFERENCE_PREFIX *)work.found)->resource,
                binding->resource);
        }
        func_00119A38(&stream,2);
    }

    for(int i=0;i<owner->table->object_count;i++) {
        SCENE_OBJECT *child=
            owner->table->objects[row*owner->table->object_count+i];
        SCENE_VIRTUAL_ENTRY *scale=&child->vtable[46];
        work.child=child;
        ((void (*)(void *,float))scale->Simple)
            ((char *)child+scale->delta,owner->scale);
        ApplyInstanceContext(work.child,owner->parent,owner->channel);
        ApplyInstanceMatrix(work.child,&owner->matrix);
        CallScene(work.child,8);
        func_001FC3A0(&D_00475480,owner,work.child);
        work.cursor=&work.child;
        ApplyInstanceQuery(owner,&work.cursor);
    }
    return entry;
}
