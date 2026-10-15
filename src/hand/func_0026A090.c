// Find the explicit identifier in the twelve-byte embedded records and update its integer and narrow formatted text only when changed. Formatting is the8-bit API, separate from16-bit game text; buffer has its original four bytes.
// Reference algorithm: src/hand/func_001CA8E0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Entry {int id;int value;char text[4];};
extern char D_00327ED0[];
struct Entry *func_0026A108(void *receiver,int id);
int func_00271448(char *output,const char *format,...);
void func_0026A090(void *receiver,int id,int value){struct Entry *entry=func_0026A108(receiver,id);if(entry && entry->value!=value){entry->value=value;func_00271448(entry->text,D_00327ED0,value);}}
