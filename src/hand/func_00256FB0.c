// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct Owner {int unused;void *selection;};
union Payload {QWORD words[3];struct {struct Owner *owner;char unknown[44];} data;};
struct S {char prefix[0x10F0];int state;char unknown[0x1730-0x10F4];union Payload payload;};
void func_0024F3B8(void *receiver,void *selection,int active);
void func_00256FB0(struct S *p,const union Payload *payload){p->payload=*payload;p->state=3;func_0024F3B8(p,p->payload.data.owner->selection,1);}
