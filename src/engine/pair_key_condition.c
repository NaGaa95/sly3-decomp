// SLY3_CFLAGS: -Os -G0
typedef struct PairRawKey { unsigned int word; } PairRawKey;
typedef struct PairKeyPeer {
    char prefix[0x14];
    PairRawKey *key;
} PairKeyPeer;
typedef struct PairKeyOwner {
    char prefix[0x1E8];
    PairKeyPeer *linked;
} PairKeyOwner;
int func_0023E178(void *first, void *second);
int func_0013CD00(int first, int second);

int func_0014D188(PairKeyOwner *owner, PairKeyPeer *peer)
{
    int result = func_0023E178(owner, peer);
    if (peer->key->word == owner->linked->key->word)
        result = func_0013CD00(result, 1);
    return result;
}
