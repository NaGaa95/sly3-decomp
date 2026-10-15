#ifndef SLY3_CARD_COMMANDS_H
#define SLY3_CARD_COMMANDS_H
#ifdef __cplusplus
extern "C" {
#endif
// The original dispatcher consumes the integer request/command and optional
// integer result pointer. Its first physical caller input is unused.
int func_001CEFC8(void *unusedContext, int request, int command, int *result);
#ifdef __cplusplus
}
#endif
#endif
