#ifndef SLY3_SEQUENCE_ACTIVITY_API_H
#define SLY3_SEQUENCE_ACTIVITY_API_H
// The receiver is a real object pointer; activity reads its fields13C/140.
struct SequenceOperation { int kind;int word; };
int func_001E5FC8(void *receiver);
int func_001E5FF8(void *receiver);
struct SequenceOperation *func_001E5F60(void *receiver,int kind);
void func_0023FE38(void *receiver,int identifier);
void func_0023FEC0(void *receiver,int identifier);
void func_00240000(void *receiver,int identifier);
void func_00240080(void *receiver,int identifier);
#endif
