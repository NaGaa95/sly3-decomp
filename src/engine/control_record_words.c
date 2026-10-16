typedef unsigned int RecordWord;

typedef struct ControlWordRecordPrefix {
    int kind;
    RecordWord payload;
    int word8;
    int wordC;
    int word10;
    int inverse14;
} ControlWordRecordPrefix;

extern void *func_00197628(void *owner, int kind, RecordWord payload);

void func_001973B8(void *owner, RecordWord payload, int word8, int wordC,
                   int word10, int flag)
{
    ControlWordRecordPrefix *record = func_00197628(owner, 6, payload);

    record->word8 = word8;
    record->wordC = wordC;
    record->word10 = word10;
    record->inverse14 = !flag;
}
