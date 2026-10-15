// Dispatch relationship records from the head, preserving the next-record cursor during callbacks.
// SLY3_CFLAGS: -Os -G0
struct Subject {
    char prefix[0xFC];
    int contextFirst;
};
struct Record {
    int kind;
    struct Subject *subject;
    int mode,first,second;
    struct Record *next,*previous;
};
struct DL {
    struct Record *first,*last;
    int nodeOffset;
};
struct Queue {
    int dispatchMode;
    char unused4[4];
    struct DL list;
    struct Record *current;
};
extern char D_004794D4[];
int func_0011B0F0(struct DL *);
void func_0011B028(struct DL *,struct Record *);
struct Record *func_0011E118(void *);
void func_0011E1F0(void *,struct Record *);
void func_0011AFC0(struct DL *,struct Record *,struct Record *);
void func_00189300(struct Subject *,int,int,int);
void func_00189500(struct Subject *,int,int,int);
void func_00189180(struct Queue *queue) {
    while(!func_0011B0F0(&queue->list)) {
        struct Record *record=queue->list.first;
        queue->current=record->next;
        switch(record->kind) {
            case 0:func_00189300(record->subject,record->mode,record->first,record->second);
            break;
            case 1:func_00189500(record->subject,record->mode,record->first,record->second);
            break;
        }
        queue->current=0;
        func_0011B028(&queue->list,record);
        func_0011E1F0(D_004794D4,record);
    }
}
