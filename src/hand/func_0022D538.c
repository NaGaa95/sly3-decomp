// Forward all three original GP event inputs before testing the event1/3 attached key and updating the receiver. The event payload is an explicit32-bit word because complete153738 interprets it as an ID on some event paths and a pointer on others; nominal payload type is provisional.
// Reference compiler shape: src/hand/func_00182700.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int EventWord;
struct Item {EventWord key;};
struct Object {char prefix[0x14];struct Item *item;};
struct S { char unknown_0[0x15E0]; struct Object * object; };
void func_00153738(void *receiver,int event,EventWord data);
void func_0022D318(void *receiver);
void func_0022D538(struct S *p,int event,EventWord data){func_00153738(p,event,data);if((event==1||event==3)&&p->object&&p->object->item->key==data)func_0022D318(p);}
