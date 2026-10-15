// Update the actual one-word previous selection2D0 for state1, choosing original3C6 only for attached state4. Complete262B60 consumes resource/selection/previous-word pointers and internally removes/adds the selection; no descriptor bytes beyond word0 are inferred.
// Reference compiler shape: src/hand/func_002245B8.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Object {char prefix[0x11C4];int state;};
struct S { char unknown_0[0x190]; int state; char unknown_194[0x18]; struct Object * object; char unknown_1B0[0x118]; void * resource; char unknown_2CC[0x4]; int selection; };
void func_00262B60(void *resource,int selection,int *previous);
void func_002876E8(struct S *p){if(p->state==1){int selection=-1;if(p->object&&p->object->state==4)selection=0x3C6;if(p->resource)func_00262B60(p->resource,selection,&p->selection);}}
