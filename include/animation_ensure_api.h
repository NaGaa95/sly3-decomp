#ifndef SLY3_ANIMATION_ENSURE_API_H
#define SLY3_ANIMATION_ENSURE_API_H
struct ASEG;
struct ALO;
struct ASEGA;
struct SeekRuntime;
#ifdef __cplusplus
extern "C" {
#endif
struct ASEGA *func_00137448(struct ASEG *animation,struct ALO *owner);
void func_00136908(struct ASEG *animation,struct ALO *owner,float time,float rate,
                   int flags,struct ASEGA **output);
void func_00137D08(struct SeekRuntime *runtime,int seek,float time,float rate,
                   int update_mode);
#ifdef __cplusplus
}
#endif
#endif
