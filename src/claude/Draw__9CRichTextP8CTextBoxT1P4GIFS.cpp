// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 port of Sly 2 CRichText::Draw (src/hand).
struct RGBA { unsigned char r, g, b, a; };
struct GIFS;
struct FONT { char pad[0xC]; int dy; char pad10[4]; float ry; };
struct CFont;
class CTextBox {
public:
    float x, y, dx, dy;
    RGBA rgba;
    int jh;
    int jv;
};
class CRichText {
public:
    unsigned char *m_achz;
    unsigned char *m_pchCur;
    int m_pad8[2];
    CFont *m_pfontCur;
    FONT *m_pfontBase;
    char pad[0x160 - 0x18];
    int m_fDirty;
    unsigned int m_rgbaCur;
    void Draw(CTextBox *ptb, CTextBox *ptbClip, GIFS *pgifs);
};
extern "C" {
void *func_00292034(void *, int, unsigned int);
void func_001813B0(CRichText *p);
int func_00181410(CRichText *p);
float func_00180A30(CFont *pfont, int ch);
void func_001813E8(CRichText *p, RGBA *prgba);
void func_00180B60(CFont *pfont, CTextBox *ptb, GIFS *pgifs);
void func_00180D80(CFont *pfont, GIFS *pgifs);
float func_00180E18(CFont *pfont, int ch, float x, float y, unsigned int rgba, GIFS *pgifs);
void func_001808E0(CFont *pfont, CTextBox *ptb, GIFS *pgifs);
}
void CRichText::Draw(CTextBox *ptb, CTextBox *ptbClip, GIFS *pgifs)
{
    float adx[64];
    int fNewLine = 1;
    int iline = 0;
    int ch;
    float x, y;
    CFont *pfontSetup;
    float *pdx;
    RGBA rgba;
    func_00292034(adx, 0, sizeof(adx));
    func_001813B0(this);
    {
        int chT;
        while ((chT = func_00181410(this)) != 0) {
            if (chT == '\n')
                iline++;
            else
                adx[iline] += func_00180A30(m_pfontCur, chT);
        }
    }
    if (ptb->jv == 0) {
        y = ptb->y;
    } else {
        float dy = (float)(iline + 1) * ((float)m_pfontBase->dy * m_pfontBase->ry);
        if (ptb->jv == 2)
            y = ptb->y + ptb->dy - dy;
        else
            y = ptb->y + (ptb->dy - dy) * 0.5f;
    }
    rgba = ptb->rgba;
    func_001813E8(this, &rgba);
    pfontSetup = 0;
    func_001813B0(this);
    pdx = adx;
    while ((ch = func_00181410(this)) != 0) {
        if (ch == '\n') {
            fNewLine = 1;
            pdx++;
            y += (float)m_pfontBase->dy * m_pfontBase->ry;
            continue;
        }
        if (fNewLine) {
            if (ptb->jh == 0)
                x = ptb->x;
            else {
                float dxLine = *pdx;
                if (ptb->jh == 2)
                    x = ptb->x + ptb->dx - dxLine;
                else
                    x = ptb->x + (ptb->dx - dxLine) * 0.5f;
            }
            fNewLine = 0;
        }
        if (!pfontSetup) {
            func_00180B60(m_pfontCur, ptbClip, pgifs);
            pfontSetup = m_pfontCur;
        } else if (m_fDirty) {
            func_00180D80(m_pfontCur, pgifs);
            m_fDirty = 0;
        }
        x += func_00180E18(m_pfontCur, ch, x, y, m_rgbaCur, pgifs);
    }
    func_001808E0(m_pfontCur, ptbClip, pgifs);
}
