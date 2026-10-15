#ifndef SLY3_CARD_TRANSFER_API_H
#define SLY3_CARD_TRANSFER_API_H
#ifdef __cplusplus
extern "C" {
#endif
int func_001D0860(void *save, const char *path, int mode, int *descriptor);
int func_001D0970(void *save, int descriptor, void *buffer, int bytes, int *written);
#ifdef __cplusplus
}
#endif
#endif
