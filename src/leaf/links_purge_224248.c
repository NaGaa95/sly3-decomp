// SLY3_CFLAGS: -Os -G0
#include "deferred_callback_api.h"
struct Link { unsigned char prefix[8]; void *peer; unsigned char gapC[0xA0]; struct Link *next; };
struct Group { unsigned char prefix[0x168]; struct Link *links; unsigned char gap16C[4]; };
struct Owner { unsigned char prefix[0x178]; int groupCount; struct Group *groups; };
extern char D_00475480[];
extern struct DEFERRED_PMF D_00326240;
void func_0023EDC8(struct Owner *owner,void *object);
void func_001CBAA0(void *game,struct Link *links);
void func_00224248(struct Owner *owner,void *object)
{
    struct Link *freed=0;
    int i;
    func_0023EDC8(owner,object);
    for(i=0;i<owner->groupCount;i++) {
        struct Link **slot=&owner->groups[i].links;
        struct Link *link=*slot;
        while(link) {
            int side=link->peer==(void *)owner;
            if(object==((struct Link *)((char *)link+(side<<6)))->peer) {
                *slot=link->next;
                link->next=freed;
                freed=link;
            } else
                slot=&link->next;
            link=*slot;
        }
    }
    func_001CBAA0(D_00475480,freed);
    func_0015DCD0(D_00475480,owner,D_00326240,0);
}
