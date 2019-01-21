#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#define N 20
#define M 35
struct snake
{
  int sx,sy;
  char sval;
  struct snake *next;
};
struct snake *head=NULL;
struct food
{
  int fx,fy;
  char fval;
};
struct pos
{
  int px,py;
  char pval;
};
void gotoxy(int x, int y)
{
COORD coord;
coord.X = x;
coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void inmat(char mat[N][M])//SENDING lINK LIST IN MATRIX
{
  struct snake *t;
  t=head;
  while(t->next!=NULL)
  {
    mat[t->sx][t->sy]=t->sval;
    t=t->next;
  }
    mat[t->sx][t->sy]=' ';
};
void display(char mat[N][M])//DISPLAYING MATRIX
{
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<M;j++)
      {
        printf("%c ",mat[i][j]);
      }
      printf("\n");
  }
}
void board(char mat[N][M])//MAKING BOARD
{
  for(int i=0;i<N;i++)//for making empty space between boundaries
  {
    for(int j=0;j<M;j++)
      {
        mat[i][j]=' ';
      }
  }
//for making boundaries
  for(int j=0;j<M;j++)
  {
    mat[0][j]='-';
  }
  for(int j=0;j<N;j++)
  {
    mat[j][M-1]='|';
  }
  for(int j=0;j<N;j++)
  {
    mat[j][M]='|';
  }
  for(int j=0;j<M;j++)
  {
    mat[N-1][j]='-';
  }

}
  struct snake* create(int r,int c,char val)//CREATING NEW NODES FOR LINKED LIST
  {
    struct snake *ptr;
    ptr=(struct snake*)malloc(sizeof(struct snake));
    ptr->sx=r;
    ptr->sy=c;
    ptr->sval=val;
    ptr->next=NULL;
    return ptr;
  }
void insert(int r,int c,char val)//APPENDING IN LINKED LIST
{
  struct snake *temp=create(r,c,val);
  struct snake *t=head;
  if(head==NULL)
  {
    head=temp;
  }
  else
  {
    temp->next=head;
    t->sval='#';
    head=temp;
  }
}
void del()//DELETING LAST ELEMENT
{
  struct snake *temp=head;
 struct snake *t;
 while(temp->next!= NULL)
 {
   t=temp;
   temp=temp->next;
 }
 free(t->next);
 t->next=NULL;
}
int check(int r,int c)
{
  struct snake *temp=head;
  while(temp->next!=NULL)
  {
  //  sleep(1);
    if(temp->sx==r && temp->sy==c)
    {
      return 1;
      break;
    }
    temp=temp->next;
  }
  return 0;
}
int main()
{
char mat[N][M],command,ch,val[100][100];
static int score=0;
int a=10,b=23,choice,n=0,i,flag=0,k=0,aa,bb,gameover=0;
board(mat);
printf("\t\t\t\t\tWelcome to nagraj\n");
printf("Do you want to resume previous game or start a new one?:\n1.Resume\n2.New game");
scanf("%d",&choice);
if(choice==1)//FOR RESUMING GAME
{
  FILE *fp;
  fp=fopen("save.txt","r");
  ch=fgetc(fp);
  rewind(fp);
  while((ch=fgetc(fp))!=EOF)
  {
    if(ch!='$'&& ch!='-')
    {
      val[n][k++]=ch;
      flag=0;
    }
    else
    {
      val[n][k++]='\0';
    //  printf("%c",ch);
      if(flag==0)
      {
        n++;
        flag=1;
      }
      k=0;
    }
  }
int num1=0,num2=1,num3=2,num4=3;
int aa,bb,dd;
char *s;
a=atoi(val[num1]);
b=atoi(val[num2]);
for(i=0;i<(n/4);i++)
{
  score=atoi(val[num4]);
  s=val[num3];
  //printf(" %d %d %c",a,b,*s);
  insert(atoi(val[num1]),atoi(val[num2]),*s);
  num1=num1+4;
  num2=num2+4;
  num3=num3+4;
  num4=num4+4;
}
}
else//FOR NEW GAME
{
  insert(10,20,'T');
  insert(10,21,'#');
  insert(10,22,'#');
  insert(10,23,'H');
  score=0;
}
inmat(mat);
int r,c;
r=rand()%20;//POS FOR FOOD
c=rand()%30;//POS FOR FOOD
mat[r][c]='@';
int posr,posc;
posr=rand()%10;//POS FOR POISON
posc=rand()%15;//POS FOR POSON
mat[posr][posc]='P';
  struct snake *t=head;
while(1)
  {
    if(a==r&&b==c)
    {
      insert(a,b,'#');
      Beep(750,300);//FOR BEEP SOUND ON EATING FOOD AND POS
    score++;
      r=rand()%20;
      c=rand()%30;
      mat[r][c]='@';
    }
    if(a==posr&&b==posc)
    {
      struct snake *t;
      t=head;
    //  mat[1][1]=head->sval;
      while(t->next!=NULL)
      {
        t=t->next;
      }
      mat[t->sx][t->sy]=' ';
        del();
      Beep(750,300);
      score--;
      posr=rand()%10;
      posc=rand()%15;
      mat[posr][posc]='P';
    }
    printf("X:%d Y:%d SCORE:%d\n",a,b,score);
    display(mat);
    printf("Enter command & X to save and exit:");
  // sleep(1);
    if(kbhit())
    {
        command=getch();
    }
     putchar(command);
     if(command=='x' && gameover==0)
     {
       FILE *out_file=fopen("save.txt","w");
       if(out_file==NULL)
       {
         printf("Sorry can't save your game!");
       }
       else
       {
          struct snake *s=head;
         while(s->next!=NULL)
         {
           fprintf(out_file,"%d-%d-%c-%d$",s->sx,s->sy,s->sval,score);
           s=s->next;
         }

       }
       fclose(out_file);
       break;
     }
     else if(command=='x' && gameover==1)
     {
      FILE *out_file=fopen("save.txt","w");
      break;
     }
     switch (command)
     {
     case 'a':
      b=b-1;
      if(check(a,b))
      {
        sleep(1);
        printf("GAME OVER");
        sleep(1);
        command='x';
        gameover=1;
        flag=1;
        break;
        break;
      }
      if(b==1)
      {
        b=34;
      }
      insert(a,b,'H');
      inmat(mat);
     del();
     break;
     case 'd':
     b=b+1;
           if(check(a,b))
           {
             sleep(1);
             printf("GAME OVER");
             gameover=1;
            sleep(1);
              command='x';
                break;
               break;
           }
     if(b==34)
     {
       b=1;
     }
     insert(a,b,'H');
      inmat(mat);
     del();
     break;
     case 's':
     a=a+1;
             if(check(a,b))
             {
               sleep(1);
               printf("GAME OVER");
                sleep(1);
                gameover=1;

                command='x';
                break;
               break;
             }
     if(a==20)
     {
       a=1;
     }
     insert(a,b,'H');
     inmat(mat);
    del();
     break;
     case 'w':

     a=a-1;
     if(check(a,b))
     {
       sleep(1);
       printf("GAME OVER");
       gameover=1;

       sleep(1);
      command='x';
       break;
       break;
     }
     if(a==0)
     {
       a=20;
     }
      insert(a,b,'H');
      inmat(mat);
     del();
     break;
   }
   system("cls");
  }
}
