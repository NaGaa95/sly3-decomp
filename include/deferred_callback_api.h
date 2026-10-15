#ifndef SLY3_DEFERRED_CALLBACK_API_H
#define SLY3_DEFERRED_CALLBACK_API_H
// Original GCC member-pointer representation, not executable instruction data.
// Negative index selects the real direct pointer; otherwise vptrOffset is read.
struct DEFERRED_PMF {
    short delta,index;
    union { void (*direct)(void *,void *);short vptrOffset;int word; } target;
};
struct DEFERRED_CALLBACK {
    void *receiver;struct DEFERRED_PMF member;void *owner;
    struct DEFERRED_CALLBACK *next;
};
typedef char deferred_pmf_size8[(sizeof(struct DEFERRED_PMF)==8)?1:-1];
typedef char deferred_node_size20[(sizeof(struct DEFERRED_CALLBACK)==20)?1:-1];
void func_0015DC68(void *game,void *receiver,struct DEFERRED_PMF member,void *owner);
void func_0015DCD0(void *game,void *receiver,struct DEFERRED_PMF member,void *owner);
#endif
