// SLY3_ASFIX: engine-exit-slots
/* strchr-style search (cf. Sly 2 strchr game copy). */
char *func_002716C8(const char *p, int ch)
{
    do {
        if (*(unsigned char *)p == ch)
            goto done;
    } while (*p++);
    p = 0;
done:
    return (char *)p;
}
