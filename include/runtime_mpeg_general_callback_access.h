#ifndef RUNTIME_MPEG_GENERAL_CALLBACK_ACCESS_H
#define RUNTIME_MPEG_GENERAL_CALLBACK_ACCESS_H
typedef struct RuntimeMpegGeneralCallback {
    void *callback;
    void *context;
    int saved_gp;
} RuntimeMpegGeneralCallback;
typedef struct RuntimeMpegGeneralCallbackState {
    unsigned char opaque00[0x0c];
    RuntimeMpegGeneralCallback callbacks[5];
} RuntimeMpegGeneralCallbackState;
typedef struct RuntimeMpegGeneralCallbackOwner {
    unsigned char opaque00[0x40];
    RuntimeMpegGeneralCallbackState *state;
} RuntimeMpegGeneralCallbackOwner;

void *func_002AA050(RuntimeMpegGeneralCallbackOwner *owner, int index,
                   void *callback, void *context);
#define MPEG_GENERAL_OFF(type, member) ((unsigned int)&((type *)0)->member)
typedef char RuntimeMpegGeneralCallbackLayoutCheck[
    (sizeof(void *) == 4 && sizeof(int) == 4 && sizeof(RuntimeMpegGeneralCallback) == 12 &&
     MPEG_GENERAL_OFF(RuntimeMpegGeneralCallbackOwner, state) == 0x40 &&
     MPEG_GENERAL_OFF(RuntimeMpegGeneralCallbackState, callbacks) == 0x0c) ? 1 : -1];
#undef MPEG_GENERAL_OFF
#endif
