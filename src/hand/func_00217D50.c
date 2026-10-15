// Store actual float F12 and integer state A2 into explicit record A1, then notify the stored resource with the original indexed selection. Context A0 is caller-derived unused by this complete body and retained provisionally.
// Reference algorithm: src/hand/func_001B0808.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Record {char prefix[8];void *resource;int unused;int state;float value;};
extern int D_00325CA0[];
void func_00239CE8(void *resource,int selection);
void func_00217D50(float value,void *context,struct Record *record,int state){record->value=value;record->state=state;if(record->resource && state>=0)func_00239CE8(record->resource,D_00325CA0[state]);}
