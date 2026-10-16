#ifndef SLY3_RANGE_CONTEXT_API_H
#define SLY3_RANGE_CONTEXT_API_H
typedef struct ZPR {
    int baseWord;
    int currentWord;
    int limitWord;
    char unknown0C[0x630-12];
} ZPR;
typedef char RangeContextWord32[(sizeof(int)==4)?1:-1];
typedef char RangeContextSize630[(sizeof(ZPR)==0x630)?1:-1];
#ifdef __cplusplus
extern "C" {
#endif
void func_00196AA8(ZPR *context,int baseWord,int limitWord);
#ifdef __cplusplus
}
#endif
#endif
