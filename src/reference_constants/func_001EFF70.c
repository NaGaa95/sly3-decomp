// Original USA entry 0x1eff70; ordinary C reconstruction.
// Only receiver A0 is consumed.152488 and its24D9D8 base initializer derive their inputs from receiver fields.258958 receives each real embedded object at1480/1530;155190 consumes receiver and selector2E.23DDA0 receives receiver/selector22/type1, returning the actual pointer stored1190.1C1410 takes receiver and the explicit15F0/16F0 array/output pointers; its floating inputs are constructed internally.
// SLY3_CFLAGS: -Os -G0
void func_00152488(void *);
void func_00258958(void *);
void func_00155190(void *,int);
void *func_0023DDA0(void *,int,int);
void func_001C1410(void *,void *,void *);
void func_001EFF70(char *p)  {
    func_00152488(p);
    func_00258958(p+0x1480);
    func_00258958(p+0x1530);
    func_00155190(p,0x2E);
    *(void **)(p+0x1190)=func_0023DDA0(p,0x22,1);
    func_001C1410(p,p+0x15F0,p+0x16F0);
}
