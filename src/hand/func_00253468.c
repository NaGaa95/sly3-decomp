// Construct the original sixteen-byte mask from the explicit tagged-reference A1, select/create its command, then store original value A2 and mode A3. Complete252D80 propagates A1 as a reference pointer into24B330, supplying every other helper input itself.
// Reference compiler shape: src/hand/func_001E9C30.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Mask {unsigned char bytes[16];};
struct Command {int kind,value,unknown,mode;};
struct Mask *func_00252D80(struct Mask *result,void *reference);
struct Command *func_002554C0(void *receiver,const struct Mask *mask);
void func_00253468(void *receiver,void *reference,int value,int mode){struct Mask mask;struct Command *command;func_00252D80(&mask,reference);command=func_002554C0(receiver,&mask);command->value=value;command->mode=mode;}
