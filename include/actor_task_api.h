#ifndef SLY3_PRIVATE_ACTOR_TASK_API_H
#define SLY3_PRIVATE_ACTOR_TASK_API_H
#include "resource_attachment_api.h"
// modeC is an actual signed scalar ordering word used by28ECE0.
// owner4/channel8/next10 are pointers; identifier14 is an integer word.
struct ACTOR_TASK { int kind;void *owner;void *channel;int mode;
    struct ACTOR_TASK *next;int identifier;void *dispatch; };
typedef char ActorTaskPrefix28[(sizeof(struct ACTOR_TASK)==28)?1:-1];
struct ACTOR_TASK *func_001306F0(int kind);
struct ACTOR_TASK *func_0012FFB0(int kind,void *owner,void *channel,int mode,int identifier);
void *func_00130010(void *owner,void *channel,int mode);
void func_0028ECE0(void *owner,void *channel,struct ACTOR_TASK *task);
#endif
