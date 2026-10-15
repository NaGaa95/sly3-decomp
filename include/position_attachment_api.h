#ifndef SLY3_POSITION_ATTACHMENT_API_H
#define SLY3_POSITION_ATTACHMENT_API_H
typedef int SequencePackedPosition __attribute__((mode(TI)));
//173778 stores attachmentWord unchanged at newobject+40: its bit pattern
// can come from a raw script-reference payload or a real related actor pointer.
// It is not interpreted as an integer identifier or dereferenced by this API.
void *func_001738C0(void *space,SequencePackedPosition position,int attachmentWord);
void *func_00173E00(void *context,int kind,SequencePackedPosition position,int attachmentWord);
#endif
