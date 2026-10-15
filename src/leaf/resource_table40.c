// SLY3_CFLAGS: -Os -G0
struct ResourceEntry40 {
    int id;
    unsigned char mode;
    unsigned char opaque[35];
};
struct ResourceAllocationRequest { int bytes,alignment; };
extern int D_00474F98;
extern struct ResourceEntry40 *D_00474F9C;
extern int D_00474F48;
int func_001191E0(void *stream);
unsigned int func_00119048(void *stream);
void func_00118DF0(void *stream,int bytes);
int func_00234500(void);
void *func_001D2670(struct ResourceAllocationRequest *);
void func_00234648(void *stream,void *heap,struct ResourceEntry40 *entry);

typedef char ResourceEntrySize40[(sizeof(struct ResourceEntry40)==40)?1:-1];
typedef char ResourceAllocationRequestSize8[(sizeof(struct ResourceAllocationRequest)==8)?1:-1];

void func_002347C8(void *stream,void *heap,int expected_mode)
{
    struct ResourceAllocationRequest request;
    int i;
    int bytes=func_001191E0(stream);
    if(func_00234500()!=expected_mode) {
        func_00118DF0(stream,bytes);
        return;
    }
    D_00474F98=func_00119048(stream);
    request.bytes=D_00474F98*sizeof(struct ResourceEntry40);
    request.alignment=16;
    D_00474F9C=func_001D2670(&request);
    D_00474F48=0;
    for(i=0;i<D_00474F98;i++) {
        func_00234648(stream,heap,&D_00474F9C[i]);
        if(D_00474F9C[i].mode==1)D_00474F48++;
    }
    if(D_00474F48<D_00474F98-D_00474F48)
        D_00474F48=D_00474F98-D_00474F48;
}
