// SLY3_CFLAGS: -Os -G0
struct GridObject { unsigned char prefix[0x18]; int id; };
struct GridOwner { unsigned char prefix[0x88]; int cells[0x28][0x20]; };
struct GridPosition { int row; int column; };
int *func_00185860(struct GridOwner *grid,struct GridObject *object,struct GridPosition *position)
{
    int row,column;
    for(row=0;row<0x28;row++) {
        for(column=0;column<0x20;column++) {
            int *cell=&grid->cells[row][column];
            if(object->id==*cell) {
                if(position) {
                    position->row=row;
                    position->column=column;
                }
                return cell;
            }
        }
    }
    if(position) {
        position->row=-1;
        position->column=-1;
    }
    return 0;
}
