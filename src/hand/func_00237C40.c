// Update the explicit descriptor and copy its four float controls, then set both unit controls.
// SLY3_CFLAGS: -Os -G0
struct Record {char prefix[0xC];float first,second,third,fourth;};struct S {char prefix[0x50];float first,second,third,fourth,scale,weight;};
void func_00236FE0(void *receiver,const struct Record *record);
void func_00237C40(struct S *p,const struct Record *record){func_00236FE0(p,record);p->first=record->first;p->second=record->second;p->third=record->third;p->fourth=record->fourth;p->weight=1.0f;p->scale=1.0f;}
