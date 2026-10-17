// SLY3_CFLAGS: -Os -G0
struct Filter { unsigned char prefix[8]; int type; int classKey; int kindKey; };
int func_001C8768(void *object,int key);
int func_0013B500(void *object,int key);
int func_00283340(struct Filter *filter,int type,void *object)
{
    if(filter->type!=type)
        return 0;
    if(filter->classKey!=-1&&(!object||!func_001C8768(object,filter->classKey)))
        return 0;
    if(filter->kindKey==-1)
        return 1;
    if(!object||!func_0013B500(object,filter->kindKey))
        return 0;
    return 1;
}
