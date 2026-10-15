/* Module02 export42: actual IRX identification record pointer. */
struct irx_id { const char *name; unsigned short version; };
typedef char assert_irx_id_size[(sizeof(struct irx_id) == 8) ? 1 : -1];
extern struct irx_id mcman_module_id;

struct irx_id *McGetModuleInfo(void)
{
    return &mcman_module_id;
}
