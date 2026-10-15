// Format an original narrow8-bit string with explicit argument-list pointer into the genuine0x420-byte buffered output object, flush/destruct it with flags2 and return the actual byte total. Complete271008 consumes output/format/argument pointer only; its parser constructs every conversion input internally, with no incoming FPR formal.
// Reference compiler shape: src/hand/func_001ED278.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Output {void *memory;int capacity,position,handle,total,buffer_capacity,buffer_count;char *buffer;char inline_buffer[0x400];};
struct Output *func_0025A1A0(struct Output *output,int handle,int capacity);
int func_00271008(struct Output *output,const char *format,void *arguments);
void func_0025A288(struct Output *output,int flags);
int func_00271328(const char *format,void *arguments){struct Output output;int result;func_0025A1A0(&output,-1,0);result=func_00271008(&output,format,arguments);func_0025A288(&output,2);return result;}
