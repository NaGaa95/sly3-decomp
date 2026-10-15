// Original USA entry 0x1977a0; ordinary C reconstruction.
// Receiver A0 and32-bit key A1 are explicit. A linked node40 walk matches full32-bit kind9/key4 and next1C.2BE3A0 receives the real local object A0/deletion flags2 A1; its complete body reads only flags bit0, so the uninitialized local representation is not read. Original node pointer is returned.
// SLY3_CFLAGS: -Os -G0
struct Node  {
    int type,key;
    char pad[0x14];
    struct Node *next;
};
struct Scratch  {
    int words[4];
};
void func_002BE3A0(void *,int);
struct Node *func_001977A0(char *p,int key)  {
    struct Node *node=*(struct Node **)(p+0x40);
    struct Scratch scratch;
    while(node) {
        if(node->type==9 && node->key==key)break;
        node=node->next;
    }
    func_002BE3A0(&scratch,2);
    return node;
}
