// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
// This remains an ordinary C view of the proven five physical pointer arguments.
// The helper writes through outputA0; no new C++ aggregate-return ABI is introduced.
struct CRef;
struct KEY;
struct TRIE;
extern struct TRIE D_004793C8;
void func_0021C528(struct CRef *output,struct TRIE *receiver,
                         struct KEY *key,const struct CRef *value,unsigned char *buffer);
struct CRef *func_002BC050(struct CRef *output,struct KEY *key,
                         const struct CRef *value,unsigned char *buffer)
{
    func_0021C528(output,&D_004793C8,key,value,buffer);
    return output;
}
