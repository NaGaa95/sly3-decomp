// SLY3_CFLAGS: -Os -G0
typedef unsigned int RecordWord;

typedef struct ControlExtraRecordPrefix {
    int kind;
    RecordWord payload;
    RecordWord word8;
    RecordWord wordC;
} ControlExtraRecordPrefix;

void *func_00197628(void *owner, int kind, RecordWord payload);

void func_00197528(void *owner, RecordWord payload, RecordWord word8,
                   RecordWord wordC)
{
    ControlExtraRecordPrefix *record = func_00197628(owner, 0xD, payload);

    record->word8 = word8;
    record->wordC = wordC;
}
