// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
typedef struct RuntimeNotificationEntry {
    short adjustment;
    short control;
    void *function;
} RuntimeNotificationEntry;
typedef struct RuntimeNotificationLink {
    void *block;
    struct RuntimeNotificationLink *next;
    RuntimeNotificationEntry *methods;
} RuntimeNotificationLink;
typedef struct RuntimeNotificationOwner {
    unsigned char opaque00[0x28];
    RuntimeNotificationLink *first;
} RuntimeNotificationOwner;

void func_002BA0D0(RuntimeNotificationOwner *owner, void *context)
{
    RuntimeNotificationLink *link;
    for (link = owner->first; link; link = link->next)
        ((void (*)(void *, void *))link->methods[2].function)(
            (char *)link + link->methods[2].adjustment, context);
}
