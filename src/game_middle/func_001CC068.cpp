// SLY3_CFLAGS: -Os -G0 -ffast-math -fno-exceptions -fno-rtti
// Sort line-segment records by how many of their end points are attached: segments attached at both ends are chained
// on *pplsgBoth, free ones on a private list, and half-attached ones are bucketed per end point (same routine as Sly 2
// CategorizeAlsg). Segments whose end point is attached to nothing else are moved to *pplsgBoth afterwards.
struct VECTOR { float x, y, z; } __attribute__((aligned(16)));
struct EDGE { unsigned short aipos[2]; };
struct LSG {
    VECTOR posA;
    VECTOR posB;
    VECTOR normalA;
    VECTOR normalB;
    float gA, gB;
    int pad48;
    int fA, fB;
    EDGE *pedge;
    int iend;
    LSG *plsgNext;
};
extern "C" void *func_00291F38(void *dst, const void *src, int cb);

extern "C" void func_001CC068(int clsg, LSG *alsg, int *pcpos, int *aipos, LSG **aplsg, LSG **pplsgBoth)
{
    LSG *plsgNone = 0;
    int cpos = 0;
    int ilsg;
    int ipos;
    LSG *plsg;

    *pplsgBoth = 0;
    for (ilsg = 0; ilsg < clsg; ilsg++) {
        plsg = &alsg[ilsg];
        if (plsg->fA && plsg->fB) {
            plsg->plsgNext = *pplsgBoth;
            *pplsgBoth = plsg;
        } else if (!plsg->fA && !plsg->fB) {
            plsg->plsgNext = plsgNone;
            plsgNone = plsg;
        } else {
            if (plsg->fA) {
                VECTOR vecT;
                vecT = plsg->posA; plsg->posA = plsg->posB; plsg->posB = vecT;
                vecT = plsg->normalA; plsg->normalA = plsg->normalB; plsg->normalB = vecT;
                {
                    float gT = plsg->gA; plsg->gA = plsg->gB; plsg->gB = gT;
                }
                {
                    int fT = plsg->fA; plsg->fA = plsg->fB; plsg->fB = fT;
                }
                plsg->iend = 1;
            }
            for (ipos = 0; ipos < cpos; ipos++) {
                if (plsg->pedge->aipos[plsg->iend] == aipos[ipos])
                    break;
            }
            if (ipos >= cpos) {
                aipos[ipos] = plsg->pedge->aipos[plsg->iend];
                cpos++;
            } else {
                plsg->plsgNext = aplsg[ipos];
            }
            aplsg[ipos] = plsg;
        }
    }

    for (ipos = 0; ipos < cpos; ipos++) {
        LSG **pplsg;
        int *pipos;
        if (aplsg[ipos]->plsgNext)
            continue;
        for (plsg = plsgNone; plsg; plsg = plsg->plsgNext) {
            if (plsg->pedge->aipos[0] == aipos[ipos] || plsg->pedge->aipos[1] == aipos[ipos])
                goto next;
        }
        pplsg = &aplsg[ipos];
        aplsg[ipos]->plsgNext = *pplsgBoth;
        *pplsgBoth = aplsg[ipos];
        func_00291F38(pplsg, pplsg + 1, (cpos - ipos) * 4 - 4);
        pipos = &aipos[ipos];
        func_00291F38(pipos, pipos + 1, (cpos - ipos) * 4 - 4);
        // Same as ipos--; the split update gives loop strength reduction the third increment the original has.
        ipos -= 2;
        ipos++;
        cpos--;
    next:;
    }

    *pcpos = cpos;
}
