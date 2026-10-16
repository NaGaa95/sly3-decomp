// SLY3_CFLAGS: -Os -G0
struct Ref;
struct SourceRecord { int word0; int word1; int word2; };
struct GatherSource { unsigned char opaque[0x16B0]; struct SourceRecord records[4]; int count; };
struct Ref *func_0024AEF8(struct Ref *output, int count, int type, void *values);
struct Ref *func_001EB288(struct Ref *output, void *receiver)
{
    struct GatherSource *source = (struct GatherSource *)receiver;
    int values[4];
    int index;
    for (index = 0; index < source->count; index++)
        values[index] = source->records[index].word0;
    func_0024AEF8(output, source->count, 0x2002, values);
    return output;
}
