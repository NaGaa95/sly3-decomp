/* Sly 3 script wrappers using the supplied Sly 2 CRef calling convention.
 * Source attribution: references/sly2/include/splicewrap.h.
 * All helper locations require independently resolved Sly 3 relocations. */
#ifndef SLY3_SPLICEWRAP_H
#define SLY3_SPLICEWRAP_H
#include "m2c_prelude.h"
typedef struct CRef { s32 m_tagk; s32 m_tag; } CRef;
typedef s32 OTYP;
void RefSetArgsFromSplice__FiP4CRefP4OTYPe(CRef *ret, s32 cref, CRef *aref, OTYP *aotyp, ...);
void Decref__4CRef(CRef *pref);
void InitTag__4CRef(CRef *pref, s32 tagk);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
#define TAGK_Void 0x24
#endif
