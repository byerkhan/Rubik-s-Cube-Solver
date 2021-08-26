#include <stdio.h>
#include <stdbool.h>

char cube[7][11];
//1:Green 2:Blue 3:Orange 4:Red 5:White 6:Yellow
//123456789When you are facing the colour sequence of green, blue, orange and red from the upper left to lower right, the colour of the bottom will be yellow. When you are facing the white colour surface, the bottom will be green and blue when you are facing yellow
struct Block
{
    int fb_face; //front/back mark
    int fb_pos;  //front/back face position
    int ud_face; //up/down
    int ud_pos;
    int lr_face; //left/right
    int lr_pos;
}block[20]={{1,1,5,7,3,3},{1,2,5,8,0,0},{1,3,5,9,4,1},{1,4,0,0,3,6},{1,6,0,0,4,4},{1,7,6,1,3,9},{1,8,6,2,0,0},{1,9,6,3,4,7},
    {0,0,5,4,3,2},{0,0,5,6,4,2},{0,0,6,4,3,8},{0,0,6,6,4,8},{2,3,5,1,3,1},{2,1,5,3,4,3},{2,2,5,2,0,0},{2,6,0,0,3,4},
    {2,4,0,0,4,6},{2,7,6,9,4,9},{2,8,6,8,0,0},{2,9,6,7,3,7}}; //record neighbor information of all blocks

bool IsCornerBlock(int i) //determine if a block is a corner block
{
    if(block[i].fb_face==0 || block[i].lr_face==0 || block[i].ud_face==0) return false;
    return true;
}

int Block_Contain_Color(int i,char color) //find if there is a specified color on this block and return the color position, 0 means no such color
{
    if(cube[block[i].fb_face][block[i].fb_pos]==color) return 1;
    if(cube[block[i].lr_face][block[i].lr_pos]==color) return 2;
    if(cube[block[i].ud_face][block[i].ud_pos]==color) return 3;
    return 0;
}
void Rotate(int id,int dir); //change the element on this side

void U(void);
void Ui(void);
void R(void);
void Ri(void);
void F(void);
void Fi(void);
void L(void);
void Li(void);
void B(void);
void Bi(void);
void D(void);
void Di(void);  //basic formula, including output

void Bottom(void);  //restore the bottom surface
void Layer2(void);  //restore the second layer
void OLL(void); //OLL
void PLL(void); //PLL
//solving rubik‘s cube formula
int main()
{
    char strin[10];
    for(int i=1;i<=6;i++)
    {
        scanf("%s", strin);
        for(int j=0;j<=8;j++) cube[i][j+1]=strin[j];
    }
    Bottom();
    Layer2();
    OLL();
    PLL();
    printf("\n");
    /*
     for(int i=1;i<=6;i++)
     {
     for(int j=1;j<=9;j++) cout << cube[i][j];
     cout << endl;
     }
     */
    //debug the program, comment it out first and run it when needed
    return 0;
}
void Rotate(int id,int dir) //id is the face number, dir is the direction of rotation, 1 is clockwise, and 0 is counterclockwise
{
    char tmp=cube[id][2];
    if(dir==1)
    {
        cube[id][2]=cube[id][4];
        cube[id][4]=cube[id][8];
        cube[id][8]=cube[id][6];
        cube[id][6]=tmp;
    }
    else
    {
        cube[id][2]=cube[id][6];
        cube[id][6]=cube[id][8];
        cube[id][8]=cube[id][4];
        cube[id][4]=tmp;
    }
    tmp=cube[id][1];
    if(dir==1)
    {
        cube[id][1]=cube[id][7];
        cube[id][7]=cube[id][9];
        cube[id][9]=cube[id][3];
        cube[id][3]=tmp;
    }
    else
    {
        cube[id][1]=cube[id][3];
        cube[id][3]=cube[id][9];
        cube[id][9]=cube[id][7];
        cube[id][7]=tmp;
    }
}
void U() //White
{
    Rotate(5,1);
    char temp[5];
    for(int i=1;i<=3;i++) temp[i]=cube[1][i];
    for(int i=1;i<=3;i++) cube[1][i]=cube[4][i];
    for(int i=1;i<=3;i++) cube[4][i]=cube[2][i];
    for(int i=1;i<=3;i++) cube[2][i]=cube[3][i];
    for(int i=1;i<=3;i++) cube[3][i]=temp[i];
    printf("U ");
}
void Ui() //White
{
    Rotate(5,0);
    char temp[5];
    for(int i=1;i<=3;i++) temp[i]=cube[1][i];
    for(int i=1;i<=3;i++) cube[1][i]=cube[3][i];
    for(int i=1;i<=3;i++) cube[3][i]=cube[2][i];
    for(int i=1;i<=3;i++) cube[2][i]=cube[4][i];
    for(int i=1;i<=3;i++) cube[4][i]=temp[i];
    printf("Ui ");
}
void R() //Red
{
    Rotate(4,1);
    char temp[5];
    for(int i=3,j=1;i<=9;i+=3,j++) temp[j]=cube[1][i];
    for(int i=3;i<=9;i+=3) cube[1][i]=cube[6][i];
    for(int i=3;i<=9;i+=3) cube[6][i]=cube[2][10-i];
    for(int i=3;i<=9;i+=3) cube[2][10-i]=cube[5][i];
    for(int i=3,j=1;i<=9;i+=3,j++) cube[5][i]=temp[j];
    printf("R ");
}
void Ri() //Red
{
    Rotate(4,0);
    char temp[5];
    for(int i=3,j=1;i<=9;i+=3,j++) temp[j]=cube[1][i];
    for(int i=3;i<=9;i+=3) cube[1][i]=cube[5][i];
    for(int i=3;i<=9;i+=3) cube[5][i]=cube[2][10-i];
    for(int i=3;i<=9;i+=3) cube[2][10-i]=cube[6][i];
    for(int i=3,j=1;i<=9;i+=3,j++) cube[6][i]=temp[j];
    printf("Ri ");
}
void F() //Green
{
    Rotate(1,1);
    char temp[5];
    for(int i=1,j=1;i<=7;i+=3,j++) temp[j]=cube[4][i];
    for(int i=1;i<=7;i+=3) cube[4][i]=cube[5][i/3+7];
    for(int i=1;i<=7;i+=3) cube[5][9-i/3]=cube[3][i+2];
    for(int i=1;i<=7;i+=3) cube[3][i+2]=cube[6][i/3+1];
    for(int i=1,j=3;i<=7;i+=3,j--) cube[6][i/3+1]=temp[j];
    printf("F ");
}
void Fi() //Green
{
    Rotate(1,0);
    char temp[5];
    for(int i=1,j=1;i<=7;i+=3,j++) temp[j]=cube[4][i];
    for(int i=1;i<=7;i+=3) cube[4][i]=cube[6][3-i/3];
    for(int i=1;i<=7;i+=3) cube[6][i/3+1]=cube[3][i+2];
    for(int i=1;i<=7;i+=3) cube[3][i+2]=cube[5][9-i/3];
    for(int i=1,j=1;i<=7;i+=3,j++) cube[5][i/3+7]=temp[j];
    printf("Fi ");
}
void L() //Orange
{
    Rotate(3,1);
    char temp[5];
    for(int i=1,j=1;i<=7;i+=3,j++) temp[j]=cube[1][i];
    for(int i=1;i<=7;i+=3) cube[1][i]=cube[5][i];
    for(int i=1;i<=7;i+=3) cube[5][i]=cube[2][9-((i-1)/3)*3];
    for(int i=3;i<=9;i+=3) cube[2][i]=cube[6][10-i];
    for(int i=1,j=1;i<=7;i+=3,j++) cube[6][i]=temp[j];
    printf("L ");
}
void Li() //Orange
{
    Rotate(3,0);
    char temp[5];
    for(int i=1,j=1;i<=7;i+=3,j++) temp[j]=cube[1][i];
    for(int i=3;i<=9;i+=3) cube[1][i-2]=cube[6][i-2];
    for(int i=3;i<=9;i+=3) cube[6][i-2]=cube[2][12-i];
    for(int i=3;i<=9;i+=3) cube[2][12-i]=cube[5][i-2];
    for(int i=1,j=1;i<=7;i+=3,j++) cube[5][i]=temp[j];
    printf("Li ");
}
void B() //Blue
{
    Rotate(2,1);
    char temp[5];
    for(int i=3,j=1;i<=9;i+=3,j++) temp[j]=cube[3][10-i];
    for(int i=3;i<=9;i+=3) cube[3][10-i]=cube[5][i/3];
    for(int i=3;i<=9;i+=3) cube[5][i/3]=cube[4][i];
    for(int i=3;i<=9;i+=3) cube[4][i]=cube[6][10-i/3];
    for(int i=3,j=1;i<=9;i+=3,j++) cube[6][10-i/3]=temp[j];
    printf("B ");
}
void Bi() //Blue
{
    Rotate(2,0);
    char temp[5];
    for(int i=3,j=1;i<=9;i+=3,j++) temp[j]=cube[3][10-i];
    for(int i=3;i<=9;i+=3) cube[3][10-i]=cube[6][10-i/3];
    for(int i=3;i<=9;i+=3) cube[6][10-i/3]=cube[4][i];
    for(int i=3;i<=9;i+=3) cube[4][i]=cube[5][i/3];
    for(int i=3,j=1;i<=9;i+=3,j++) cube[5][i/3]=temp[j];
    printf("Bi ");
}
void D() //Yellow
{
    Rotate(6,1);
    char temp[5];
    for(int i=7,j=1;i<=9;i++,j++) temp[j]=cube[1][i];
    for(int i=7;i<=9;i++) cube[1][i]=cube[3][i];
    for(int i=7;i<=9;i++) cube[3][i]=cube[2][i];
    for(int i=7;i<=9;i++) cube[2][i]=cube[4][i];
    for(int i=7,j=1;i<=9;i++,j++) cube[4][i]=temp[j];
    printf("D ");
}
void Di() //Yellow
{
    Rotate(6,0);
    char temp[5];
    for(int i=7,j=1;i<=9;i++,j++) temp[j]=cube[1][i];
    for(int i=7;i<=9;i++) cube[1][i]=cube[4][i];
    for(int i=7;i<=9;i++) cube[4][i]=cube[2][i];
    for(int i=7;i<=9;i++) cube[2][i]=cube[3][i];
    for(int i=7,j=1;i<=9;i++,j++) cube[3][i]=temp[j];
    printf("Di ");
}
void Cross(int i,char color) //return the corresponding edge to the yellow-green edge
{
    switch(Block_Contain_Color(i,color))
    {
        case 0:break;
        case 1: //on the front and back side
        {
            if(block[i].fb_face==1) //on the front side
            {
                switch(block[i].fb_pos)
                {
                    case 2:F();F();break;
                    case 4:Fi();break;
                    case 6:F();break;
                    case 8:break;
                }
            }
            else //on the back side
            {
                switch(block[i].fb_pos)
                {
                    case 2:U();U();F();F();;break;
                    case 4:B();U();U();F();F();Bi();break;
                    case 6:Bi();U();U();F();F();B();break;
                    case 8:B();B();U();U();F();F();break;
                }
            }
            return; //after this block is processed, process the next block. same below
        }
        case 2: //on the left and right side
        {
            if(block[i].lr_face==3) //on the left side
            {
                switch(block[i].lr_pos)
                {
                    case 2:Ui();F();F();break;
                    case 4:Di();Li();D();break;
                    case 6:Di();L();D();break;
                    case 8:L();L();Ui();F();F();break;
                }
            }
            else //on the right side
            {
                switch(block[i].lr_pos)
                {
                    case 2:U();F();F();break;
                    case 4:D();Ri();Di();break;
                    case 6:D();R();Di();break;
                    case 8:R();R();U();F();F();break;
                }
            }
            return;
        }
        case 3: //on the up and down side
        {
            if(block[i].ud_face==5) //on the up side
            {
                switch(block[i].ud_pos)
                {
                    case 2:U();U();F();D();Ri();Di();break;
                    case 4:Ui();F();D();Ri();Di();break;
                    case 6:U();F();D();Ri();Di();break;
                    case 8:F();D();Ri();Di();break;
                }
            }
            else //on the down side
            {
                switch(block[i].ud_pos)
                {
                    case 2:Fi();D();Ri();Di();break;
                    case 4:Li();Fi();break;
                    case 6:R();F();break;
                    case 8:B();D();R();Di();break;
                }
            }
            return;
        }
    }
}
void BottomCorner_FirstStep(int i,bool *IsDone)  //corner block restoration step 1: Move it to the upper right, you need to know the block number (i)
{
    if(block[i].ud_face==5) //there are only 8 vertices, which can be divided into top and bottom cases; the situation here is the top cases
    {
        switch(block[i].ud_pos)
        {
            case 1:U();U();break;
            case 3:U();break;
            case 7:Ui();break;
            case 9:break;
        }
    }
    else //on the down side
    {
        if(block[i].ud_pos==3 && cube[6][3]=='Y') {*IsDone=true;return;}  //it has been restored, no action is required, and this information is passed (modify the IsDone variable)
        switch(block[i].ud_pos)
        {
            case 1:Li();Ui();L();break;
            case 3:R();U();Ri();Ui();break;
            case 7:Bi();U();U();B();break;
            case 9:B();U();Bi();break;
        }
    }
}
void BottomCorner_FinalStep(int state,bool IsDone) //the last step of corner block restoration, there are four states; the bool variable is used to determine whether an operation is required
{
    if(IsDone) return; //already restored, no action required
    switch(state)
    {
        case 0:break;
        case 1:Fi();Ui();F();break;
        case 2:R();U();Ri();break;
        case 3:R();U();U();Ri();Ui();R();U();Ri();break;
    }
}
void Bottom() //restore the bottom surface
{
    //bottom side cross
    char Order[5]="GOBR";  //record the restore sequence
    for(int i=0,k=0;i<20;i++)
    {
        if(!IsCornerBlock(i))  //a block of Rubik's Cube
            if(Block_Contain_Color(i,'Y') && Block_Contain_Color(i,Order[k])) //seek block of Rubik's Cube
            {
                Cross(i,Order[k]);
                D();
                k++;  //restore next color
                i=-1;  //reroute all blocks
            }
        if(k==4) break;  //all restoration completed
    }
    //corner block restore
    char _Order[6]="RGOBR";
    for(int i=0,k=0;i<20;i++)
    {
        if(IsCornerBlock(i)) //a corner block
            if(Block_Contain_Color(i,'Y') && Block_Contain_Color(i,_Order[k]) && Block_Contain_Color(i,_Order[k+1]))
            {
                bool IsDone=false;
                bool *p = &IsDone;
                BottomCorner_FirstStep(i,p);
                BottomCorner_FinalStep(Block_Contain_Color(2,'Y'),IsDone);
                D();
                k++;
                i=-1;
            }
        if(k==4) break;
    }
}
bool Layer2_BlockIsDone(int i,int state) //determine whether the restoration of the edge blocks of the second layer is complete
{
    bool IsDone=false;
    switch(state)
    {
        case 1:IsDone=(block[i].fb_face==1 && block[i].fb_pos==6 && cube[1][6]=='G');break;   //green and red
        case 2:IsDone=(block[i].fb_face==1 && block[i].fb_pos==4 && cube[1][4]=='G');break;   //green and orange
        case 3:IsDone=(block[i].fb_face==2 && block[i].fb_pos==4 && cube[2][4]=='B');break;   //red and blue
        case 4:IsDone=(block[i].fb_face==2 && block[i].fb_pos==6 && cube[2][6]=='B');break;   //orange and blue
    }
    return IsDone;
}
void Up_To_Layer2(int i,int state,int type) //to move the top block to the second level, you need the block number i, the state number, and the type number
{
    switch(state)
    {
        case 1:
        {
            if(type==0)
            {
                switch(block[i].ud_pos)
                {
                    case 2:Ui();R();Ui();Ri();Ui();Fi();U();F();break;
                    case 4:R();Ui();Ri();Ui();Fi();U();F();break;
                    case 6:U();U();R();Ui();Ri();Ui();Fi();U();F();break;
                    case 8:U();R();Ui();Ri();Ui();Fi();U();F();break;
                }
            }
            else
            {
                switch(block[i].ud_pos)
                {
                    case 2:Fi();U();F();U();R();Ui();Ri();break;
                    case 4:U();Fi();U();F();U();R();Ui();Ri();break;
                    case 6:Ui();Fi();U();F();U();R();Ui();Ri();break;
                    case 8:U();U();Fi();U();F();U();R();Ui();Ri();break;
                }
            }
            break;
        }
        case 2:
        {
            if(type==1)
            {
                switch(block[i].ud_pos)
                {
                    case 2:U();Li();U();L();U();F();Ui();Fi();break;
                    case 4:U();U();Li();U();L();U();F();Ui();Fi();break;
                    case 6:Li();U();L();U();F();Ui();Fi();break;
                    case 8:Ui();Li();U();L();U();F();Ui();Fi();break;
                }
            }
            else
            {
                switch(block[i].ud_pos)
                {
                    case 2:F();Ui();Fi();Ui();Li();U();L();break;
                    case 4:U();F();Ui();Fi();Ui();Li();U();L();break;
                    case 6:Ui();F();Ui();Fi();Ui();Li();U();L();break;
                    case 8:U();U();F();Ui();Fi();Ui();Li();U();L();break;
                }
            }
            break;
        }
        case 3:
        {
            if(type==1)
            {
                switch(block[i].ud_pos)
                {
                    case 2:Ui();Ri();U();R();U();B();Ui();Bi();break;
                    case 4:Ri();U();R();U();B();Ui();Bi();break;
                    case 6:U();U();Ri();U();R();U();B();Ui();Bi();break;
                    case 8:U();Ri();U();R();U();B();Ui();Bi();break;
                }
            }
            else
            {
                switch(block[i].ud_pos)
                {
                    case 2:U();U();B();Ui();Bi();Ui();Ri();U();R();break;
                    case 4:Ui();B();Ui();Bi();Ui();Ri();U();R();break;
                    case 6:U();B();Ui();Bi();Ui();Ri();U();R();break;
                    case 8:B();Ui();Bi();Ui();Ri();U();R();break;
                }
            }
            break;
        }
        case 4:
        {
            if(type==0)
            {
                switch(block[i].ud_pos)
                {
                    case 2:U();L();Ui();Li();Ui();Bi();U();B();break;
                    case 4:U();U();L();Ui();Li();Ui();Bi();U();B();break;
                    case 6:L();Ui();Li();Ui();Bi();U();B();break;
                    case 8:Ui();L();Ui();Li();Ui();Bi();U();B();break;
                }
            }
            else
            {
                switch(block[i].ud_pos)
                {
                    case 2:U();U();Bi();U();B();U();L();Ui();Li();break;
                    case 4:Ui();Bi();U();B();U();L();Ui();Li();break;
                    case 6:U();Bi();U();B();U();L();Ui();Li();break;
                    case 8:Bi();U();B();U();L();Ui();Li();break;
                }
            }
            break;
        }
    }
}
void Layer2_To_Up(int i)  //turn the second square to the top
{
    if(block[i].fb_face==1)
    {
        if(block[i].fb_pos==4) Up_To_Layer2(8,2,0);
        else Up_To_Layer2(1,1,0);
    }
    else
    {
        if(block[i].fb_pos==4) Up_To_Layer2(9,3,0);
        else Up_To_Layer2(14,4,0);
    }
}
void Layer2() //restore the second layer
{
    for(int i=0;i<20;i++)
    {
        if(!IsCornerBlock(i)) //a block of Rubik's Cube
            if(Block_Contain_Color(i,'G') && Block_Contain_Color(i,'R'))  //green and red block
            {
                if(block[i].ud_face==5) //there are only 8 block in total, which can be divided into the upper and second layers for discussion; the situation here is above
                {
                    if(cube[5][block[i].ud_pos]=='R') Up_To_Layer2(i,1,0); //state 1
                    else Up_To_Layer2(i,1,1);
                    break;  //can end the loop
                }
                else  //on the second layer
                {
                    if(Layer2_BlockIsDone(i,1)) break; //restored, no action required
                    Layer2_To_Up(i);
                    i=-1; //restart the cycle
                }
            }
    }
    for(int i=0;i<20;i++)
    {
        if(!IsCornerBlock(i)) //a block of Rubik's Cube
            if(Block_Contain_Color(i,'G') && Block_Contain_Color(i,'O')) //green and orange block
            {
                if(block[i].ud_face==5)  //there are only 8 block in total, which can be divided into the upper and second layers for discussion; the situation here is above
                {
                    if(cube[5][block[i].ud_pos]=='O') Up_To_Layer2(i,2,1); //state 2
                    else Up_To_Layer2(i,2,0);
                    break;
                }
                else //on the second floor
                {
                    if(Layer2_BlockIsDone(i,2)) break; //restored, no action required
                    Layer2_To_Up(i);
                    i=-1; //restart the cycle
                }
            }
    }
    for(int i=0;i<20;i++)
    {
        if(!IsCornerBlock(i)) //a block of Rubik's Cube
            if(Block_Contain_Color(i,'R') && Block_Contain_Color(i,'B')) //red and blue block
            {
                if(block[i].ud_face==5) //there are only 8 block in total, which can be divided into the upper and second layers for discussion; the situation here is above
                {
                    if(cube[5][block[i].ud_pos]=='R')  Up_To_Layer2(i,3,1); //state 3
                    else Up_To_Layer2(i,3,0);
                    break;
                }
                else  //on the second layer
                {
                    if(Layer2_BlockIsDone(i,3)) break; //restored, no action required
                    Layer2_To_Up(i);
                    i=-1; //restart the cycle
                }
            }
    }
    for(int i=0;i<20;i++)
    {
        if(!IsCornerBlock(i)) //a block of Rubik's Cube
            if(Block_Contain_Color(i,'O') && Block_Contain_Color(i,'B'))  //blue and orage block
            {
                if(block[i].ud_face==5) //there are only 8 block in total, which can be divided into the upper and second layers for discussion; the situation here is above
                {
                    if(cube[5][block[i].ud_pos]=='O') Up_To_Layer2(i,4,0); //state 4
                    else Up_To_Layer2(i,4,1);
                    break;
                }
                else //on the second layer
                {
                    if(Layer2_BlockIsDone(i,4)) break; //restored, no action required
                    Layer2_To_Up(i);
                    i=-1;  //restart the cycle
                }
            }
    }
}
bool OLL_BlockIsDone()
{
    for(int i=1;i<=9;i++) if(cube[5][i]!='W') return false;
    return true;
}
int Up_Situation()
{
    if(cube[5][2]=='W' && cube[5][4]=='W' && cube[5][6]=='W' && cube[5][8]=='W') return 3; //cross
    if((cube[5][2]=='W' && cube[5][8]=='W') || (cube[5][4]=='W' && cube[5][6]=='W')) return 2;  //straight line
    if((cube[5][2]=='W' && cube[5][4]=='W') ||
       (cube[5][4]=='W' && cube[5][8]=='W') ||
       (cube[5][8]=='W' && cube[5][6]=='W') ||
       (cube[5][6]=='W' && cube[5][2]=='W')) return 1; //right angle
    return 0; //single center
}
int Up_Num_of_White() //count the number of top white blocks
{
    int sum=0;
    for(int i=1;i<=9;i++) if(cube[5][i]=='W') sum++;
    return sum;
}
void OLL_Formula(int i) //OLL formula, i is the number
{
    switch(i)
    {
        case 1:F();R();U();Ri();Ui();Fi();break;
        case 2:F();R();U();Ri();Ui();R();U();Ri();Ui();Fi();break; //it is equivalent to merging two case 1 and omitting the offsetting steps
        case 3:Ri();Ui();R();Ui();Ri();Ui();Ui();R();break;
        case 4:L();U();Li();U();L();U();U();Li();break;
        case 5:R();B();Ri();F();R();Bi();Ri();Fi();break;
        case 6:Fi();L();F();Ri();Fi();Li();F();R();break;
        case 7:R();R();D();Ri();U();U();R();Di();Ri();U();U();Ri();break;
    }
}
void OLL() //OLL
{
    if(OLL_BlockIsDone()) return; //determine if OLL has been completed
    //first judge the top surface structure cross / straight / right angle / single center
    switch(Up_Situation())
    {
        case 0:OLL_Formula(1);break;
        case 1:
        {
            if(cube[5][2]=='W')
            {
                if(cube[5][6]=='W') Ui();
            }
            else
            {
                if(cube[5][4]=='W') U();
                else {U();U();}
            }
            OLL_Formula(2);break;
        }
        case 2:
        {
            if(cube[5][2]=='W') U();
            OLL_Formula(1);break;
        }
        case 3:
        {
            switch(Up_Num_of_White())
            {
                case 5:OLL_Formula(3);break;
                case 6:
                {
                    int i=3;
                    if(cube[5][1]=='W')
                    {
                        if(cube[4][1]!='W') {U();i=4;} //else i=3; no need to write
                    }
                    else if(cube[5][3]=='W')
                    {
                        if(cube[3][3]!='W') Ui();
                        else i=4;
                    }
                    else if(cube[5][7]=='W')
                    {
                        if(cube[2][1]=='W') U();
                        else {U();U();i=4;}
                    }
                    else
                    {
                        if(cube[3][1]=='W') {U();U();}
                        else {Ui();i=4;}
                    }
                    OLL_Formula(i);
                    break;
                }
                case 7:
                {
                    if((cube[5][1]=='W' && cube[5][3]=='W'))
                    {
                        if(cube[4][1]=='W') OLL_Formula(5);
                        else OLL_Formula(7);
                    }
                    else if((cube[5][1]=='W' && cube[5][7]=='W'))
                    {
                        U();
                        if(cube[4][1]=='W') OLL_Formula(5);
                        else OLL_Formula(7);
                    }
                    else if((cube[5][9]=='W' && cube[5][3]=='W'))
                    {
                        Ui();
                        if(cube[4][1]=='W') OLL_Formula(5);
                        else OLL_Formula(7);
                    }
                    else if((cube[5][7]=='W' && cube[5][9]=='W'))
                    {
                        U();U();
                        if(cube[4][1]=='W') OLL_Formula(5);
                        else OLL_Formula(7);
                    }
                    else if((cube[5][3]=='W' && cube[5][7]=='W'))
                    {
                        if(cube[4][1]=='W') {U();U();OLL_Formula(6);}
                        else OLL_Formula(6);
                    }
                    else
                    {
                        if(cube[3][3]=='W') {Ui();OLL_Formula(6);}
                        else {U();OLL_Formula(6);}
                    }
                    break;
                }
            }break;
        }
    }
    OLL(); //recursion
}
bool PLL_BlockIsDone()
{
    char Order[5]="GBOR";
    for(int i=1;i<=4;i++)
        for(int j=1;j<=3;j++) if(cube[i][j]!=Order[i-1]) return false;
    return true;
}
int PLL_Situation(int type) //possible case of returning PLL may return 0/1/4 type2: possible case of returning PLL may return 0/1/4
{
    int sum=0;
    if(type==1)
    {
        for(int i=1;i<=4;i++) sum+=(cube[i][1]==cube[i][3]);
    }
    else
    {
        for(int i=1;i<=4;i++) sum+=(cube[i][2]==cube[i][1]);
    }
    return sum;
}
void PLL_Formula(int i) //PLL formula, i is the number
{
    switch(i)
    {
        case 1:R();R();F();F();Ri();Bi();R();F();F();Ri();B();Ri();break;
        case 2:R();Ui();R();U();R();U();R();Ui();Ri();Ui();Ri();Ri();break;
        case 3:R();R();U();R();U();Ri();Ui();Ri();Ui();Ri();U();Ri();break;
        case 4:R();R();Ui();Ui();Ri();U();U();Ri();Ri();Ui();Ui();R();R();Ui();Ui();Ri();U();U();Ri();Ri();break;
        case 5:U();Ri();Ui();R();Ui();R();U();R();Ui();Ri();U();R();U();R();R();Ui();Ri();U();break;
    }
}
void PLL() //PLL
{
    if(PLL_BlockIsDone()) return; // successfully accomplished !
    switch(PLL_Situation(1))
    {
        case 0:PLL_Formula(1);break;
        case 1:
        {
            if(cube[1][1]==cube[1][3]) Ui();
            else if(cube[2][1]==cube[2][3]) U();
            else if(cube[3][1]==cube[3][3]) {Ui();Ui();}
            PLL_Formula(1);
            break;
        }
        case 4:
        {
            switch(PLL_Situation(2))
            {
                case 0:
                {
                    if(cube[1][2]==cube[2][1]) PLL_Formula(4);
                    else PLL_Formula(5);
                    break;
                }
                case 1:
                {
                    if(cube[4][2]==cube[4][1])
                    {
                        Ui();
                        if(cube[1][2]==cube[4][1]) PLL_Formula(2);
                        else PLL_Formula(3);
                    }
                    else if(cube[1][2]==cube[1][1])
                    {
                        U();U();
                        if(cube[1][2]==cube[4][1]) PLL_Formula(2);
                        else PLL_Formula(3);
                    }
                    else if(cube[3][2]==cube[3][1])
                    {
                        U();
                        if(cube[1][2]==cube[4][1]) PLL_Formula(2);
                        else PLL_Formula(3);
                    }
                    else
                    {
                        if(cube[1][2]==cube[4][1]) PLL_Formula(2);
                        else PLL_Formula(3);
                    }
                    break;
                }
                case 4:
                {
                    switch(cube[1][2])
                    {
                        case 'G':break;
                        case 'O':U();break;
                        case 'R':Ui();break;
                        case 'B':U();U();break;
                    }
                    break;
                }
            }
        }
    }
    PLL(); //recursion
}

