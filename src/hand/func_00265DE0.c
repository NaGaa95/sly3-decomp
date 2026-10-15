// Return an original16-bit code scalar from the direct table below256 or from the complete binary-search record above it, otherwise the receiver fallback. Both inputs are explicit and the search reads only receiver/code.
// Reference compiler shape: src/hand/func_00229798.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Record {unsigned short identifier,unknown;float value;int auxiliary;};
struct S { char unknown_0[0x14]; struct Record ** direct; float fallback; };
struct Record *func_00265D68(void *receiver,unsigned short identifier);
float func_00265DE0(struct S *p,unsigned short identifier){struct Record *record;if(identifier<0x100)record=p->direct[identifier];else record=func_00265D68(p,identifier);return record?record->value:p->fallback;}
