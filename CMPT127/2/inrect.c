#include <stdio.h>

int InRectangle( float pt[2], float rect[4] )
{
    float leftdown[2],rightup[2];
    if (rect[0]>rect[2]){
        leftdown[0]=rect[2];
        rightup[0]=rect[0];
    }else {
        leftdown[0]=rect[0];
        rightup[0]=rect[2];
    }
    if(rect[1]>rect[3]){
        leftdown[1]=rect[3];
        rightup[1]=rect[1];
    }else{
        leftdown[1]=rect[1];
        rightup[1]=rect[3];
    }
    if(pt[0]>rightup[0] | pt[0]<leftdown[0] | pt[1]>rightup[1] | pt[1]<leftdown[1]){
        return 0;
    }else{
        return 1;
    }
}
