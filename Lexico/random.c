#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define DICLEN 300
#define INORDER 1
#define RANDOM 0
typedef struct dic
{
    char* espa;
    char* chin;
    double train;
    double hit;
    int num;
}RecordNode;

int glnum;
RecordNode* List[DICLEN];
void InitPointer(char* pointer,size_t size)
{
    if(pointer)
    memset(pointer,0,size);
    else{
        printf("null pointer \n");
        exit(0);
    }
}
int GetPosi(char* src)
{
    size_t len = strlen(src);
    int res = 0;
    for(int i=0;i<len;i++)
    {
        if(src[i]>='a'&&src[i]<='z')
        res =i;
    }
    return res;
}
void split(char* src, char* fir, char* sec)
{
    int p = GetPosi(src);
    p++;
    if((*src)==' '){
        src++;
        p--;
    }
    strncpy(fir,src,p);

    if(*(src+p)==' ') p++;
    strcpy(sec,src+p);
}
void lower(char* src)
{
    size_t len = strlen(src);
    for(int i=0;i<len;i++)
    {
        if(src[i]>='A'&&src[i]<='Z')
        src[i]+=32;
    }
}
RecordNode* CrtDic(char* es,char* ch)
{

    RecordNode* D = (RecordNode*)malloc(sizeof(RecordNode));
    if(D) memset(D,0,sizeof(RecordNode));
    else 
    {
        printf("unable to malloc for a new record\n");
        exit(0);
    }
    D->chin = (char*)malloc(strlen(ch)+1);
    D->espa = (char*)malloc(strlen(es)+1);
    InitPointer(D->chin,strlen(ch)+1);
    InitPointer(D->espa,strlen(es)+1);
    /*flag strcpy is wrong and can cause unable to malloc for a new record */
    strncpy(D->chin,ch,strlen(ch)+1);
    strncpy(D->espa,es,strlen(es)+1);
    printf("%s END\n",D->espa);
    lower(D->espa);
    D->num = glnum;
    D->train=0;
    D->hit=0;
    glnum++;
    return D;
}
void Train(int wordnum)
{
    int r0=0;
    char* input =(char*)malloc(50);
    double acc=0;
    InitPointer(input,50);
    for(int i=0;i<wordnum;i++)
    {
        r0 = rand()%glnum;
        printf("%s",List[r0]->chin);
        fgets(input,50,stdin);
        if(!strncmp(input,List[r0]->espa,strlen(input))) {
            List[r0]->hit++;
            acc++;
            printf("CORRET\n");
        }
        else{
            printf("WRONG, ANSWER IS :%s E\n",List[r0]->espa);
        }
        List[r0]->train++;
        if((i+1)%10==0) 
        {
            printf("**************************\n");
            printf("you have complete (%d\\%d),your current accuracy is %.2lf%c\n",i,wordnum,100*(acc/wordnum),'%');
            printf("**************************\n");
        }
        InitPointer(input,50);
    }
    printf("You have complete this round of training, your accuracy is: %.2lf%c\n",100*(acc/wordnum),'%');
    free(input);
}
void Record()
{
    FILE* out = fopen("out.txt","w+");
    if(!out) {printf("wrong\n");exit(0);}
    for(int i=0;i<glnum-1;i++)
    {
        fprintf(out,"%s %s  %lf %lf",List[i]->espa,List[i]->chin,List[i]->train,List[i]->hit);
    }
    fclose(out);
}
void Order()
{
    char* input =(char*)malloc(50);
    double acc=0;
    InitPointer(input,50);
    for(int r0=0;r0<glnum;r0++)
    {
        printf("%s",List[r0]->chin);
        fgets(input,50,stdin);
        //printf("intput: %s \n",input);
        if(!strncmp(input,List[r0]->espa,strlen(input)-1)) {
            List[r0]->hit++;
            acc++;
            printf("CORRET\n");
        }
        else{
            printf("WRONG, ANSWER IS :%s\n",List[r0]->espa);
        }
        List[r0]->train++;
        if((r0+1)%10==0) 
        {
            printf("**************************\n");
            printf("you have complete (%d\\%d),your current accuracy is %.2lf%c\n",r0,glnum,100*(acc/glnum),'%');
            printf("**************************\n");
        }
    }
    printf("You have complete this round of training, your accuracy is: %.2lf%c\n",100*(acc/glnum),'%');
    free(input);
}
int main()
{
    char* buffer = (char*)malloc(100);
    char* es = (char*)malloc(50);
    char* ch = (char*)malloc(50);
    InitPointer(buffer,100);
    InitPointer(es,50);
    InitPointer(ch,50);


    SetConsoleOutputCP(65001);
    srand(time(0));
    FILE* fp = fopen("1.txt","r");
    while(fgets(buffer,100,fp))
    {
        //printf("%s",buffer);
        split(buffer,es,ch);
        RecordNode* record = CrtDic(es,ch);
        List[glnum-1] = record;
        InitPointer(buffer,100);
        InitPointer(es,50);
        InitPointer(ch,50);
        //break;
    }
    fclose(fp);
    printf("\n");
    int mode;
    printf("Enter 1 for order ; 0 for random:\n");
    scanf("%d",&mode);
    getchar();
    switch (mode)
    {
    case INORDER:
        Order();
        break;
    case RANDOM:
        printf("input train word num\n");
        int n;
        scanf("%d",&n);
        Train(n);
        break;
    default:
        break;
    }
    
    Record();
    for(int i=0;i<glnum;i++)
    {
        //printf("%s %s\n",List[i]->espa,List[i]->chin);
        free(List[i]->chin);
        free(List[i]->espa);
    }
    free(buffer);
    free(es);
    free(ch);
}