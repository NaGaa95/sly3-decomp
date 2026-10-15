// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
// Retain the existing C physical-output helper view; its returned pointer is ignored.
// The actual native nontrivial C++ result is written through outputA0.
struct CRef;
struct KEY;
struct TRIE;
extern struct TRIE D_004793C8;
void func_0021C338(struct CRef *output, struct TRIE *receiver,
                  struct KEY *key, unsigned char *buffer);
struct CRef *func_002BC010(struct CRef *output, struct KEY *key,
                         unsigned char *buffer)
{
    func_0021C338(output, &D_004793C8, key, buffer);
    return output;
}
