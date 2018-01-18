## Dot_Mission1

> 문자를 입력받아서 도트로 출력하기

* 8x8font.h에 있는 배열과 매칭

```c
char input[100];
printf("input: ");
scanf("%s",&input);
int i=0,alpha=0;
while(input[i]!=NULL)
{
    alpha=0;
    if(input[i]>=97)
    {
        alpha=-6;
    }
    boardWriter(input[i]-'A'+alpha,0);
    i++;
}
```
## Dot_Mission2

> 위에서 받은 데이터 파일을 읽어  8x8 dot LED로 출력하기

```c++
//파일 읽기
FILE *fp=fopen("data","r+");
char **test=(char**)malloc(150*sizeof(char*));
int size=sizeof(*fp);

for(int i=0;i<12;i++){
    test[i]=(char*)malloc(size*sizeof(char));
    fgets(test[i],size,fp);
}

// 널문자로 colum의 개수 확인
 for(int j=0;j<150;j++){
        if(test[5][j]=='\n')
        {
            break;
        }
        col++;
 }

//잘 저장됬나 도트확인 (0~2까지는 보드 정보(?)가 있으므로 빼고 )
for(int i=3;i<12;i++)
{
        for(int j=0;j<col;j++)
        {
            printf("%c",test[i][j]);
        }
        printf("\n");
}

printf("col=%d\n",col);
    //   printf("%c",test[4][k]);

// o문자를 1로 바꾸기
uint8_t  mat[8][col];
for(int i=0;i<8;i++)
{
    for(int j=0;j<col;j++)
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
    for(int j=0;j<col;j++)
    {
        printf("%d ",mat[i][j]);
    }
    printf("\n");
}

```

### 결과 클릭

[![Video Label](http://img.youtube.com/vi/6Fwy64QgFuY/0.jpg)](https://youtu.be/6Fwy64QgFuY)
