// SLY3_CFLAGS: -Os -G0
struct IndexedRowWords { int word0; int word1; int word2; int word3; };
struct IndexedRowTable { unsigned char opaque[0x2C]; struct IndexedRowWords rows[1]; };

int func_001C21E0(void *rows, int index)
{
    return ((struct IndexedRowTable *)rows)->rows[index].word2;
}
