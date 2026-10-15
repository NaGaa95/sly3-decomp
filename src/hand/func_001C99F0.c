// SLY3_CFLAGS: -Os -G0
// Release the original retained object and its actor, script and message references.
// Count at10 belongs to this retained-object class, distinct from scene owner fields.
struct S {void *actor;void *script;void *messages;int unknown;int references;};
void func_002BAA50(void *reference,void *actor);
void func_002BBF40(void *reference,void *script);
void func_0013BDE0(void *receiver);
void func_002BE578(void *receiver,int flags);
void func_001C99F0(struct S *p){if(--p->references<=0){func_002BAA50(p,0);func_002BBF40(&p->script,0);func_0013BDE0(p);if(p)func_002BE578(p,3);}}
