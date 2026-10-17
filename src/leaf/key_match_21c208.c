// SLY3_CFLAGS: -Os -G0
struct TrieNode { short ch; signed char kind; unsigned char terminal; unsigned short offset; unsigned short child; unsigned short sibling; };
struct Trie { int word0; struct TrieNode *nodes; };
struct Key { int length; unsigned short *chars; };
struct Match { struct TrieNode *node; int index; };
int func_0021C208(struct Trie *trie,struct Key *key,struct Match *match)
{
    struct TrieNode *node,*nodes;
    int index,child;
    nodes=trie->nodes;
    if(!nodes->child)
        return 0;
    node=nodes+nodes->child;
    match->index=0;
    index=0;
    for(;;) {
        if(node->ch==key->chars[index]) {
            index++;
            if(index==key->length) {
                match->node=node;
                return 1;
            }
            if(node->terminal) {
                match->node=node;
                match->index=key->chars[index++];
                return index==key->length;
            }
            if(node->kind!=-1)
                return 0;
            if(!node->child)
                return 0;
            node=trie->nodes+node->child;
            continue;
        } else {
            if(!node->sibling)
                return 0;
            node=trie->nodes+node->sibling;
        }
    }
}
