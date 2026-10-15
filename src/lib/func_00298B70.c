// Reference: Sly 2 src/lib/UnlinkAlarm.c; target Sly 3 0x00298B70.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
typedef struct ALARM { struct ALARM *next; struct ALARM *prev; } ALARM;
extern ALARM *_alarm_head;
ALARM *UnlinkAlarm(ALARM *a)
{
    ALARM *n = a->next;
    if (a->prev) a->prev->next = n;
    else _alarm_head = n;
    if (n) n->prev = a->prev;
    a->prev = 0;
    return n;
}
