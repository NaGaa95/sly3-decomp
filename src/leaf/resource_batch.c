// SLY3_CFLAGS: -Os -G0
struct ResourceBatchRequest { int bytes,alignment; };
struct ResourceBatchRecord44 {
    int id;
    unsigned char opaque4,flags;
    unsigned char opaque6[38];
};
extern int D_00474FA8;
extern void **D_00474FAC;
extern int D_0046FF38;
extern struct ResourceBatchRecord44 *D_0046FF3C;
extern int D_00474FA0,D_00474F98;
extern unsigned int D_00474F50;
extern void *D_00474F58[16];
void func_00234518(void *stream,void *heap,int mode);
void func_002347C8(void *stream,void *heap,int mode);
int func_00118FF8(void *stream);
unsigned int func_00119048(void *stream);
void *func_001D2670(struct ResourceBatchRequest *request);
void *func_00236EB0(void *owner,void *stream);
void func_00234A58(void *stream,void *heap,struct ResourceBatchRecord44 *record);
void func_0025C9A0(void *context,void *stream);
void *func_002364F0(void *graphics_stream,int mode);
void func_00235128(void);
void func_00234DA8(struct ResourceBatchRecord44 *source,void *heap);
typedef char ResourceBatchRecordSize44[(sizeof(struct ResourceBatchRecord44)==44)?1:-1];
typedef char ResourceBatchRequestSize8[(sizeof(struct ResourceBatchRequest)==8)?1:-1];

void func_00234EA0(void *context,void *graphics_stream,void *stream,void *heap)
{
    struct ResourceBatchRequest request;
    int i,j;
    void *batch;
    func_00234518(stream,heap,1);
    func_002347C8(stream,heap,1);
    func_00234518(stream,heap,0);
    func_002347C8(stream,heap,0);
    D_00474FA8=func_00118FF8(stream);
    request.bytes=D_00474FA8*4;
    request.alignment=16;
    D_00474FAC=func_001D2670(&request);
    for(i=0;i<D_00474FA8;i++)
        D_00474FAC[i]=func_00236EB0(0,stream);
    D_0046FF38=func_00119048(stream);
    request.bytes=D_0046FF38*sizeof(struct ResourceBatchRecord44);
    request.alignment=16;
    D_0046FF3C=func_001D2670(&request);
    for(j=0;j<D_0046FF38;j++)
        func_00234A58(stream,heap,&D_0046FF3C[j]);
    func_0025C9A0(context,stream);
    if(graphics_stream) {
        batch=func_002364F0(graphics_stream,3);
        if(batch && (unsigned int)D_00474F50<16)
            D_00474F58[D_00474F50++]=batch;
    } else {
        int resource_index;
        for(resource_index=0;resource_index<D_00474FA0;resource_index++) {}
        for(resource_index=0;resource_index<D_00474F98;resource_index++) {}
    }
    func_00235128();
    for(i=0;i<D_0046FF38;i++) {
        struct ResourceBatchRecord44 *record=&D_0046FF3C[i];
        if(record->flags&8)func_00234DA8(record,heap);
    }
}
