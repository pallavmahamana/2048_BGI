#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<stdlib.h>
#include<time.h>
#include<dos.h>
#include<string.h>
#include<math.h>

int z=0;
int score=0;
int tmp;
void showusertip(void)
{ char str[10];
settextstyle(1,0,1);
outtextxy(40,getmaxy()-60,"Use W S A D keys to move the tiles, <SPACE> to Quit." );
outtextxy(0,getmaxy()-40,"When two tiles with the same number touch, they merge into one!");
itoa(score,str,10);
tmp=score;
settextstyle(1,0,4);
outtextxy(getmaxx()-150,30,"SCORE");
settextstyle(9,0,4);
outtextxy(getmaxx()-120-15*(strlen(str)-1),80,str);
}

int mat[4][4]=             // seed matrix
 {0,0,0,0,
  0,0,0,0,
  0,0,0,0,
  0,0,0,0};

 int x1[4][4]=
 {30,120,210,300,
  30,120,210,300,                  // grid cordinates
  30,120,210,300,
  30,120,210,300};

  int y1[4][4]=
  {30,30,30,30,
  120,120,120,120,
  210,210,210,210,
  300,300,300,300};

  int x2[4][4]=
  {110,200,290,380,
  110,200,290,380,
  110,200,290,380,
  110,200,290,380};


  int y2[4][4]=
  {110,110,110,110,
  200,200,200,200,
  290,290,290,290,
  380,380,380,380};

void rendermat(int mat[][4])                 // seedmatrix rendering function
{ char str[4];
  z=0;
  for(int i=0;i<4;i++)
  for(int j=0;j<4;j++)
	{ if(mat[i][j])
	{z++;
	rectangle(x1[i][j],y1[i][j],x2[i][j],y2[i][j]);
	itoa(mat[i][j],str,10);
	int clr;
	for(clr=1;pow(2,clr)<=mat[i][j];clr++){}
	if(clr>=15) {clr=clr%15;clr+=3;}
	setfillstyle(1,clr);
	floodfill(x1[i][j]+15,y1[i][j]+15,15);
	settextstyle(8,0,6-strlen(str));
	outtextxy(x1[i][j]+10*(4-strlen(str)),y1[i][j]+strlen(str)*8,str);}
	rectangle(15,15,395,395);
	}
	showusertip();
}
void rendermatnotip(int mat[][4])
{
  char str[4];
  z=0;
  for(int i=0;i<4;i++)
  for(int j=0;j<4;j++)
	{ if(mat[i][j])
	{z++;
	rectangle(x1[i][j],y1[i][j],x2[i][j],y2[i][j]);
	itoa(mat[i][j],str,10);
	settextstyle(8,0,6-strlen(str));
	outtextxy(x1[i][j]+10*(4-strlen(str)),y1[i][j]+strlen(str)*8,str);}
	rectangle(15,15,395,395);
	}
}

void pullrandom(int a[][4])
{
int l = rand()%4;int m = rand()%4;
while(a[l][m])
{l=rand()%4;m=rand()%4;
}
a[l][m] = (rand() % 2 + 1) * 2;
char str[4];
delay(150);
  rendermat(mat);
  rectangle(x1[l][m],y1[l][m],x2[l][m],y2[l][m]);
  itoa(a[l][m],str,10);
  settextstyle(8,0,6-strlen(str));
  outtextxy(x1[l][m]+10*(4-strlen(str)),y1[l][m]+strlen(str)*8,str);
  rectangle(15,15,395,395);

}


int upmat(int a[][4])
{ int check=0;
 for(int j=0;j<4;j++)
 {
 int l=0,b[4]={0,0,0,0};
  for(int i=0;i<4;i++)
  {
   if(a[i][j]!=0){b[l]=a[i][j];l++;}
  }
  for(i=0;i<4;i++)
  if(b[i]!=a[i][j]) {check=1;}

  for(i=0;i<3;i++)
  if(b[i]==b[i+1] && b[i]!=0 && b[i+1]!=0) {b[i]=2*b[i];score=score+b[i];b[i+1]=0;check=1;}
	  l=0;
  a[0][j]=0;a[1][j]=0;a[2][j]=0;a[3][j]=0;
  for(i=0;i<4;i++)
  {
  if(b[i]!=0) {a[l][j]=b[i];l++;}
  }
 }
return check;
}


int downmat(int a[][4])

{  int check=0;
for(int j=0;j<4;j++)
{
	int l=3;int b[4]={0,0,0,0};
	for(int i=3;i>=0;i--)
	{
	if(a[i][j]!=0) {b[l]=a[i][j];l--;}
	}

	 for(i=3;i>=0;i--)
  if(b[i]!=a[i][j]) {check=1;}

	for(i=3;i>=0;i--)
	 if(b[i]==b[i-1] && b[i]!=0 && b[i-1]!=0) {b[i]=2*b[i];score=score+b[i];b[i-1]=0;check=1;}

	l=3;
	a[0][j]=0;a[1][j]=0;a[2][j]=0;a[3][j]=0;
	for(i=3;i>=0;i--)
	{
		if(b[i]!=0){a[l][j]=b[i];l--;}
	}

	}
 return check;
}

int leftmat(int a[][4])
{  int check=0;
    for(int j=0;j<4;j++)
 {
 int l=0,b[4]={0,0,0,0};
  for(int i=0;i<4;i++)
  {
   if(a[j][i]!=0){b[l]=a[j][i];l++;}
  }

   for(i=0;i<4;i++)
  if(b[i]!=a[j][i]) {check=1;}

  for(i=0;i<3;i++)
  if(b[i]==b[i+1] && b[i]!=0 && b[i+1]!=0) {b[i]=2*b[i];score=score+b[i];b[i+1]=0;check=1;}
	  l=0;
  a[j][0]=0;a[j][1]=0;a[j][2]=0;a[j][3]=0;
  for(i=0;i<4;i++)
  {
  if(b[i]!=0) {a[j][l]=b[i];l++;}
  }
 }
  return check;
}


int rightmat(int a[][4])
{ int check=0;
for(int j=0;j<4;j++)
{
	int l=3;int b[4]={0,0,0,0};
	for(int i=3;i>=0;i--)
	{
	if(a[j][i]!=0) {b[l]=a[j][i];l--;}
	}

	for(i=3;i>=0;i--)
    if(b[i]!=a[j][i]) {check=1;}

	for(i=3;i>=0;i--)
	if(b[i]==b[i-1] && b[i]!=0 && b[i-1]!=0) {b[i]=2*b[i];score=score+b[i];b[i-1]=0;check=1;}
	l=3;
	a[j][0]=0;a[j][1]=0;a[j][2]=0;a[j][3]=0;
	for(i=3;i>=0;i--)
	{
		if(b[i]!=0){a[j][l]=b[i];l--;}
	}
	}
  return check;
}


int checkgameover(int a[][4])
{
int c=1;
int m[4][4];
for(int i=0;i<4;i++)
for(int j=0;j<4;j++)
m[i][j]=a[i][j];

leftmat(m);

int r=0;
for(i=0;i<4;i++)
for(j=0;j<4;j++)
{ if(m[i][j]) r++;}

if(r<16) c=0;

for(i=0;i<4;i++)
for(j=0;j<4;j++)
m[i][j]=a[i][j];

rightmat(m);

r=0;
for(i=0;i<4;i++)
for(j=0;j<4;j++)
{ if(m[i][j]) r++;}

if(r<16) c=0;

for(i=0;i<4;i++)
for(j=0;j<4;j++)
m[i][j]=a[i][j];

upmat(m);

r=0;
for(i=0;i<4;i++)
for(j=0;j<4;j++)
{ if(m[i][j]) r++;}

if(r<16) c=0;

for(i=0;i<4;i++)
for(j=0;j<4;j++)
m[i][j]=a[i][j];

downmat(m);

r=0;
for(i=0;i<4;i++)
for(j=0;j<4;j++)
{ if(m[i][j]) r++;}

if(r<16) c=0;

return c;
}






void main()
{
time_t t;

int gdriver = DETECT, gmode, errorcode;
initgraph(&gdriver, &gmode, "");
errorcode = graphresult();
if (errorcode != grOk)
{
   printf("Graphics error: %s\n", grapherrormsg(errorcode));
   printf("Press any key to halt:");
   getch();
   exit(1);
}
cleardevice();
srand((unsigned) time(&t));
int l,m,i,j,u;
l = rand()%4; m = rand()%4;
mat[l][m] = (rand() % 2 + 1) * 2;
l = rand()%4; m = rand()%4;
if(mat[l][m])
{ l = rand() % 4; m = rand() % 4; }
mat[l][m] = (rand() % 2 + 1) * 2;

char str[4];
rendermat(mat);
char ch;
ch=getch();
while(ch!=32)
{
inp:
if(ch=='w')
{int v;
sound(rand()%2000+15);delay(100);nosound();
v=upmat(mat);
cleardevice();
rendermat(mat);
delay(150);

if(z==16 && checkgameover(mat)==1) goto kaboom;

if(z<16 && v==1) {pullrandom(mat); }
}
if(ch=='a')
{ int v;
sound(rand()%2000+15);delay(100);nosound();
v=leftmat(mat);
cleardevice();
rendermat(mat);
delay(150);

if(z==16 && checkgameover(mat)==1) goto kaboom;

if(z<16 && v==1) {pullrandom(mat);}
}
if(ch=='d')
{ int v;
sound(rand()%2000+15);
delay(100);
nosound();
v=rightmat(mat);
cleardevice();
rendermat(mat);
delay(150);

if(z==16 && checkgameover(mat)==1) goto kaboom;

if(z<16 && v==1) {pullrandom(mat);}
}
if(ch=='s')
{int v;
sound(rand()%2000+15);
delay(100);
nosound();
v=downmat(mat);
cleardevice();
rendermat(mat);
delay(150);

if(z==16 && checkgameover(mat)==1) goto kaboom;

if(z<16 && v==1) {pullrandom(mat);}
}
ch=getch();
}
cleardevice();
rendermatnotip(mat);
settextstyle(3,0,3);
setcolor(RED);
outtextxy(100,getmaxy()-60,"!!! Press <SPACE> to Exit !!!");
delay(500);
setcolor(YELLOW);
outtextxy(100,getmaxy()-60,"!!! Press <SPACE> to Exit !!!");
goto puddle;
kaboom:
cleardevice();
itoa(tmp,str,10);
rendermatnotip(mat);
settextstyle(7,0,5);
outtextxy(100,425,"!!! GAME OVER !!!");
for(i=0;i<18;i++)
{sound(rand()%2000+15);
settextstyle(1,0,4);
outtextxy(getmaxx()-150,30,"SCORE");
setcolor(i/3*3);
settextstyle(9,0,4);
outtextxy(getmaxx()-120-15*(strlen(str)-1),80,str);
delay(rand()%200+100);
nosound();}
puddle:
getch();
}