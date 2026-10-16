#include "range_context_api.h"
extern "C" void func_00292034(void *p, int c, int n);
extern "C" void func_00196AA8(ZPR *pzpr, int baseWord, int limitWord)
{
    func_00292034(pzpr, 0, sizeof(ZPR));
    pzpr->baseWord = pzpr->currentWord = baseWord;
    pzpr->limitWord = limitWord;
}
