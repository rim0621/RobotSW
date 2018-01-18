#include <stdio.h>
#include <pigpio.h>
#include<stdlib.h>
#include "74hc595_functions.h"
#include<unistd.h>
void dot(int row, int col)
{
    uint8_t row8, col8;
    uint16_t tmp;
    row8 = ~(1 << (8-row));
    col8 = 1 << (8-col);
    tmp = (row8<<8) | col8;
    set16(tmp);
}


int cnt;
void callback(void)
{
	printf("500 milliseconds have elapsed\n");
	cnt++;	
}
 
int main()
{
    int i,j;
    int total_col;
    FILE *fp=fopen("data","r+");
    char **test=(char**)malloc(16*sizeof(char*));
    int size=sizeof(*fp);
    //받아오기
    for(int i=0;i<12;i++){
        test[i]=(char*)malloc(size*sizeof(char));
        fgets(test[i],size,fp); 
    }
    
    //도트확인
    for(int i=3;i<11;i++)
    {
            for(int j=0;j<9;j++)
            {
                printf("%c",test[i][j]);
            }
            printf("\n");
    }

    //글자 개수구하기
    int last=9;
   
    
    
    printf("last=%d\n",last); 
        //   printf("%c",test[4][k]);

    //1로 바꾸기
    uint8_t  mat[8][9]; //배열을 크게 잡으면 이상한게 출력됬음 왜그럴까?
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<last;j++)
        {
            if(test[i+3][j]=='o'){
                mat[i][j]=1;
            }
            else
                mat[i][j]=0;
        }
    }
    //print
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<last;j++)
        {
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }

    total_col = sizeof(mat)/9;
    printf("total_col=%d\n",total_col);

    int ret;
    ret = init();
    if(ret == 0)
        return 0;

    gpioSetTimerFunc(0, 50, callback);

    while(1)
        for(i = 0 ; i < 8 ; i++)
            for(j = 0 ; j < last ; j++)
                if(mat[i][(j+cnt)%total_col] == 1)
                    dot(i+1,j+1);


    release();
    
    return 0;
}

