/* Private measured EE pointer/index API proposal; no historical formal float order claim. */
#ifndef SLY3_PRIVATE_ACTOR_STATE_RESOURCE_API_H
#define SLY3_PRIVATE_ACTOR_STATE_RESOURCE_API_H
#ifdef __cplusplus
extern "C" {
#endif
extern void *D_0036B250;
extern void *D_00370AC0;
extern void *D_0038AE90;
void *func_001F4AD0(void *unused, int index);
void func_001B40F0(void *context, int kind, void *payload, void *record);
void func_00209490(void *context, void *payload);
void func_001B77F8(void *request, int mode, void *payload);
void func_00154C00(void *receiver, void *payload);
int func_002489A0(void *context, int id);
void func_002462B8(void *receiver, int index, void *target, float scale, float *range);
#ifdef __cplusplus
}
#endif
#endif
