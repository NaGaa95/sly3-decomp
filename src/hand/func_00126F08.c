// Real scene-pointer and packed-vector-pointer CRef payload views.
// Historical pbasicA1 is unused by the original wrapper and retained as a caller formal.
// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef int TI __attribute__((mode(TI)));
struct SCENE_OBJECT;
typedef union CRefPayload { int word; struct SCENE_OBJECT *scene; const TI *vector; } CRefPayload;
typedef struct CRef { short m_tagk; short m_padding; CRefPayload m_tag; } CRef;
void Decref__4CRef(CRef *pref);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
void InitTag__4CRef(CRef *pref, int tagk);
void func_0012AFA0(CRef *pref, TI vec);
TI func_001C9428(struct SCENE_OBJECT *source, struct SCENE_OBJECT *destination, TI point);
CRef *func_00126F08(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    func_0012AFA0(&ref, func_001C9428(aref[0].m_tag.scene, aref[1].m_tag.scene, *aref[2].m_tag.vector));
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
