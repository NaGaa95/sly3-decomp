#ifndef SLY3_ATTACHMENT_CREATION_API_H
#define SLY3_ATTACHMENT_CREATION_API_H
typedef int AttachmentPackedPosition __attribute__((mode(TI)));
#ifdef __cplusplus
extern "C" {
#endif
/* Real space pointer A0, whole packed position A1, raw word A2, optional output A3. */
void func_00173778(void *space,AttachmentPackedPosition position,int attachmentWord,void **output);
void *func_001738C0(void *space,AttachmentPackedPosition position,int attachmentWord);
void func_001738E0(void *receiver);
#ifdef __cplusplus
}
#endif
#endif
