// Original USA entry 0x13d108; ordinary C reconstruction.
// Receiver A0 and two signed32-bit deltas A1/A2 are explicit. Complete1F43C8/1F4430 read only receiver16C/174; complete1F43D0/1F4438 consume receiver and the calculated value and implement their original clamps.1F48A0 receives receiver/both deltas and creates its own complete six-input event. No inherited floating argument is consumed.
// SLY3_CFLAGS: -Os -G0
int func_001F43C8(void *);
void func_001F43D0(void *,int);
int func_001F4430(void *);
void func_001F4438(void *,int);
void func_001F48A0(void *,int,int);
void func_0013D108(void *p,int first,int second)  {
    func_001F43D0(p,func_001F43C8(p)+first);
    func_001F4438(p,func_001F4430(p)+second);
    func_001F48A0(p,first,second);
}
