// SLY3_CFLAGS: -Os -G0 -ffast-math
// Cell-edge state machine: re-evaluates the state of one slot until it settles; each state tests the (x, y) offsets
// against the cell border (0.5026548 or 0.2513274) and asks for the transition to the next state.
struct Cursor {
    char pad[0x1E4];
    float margin[7];
    float x;
    float y;
    int pad208;
    int state[3];
};
float func_001CABB8(struct Cursor *c, int idx);
void func_001CAE80(struct Cursor *c, int idx, int to);
void func_001CAD10(struct Cursor *c, int to);
void func_001CA078(struct Cursor *c, int idx)
{
    int state;
    do {
        float w, a, b;
        state = c->state[idx];
        w = func_001CABB8(c, idx) * c->margin[idx];
        b = c->y - w;
        a = c->x - w;
        switch (state) {
        case -1:
            break;
        case 0:
            if (b + 0.50265485f <= 0.0f && a + 0.50265485f > 0.0f)
                func_001CAE80(c, idx, 3);
            {
                float ym = c->y + c->margin[idx];
                float xm = c->x + c->margin[idx];
                if (ym - 0.50265485f >= 0.0f && xm - 0.50265485f < 0.0f)
                    func_001CAE80(c, idx, 4);
            }
            break;
        case 1:
            if (b + 0.50265485f <= 0.0f && a + 0.50265485f > 0.0f)
                func_001CAE80(c, idx, 3);
            break;
        case 2:
            if (b - 0.50265485f >= 0.0f && a - 0.50265485f < 0.0f)
                func_001CAE80(c, idx, 4);
            break;
        case 3:
            if (b + 0.251327425f <= 0.0f && a + 0.251327425f > 0.0f) {
                int n;
                func_001CAE80(c, idx, 5);
                n = idx + 1;
                if (n >= 0 && n < 3)
                    func_001CAE80(c, n, 2);
            }
            break;
        case 4:
            if (b - 0.251327425f >= 0.0f && a - 0.251327425f < 0.0f) {
                int n;
                func_001CAE80(c, idx, 6);
                n = idx + 1;
                if (n >= 0 && n < 3)
                    func_001CAE80(c, n, 1);
            }
            break;
        case 5:
            if (b - 0.251327425f <= 0.0f && a - 0.251327425f > 0.0f) {
                int n = idx + 2;
                if (n < 0 || n >= 3 || c->state[n] == -1)
                    func_001CAD10(c, 2);
            }
            break;
        case 6:
            if (b + 0.251327425f >= 0.0f && a + 0.251327425f < 0.0f) {
                int n = idx + 2;
                if (n < 0 || n >= 3 || c->state[n] == -1)
                    func_001CAD10(c, 2);
            }
            break;
        }
    } while (state != c->state[idx]);
}
