// Insert a captured relationship request before the current cursor; a null cursor appends.
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
void func_00189180(struct Queue *);
void func_00189240(struct Queue *queue,struct Subject *p,int kind,int mode,int second) {
    struct DL *list=&queue->list;
    struct Record *record=func_0011E118(D_004794D4);
    record->kind=kind;
    record->mode=mode;
    record->subject=p;
    record->first=p->contextFirst;
    record->second=second;
    func_0011AFC0(list,queue->current,record);
    switch(queue->dispatchMode) {
        case 0:break;
        case 1: if(queue->list.first==list->last)func_00189180(queue);
        break;
    }
}
