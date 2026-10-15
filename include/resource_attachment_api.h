/* Private measured EE attachment inputs. Counted-list identities remain raw int keys. */
#ifndef SLY3_PRIVATE_RESOURCE_ATTACHMENT_API_H
#define SLY3_PRIVATE_RESOURCE_ATTACHMENT_API_H
typedef int EE_ATTACHMENT_QWORD __attribute__((mode(TI)));
#ifdef __cplusplus
extern "C" {
#endif
void func_0013BD00(void *receiver, int key);
void func_0013BD88(void *receiver, int key);
void func_001309D8(void **task);
void *func_00130078(void *owner, void *channel, int mode, int event, int flags, EE_ATTACHMENT_QWORD value);
void func_002568E8(void *owner, void *parameter, void *node, EE_ATTACHMENT_QWORD value);
void *func_00238690(void *factory, int kind);
void *func_002B58E8(void *receiver);
void func_001A4CD0(void *receiver, int state);
#ifdef __cplusplus
}
#endif
#endif
