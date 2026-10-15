/* Reconstructed module-local view: original reads only the next link at +0xC8. */
typedef struct SndChainNode {
    unsigned char opaque[200];
    const struct SndChainNode *next;
} SndChainNode;

typedef char SndChainNode_size_check[sizeof(SndChainNode) == 204 ? 1 : -1];

unsigned int snd_count_chain(const SndChainNode *node)
{
    unsigned int count = 0;
    while (node != 0) {
        node = node->next;
        ++count;
    }
    return count;
}
