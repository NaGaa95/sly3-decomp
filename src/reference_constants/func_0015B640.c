// Original USA entry 0x15b640; ordinary C reconstruction.
// Receiver A0 and node A1 are explicit. Complete15B580 consumes that pair and derives its virtual-call receiver internally.11B0C0 receives the actual list at3E50 and node; successful membership updates the current node pointer3E5C from node.next4 before11B028(list,node). Original list offset and alias-sensitive load/store order are preserved.
// SLY3_CFLAGS: -Os -G0
struct Node  {
    int unused;
    struct Node *next;
};
void func_0015B580(void *,void *);
int func_0011B0C0(void *,void *);
void func_0011B028(void *,void *);
void func_0015B640(char *p,struct Node *node)  {
    void *list=p+0x3E50;
    func_0015B580(p,node);
    if(func_0011B0C0(list,node)) {
        if(*(struct Node **)(p+0x3E5C)==node)*(struct Node **)(p+0x3E5C)=node->next;
        func_0011B028(list,node);
    }
}
