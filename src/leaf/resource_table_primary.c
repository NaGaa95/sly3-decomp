// SLY3_CFLAGS: -Os -G0
struct ResourceEntry32 {
    int id;
    unsigned char mode;
    unsigned char opaque[27];
};
struct ResourceAllocationRequest { int bytes,alignment; };
extern int D_00474FA0;
extern struct ResourceEntry32 *D_00474FA4;
extern int D_00474F4C;
int func_001191E0(void *stream);
unsigned int func_00119048(void *stream);
void func_00118DF0(void *stream,int bytes);
int func_00234500(void);
void *func_001D2670(struct ResourceAllocationRequest *);
void func_00233EA8(void *stream,void *heap,struct ResourceEntry32 *entry);

typedef char ResourceEntrySize32[(sizeof(struct ResourceEntry32)==32)?1:-1];
typedef char ResourceAllocationRequestSize8[(sizeof(struct ResourceAllocationRequest)==8)?1:-1];

void func_00234518(void *stream,void *heap,int expected_mode)
{
    struct ResourceAllocationRequest request;
    int i;
    int bytes=func_001191E0(stream);
    if(func_00234500()!=expected_mode) {
        func_00118DF0(stream,bytes);
        return;
    }
    D_00474FA0=func_00119048(stream);
    request.bytes=D_00474FA0*sizeof(struct ResourceEntry32);
    request.alignment=16;
    D_00474FA4=func_001D2670(&request);
    D_00474F4C=0;
    for(i=0;i<D_00474FA0;i++) {
        func_00233EA8(stream,heap,&D_00474FA4[i]);
        if(D_00474FA4[i].mode==1)D_00474F4C++;
    }
    if(D_00474F4C<D_00474FA0-D_00474F4C)
        D_00474F4C=D_00474FA0-D_00474F4C;
}
