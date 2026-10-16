#ifndef SLY3_WAIT_BIND_API_H
#define SLY3_WAIT_BIND_API_H
#ifdef __cplusplus
extern "C" {
#endif
struct WaitBindState;
struct WaitBindTemplate;
struct WaitBindOverride;
void func_00197838(struct WaitBindState *state,
                   struct WaitBindTemplate *value,
                   unsigned int word,
                   struct WaitBindOverride *override);
#ifdef __cplusplus
}
#endif
#endif
