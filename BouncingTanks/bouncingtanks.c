#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
int docount;
int get2c(){
	char c;
	static int d;
	c=getch();
	fflush(stdin);
	d=c;
	return 256+d;
}
int arrowonly(){long int a=(get2c());
    if(a==224)
	a=(a)*1000+(get2c()-256);
	else a=a-256;

	return 0;

}
int arrow(){long int a=(get2c());
    if(a==224)
	a=(a)*1000+(get2c()-256);
	else a=a-256;

	return a;

}void hidecursor(){
	CONSOLE_CURSOR_INFO info;
	info.dwSize=100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
void gotoxy(int col,int row)
{
	COORD position ={row,col};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),position);	}
	

void delay1(int a){
	int i,j;
	for(i=0;i<a;i++){
		for(j=0;j<a;j++){
			i-j;	}}}	
void cursor(){
    CONSOLE_FONT_INFOEX console_info  ;
    console_info.cbSize = sizeof(console_info);
	console_info.dwFontSize.X = 10;
	console_info.dwFontSize.Y= 24;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),FALSE,  &console_info);
	CONSOLE_CURSOR_INFO info;
	info.dwSize=100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);}
int health=1;
int c=0,score=0,bullets=0;int a[500][2];
int flag,bul=15,speed1=1000,speed2=500;
void bounce();
int  pause(){int j;gotoxy(26,45);printf("      P A U S E D");
            gotoxy(27,45);printf("Press SPACE BAR to resume.");
	       pause:
			for(j=0;j<20000;j++){ 
			j=j;
			if(kbhit())
			{int a=arrow();
			if(a==27)mainmenu();
			if(a==32){
			gotoxy(26,45);printf("                        ");gotoxy(27,45);printf("                          ");break;}}
			goto pause;}
	
}
 int  printsc(int y)
{	 int x=3;
if(flag==1)goto a;else goto b;
   a: while(y>30){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),280);
    	gotoxy(y,x);
    	printf("/"	);
    	y--;x++;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    	if(x==120)return 0;
    	if(y<=30)break;}
  b:while(y<40){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),280);
    	gotoxy(y,x);
    	printf("\\");
    	y++;x++;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    	if(x==120)return 0;
	   if(y>=40)goto a;}	

	
}
void lose(int i,int j){gotoxy(i,j);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	printf("00000      0      0     0  00000       0000  0       0 00000 0000\a");gotoxy(i+1,j);
	printf("0         0 0     00   00  0          0    0  0     0  0     0   0");gotoxy(i+2,j);
	printf("0  000   00000    0 0 0 0  0000       0    0   0   0   0000  0000");gotoxy(i+3,j);
	printf("0   0   0     0   0  0  0  0          0    0    0 0    0     0   0");gotoxy(i+4,j);
	printf("00000  0       0  0     0  00000       0000      0     00000 0    0");gotoxy(i+7,j);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	printf("                   Y O U R      S C O R E  :  %02d",score);
	FILE *fp;int s,hs;
		s=score;
		fp=fopen("highscorebt.dat","r");
       fscanf(fp,"%d",&hs);
       fclose(fp);
       if(score==hs){gotoxy(i+8,j);delay1(10000);printf("                        PERSONAL  BEST  !!!   ");
	   }
}
int erasesc(int y)
{   	 int c=0,x=3;
if(flag==1)goto a;else goto b;
   a: while(y>30){
    	gotoxy(y,x);
    	printf(" "	);
    	y--;x++;
    	if(x==120)return 0;
    	if(y<=30)break;}
  b:while(y<40){
    	gotoxy(y,x);
    	printf(" ");
    	y++;x++;
    	if(x==120)return 0;
	   if(y>=40)goto a;}	

}

void printtank(int i,int j)
{   int t;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),228);
    gotoxy(18,9);printf("Press Esc key to go to main menu");
    gotoxy(18,89);printf("Press SPACE bar to pause");SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	for(t=0;t<120;t++){
		gotoxy(43,t);printf("%c",254);
	}SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    gotoxy(20,50);
    printf("BOUNCING TANKS");
	gotoxy(21,10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    gotoxy(i-1,j+5);
	printf("__"); 
	gotoxy(i,j+4);
	printf("/__");
	
	gotoxy(i+1,j+1);
	printf("__  __");gotoxy(i+1,j+3);printf("//");
	gotoxy(i+2,j);
	printf("(______)");SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);}
   
void erasetank(int i,int j)
{   gotoxy(i-1,j);
	printf("       "); 
	gotoxy(i,j);
	printf("       ");
	gotoxy(i+1,j);
	printf("       ");
	gotoxy(i+2,j);
	printf("        ");}


int foepos=116;
int continueflag=2;	
void shootprevious()
	{int i;static int r=35;
		FILE *fp;int s,hs;
		s=score;
		fp=fopen("highscorebt.dat","r");
       fscanf(fp,"%d",&hs);
       fclose(fp);
	gotoxy(r,foepos+2);printf("   ");SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);gotoxy(r,foepos);printf("<%c%c",254,254);foepos--;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	for(i=c;i>0;i--){if(a[i][1]!=118){gotoxy(a[i][0],a[i][1]);printf(" ");gotoxy(a[i][0],a[i][1]+1);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);printf("%c",254);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);if(((a[i][0]==r)&&(a[i][1]==foepos)))
	{srand(time(NULL)+getpid());r=(rand()%10)+30;foepos=116;gotoxy(a[i][0],a[i][1]+1);score++;printf("    ");
		FILE *fp;
		s=score;
		fp=fopen("highscorebt.dat","r");
       fscanf(fp,"%d",&hs);
       fclose(fp);
       if(s>hs)
      {
      fp=fopen("highscorebt.dat","w");
	  fprintf(fp,"%d",s);hs=s;fclose(fp);}
	  bullets--;a[i][1]=117;}a[i][1]=a[i][1]+1;if(((a[i][0]==r)&&(a[i][1]==foepos)))
	{srand(time(NULL)+getpid());r=(rand()%9)+31;foepos=116;gotoxy(a[i][0],a[i][1]);score++;printf("    ");
			FILE *fp;int s,hs;
		s=score;
		fp=fopen("highscorebt.dat","r");
       fscanf(fp,"%d",&hs);
       fclose(fp);
       if(s>hs)
      {
      fp=fopen("highscorebt.dat","w");
	  fprintf(fp,"%d",s);hs=s;fclose(fp);}bullets--;a[i][1]=118;}}}
	if(foepos==6){
		health--;foepos=116;{srand(time(NULL)+getpid());r=(rand()%9)+31;}
	}int k;
  gotoxy(20,100);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("HEALTH");if(health>3)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
	for(k=0;k<health;k++){gotoxy(21,98+k);printf("%c          ",254);}SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	gotoxy(23,98);
	printf("  BEST:%02d",hs);
	gotoxy(24,54);
	printf("SCORE");
	gotoxy(25,56);printf("%d",score);
	gotoxy(20,10);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
	printf("BULLETS");SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
	for(k=0;k<bul-bullets;k++){gotoxy(21,10+k);printf("%c          ",254);}if(bullets==bul){gotoxy(21,10);printf(" ",1);}SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
     if(health==0){gotoxy(21,98);printf(" ");lose(22,25);delay1(20000);delay1(20000);delay1(20000);delay1(20000);continueflag=2;mainmenu();}
	if(docount==1)
	{gotoxy(27,54);printf("READY ");
	 delay1(20000);	
	 gotoxy(27,54);printf("STEADY");	
	 delay1(20000);	
	 gotoxy(27,53);printf("  GO   ");
	 delay1(20000);
	 gotoxy(27,53);printf("       ");
	 docount=0;
	}
	
	
	
	
	if(bullets<bul)
	delay1(speed1);
	
	bounce();	}

void shoot(int y,int x)
{   
    a[c][0]=y;a[c][1]=x;shootprevious();}

	
		
	void bounce()	
	{static int x=3,y=40,v,i=0,j=0,w=30;int b;
	
      printtank(y,x);

	 
     if(j==0)    	 
	while(y>30)
		{up:
		{if(y!=1)
		 {erasetank(y,x);erasesc(w);
		 y=y-1; }if(y==30)j=1;
		 if(w==40)flag=1;
	 	if(w==30)
		flag=0;	 
		if(flag==1)w--;
	 	if(flag==0)w++;
	 	printsc(w);
		 printtank(y,x);
         
		 if(kbhit())
         b=arrow();
         if(b==27)mainmenu();
		  if(b==' ')pause();
		 if(b==13)goto shoot;
		 }shootprevious();}
	    	 

	if(j==1) 
	while(y<40)
		{down:
		{if(y!=300)
		 {erasetank(y,x);erasesc(w);
		 if(w==40)flag=1;
	 	if(w==30)
		flag=0;
		 if(flag==1)w--;
	 	if(flag==0)w++;
		 y=y+1;}if(y==40)j=0;
		printsc(w); printtank(y,x);
		 	 
		
         
		 if(kbhit())
         b=arrow();
		  if(b==27)mainmenu();if(b==' ')pause();
		 if(b==13)goto shoot;}shootprevious();}
	
		
	
		{shoot:
		{if(bullets<bul){bullets++;c++;}else shootprevious();shoot(y,x+7);}}

}	
int getkey(){
	long int a=arrow();
	if(a==13) return 5;
	if(a==224072) return 1;
	if(a==224080) return 2;
		else if(a==224075){return 3;}
	else if(a==224077){return 4;}

	return a;
}
int mainmenu(){int y=continueflag;int v;system("cls");
    gotoxy(18,22);
	printf(" ___________________");
    gotoxy(19,22);printf("| M A I N - M E N U |");
    gotoxy(20,22);
	printf("|___________________|");gotoxy(21,22);printf("|  |                |");
    if(continueflag==1)	{
	gotoxy(21,26);printf("Continue");}
	
	gotoxy(22,22);printf("|  |New Game        |");
	gotoxy(23,22);printf("|  |Level           |");
	gotoxy(24,22);printf("|  |Instructions    |");
	gotoxy(25,22);printf("|  |High Score      |");
	gotoxy(26,22);printf("|  |Exit            |");
	gotoxy(27,22);
	printf("|__|________________|");gotoxy(40,0);
	{gotoxy(20+continueflag,23);printf("->");}

		wait:		 if(kbhit){
		 	int v=getkey();
		 	if(v==1)goto up;
		 	if(v==2)goto down;
            if(v==27)goto exit;
			if(v==5)goto enter;
			  goto wait;}
	up:
		{gotoxy(20+y,23);printf("  ");
		if(y!=continueflag)
		 y=y-1;

		 gotoxy(20+y,23);printf("->");
		 
		    goto wait;
		}
		
	
	
	down:
		{gotoxy(20+y,23);printf("  ");
		if(y!=6)
		 y=y+1;

		 gotoxy(20+y,23);printf("->");

		    goto wait;
		}
    
    enter:
    	if(y==1)
    	{docount=1;system("cls");bounce();}

    	if(y==2)
    	{system("cls");docount=1;
    	
		 health=10;
          c=0;score=0;bullets=0;foepos=116;continueflag=1;bounce();}
    	if(y==3)
    	{
    		
		  system("cls");gotoxy(12,4);printf("     Press Esc key to go to main menu ");gotoxy(40,0);
            int h;static lev=3;int levprev=lev;
			for(h=0;h<3*lev;h=h+3)
			{if(lev==1)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),5);
			if(lev==2)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
			if(lev==3)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),1);
			if(lev==4)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
			if(lev==5)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
			gotoxy(20,25+h);printf("%c%c%c     ",254,254,254);}gotoxy(20,20+3*lev);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
			gotoxy(20,20);printf("|");gotoxy(20,45);printf("|");
		  level:
		 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		
		 	if(lev==5){bul=8;speed1=1;gotoxy(18,20);       printf("|LEVEL:     Insane       |"); }
		 	if(lev==0){bul=20;speed1=10000;gotoxy(18,20);printf("|LEVEL:     Novice       |");}
		 	if(lev==1){bul=18;speed1=5000;gotoxy(18,20);printf("|LEVEL:     Very Easy    |"); }
		 	if(lev==2){bul=15;speed1=1000;gotoxy(18,20); printf("|LEVEL:     Easy         |"); }
		 	if(lev==3){bul=12;speed1=40;gotoxy(18,20); printf("|LEVEL:     Moderate     |"); }
		 	if(lev==4){bul=10;speed1=20;gotoxy(18,20); printf("|LEVEL:     Hard         |"); }
		 	gotoxy(17,20);printf(" ________________________");gotoxy(19,20);printf("|________________________|");gotoxy(21,20);printf("|________________________|");
			 if(kbhit)
		 	v=getkey();
		 	if(v==3){if(lev!=0)lev--;
		 	if(lev==1)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),5);
			if(lev==2)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
			if(lev==3)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),1);
			if(lev==4)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
			if(lev==5)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
			for(h=0;h<3*lev;h=h+3){gotoxy(20,25+h);printf("%c%c%c     ",254,254,254);}
			 {gotoxy(20,25+3*lev);printf("   ");}}
		 	if(v==4){if(lev!=5)lev++;
			 if(lev==1)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),5);
			if(lev==2)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
			if(lev==3)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),1);
			if(lev==4)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
			if(lev==5)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);;for(h=0;h<3*lev;h=h+3){gotoxy(20,25+h);printf("%c%c%c     ",254,254,254);}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);gotoxy(20,20);printf("|");gotoxy(20,45);printf("|");}
			if(v==27){if(lev!=levprev)continueflag=2;SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);mainmenu();} goto level;}
    	if(y==4)
    	{system("cls");gotoxy(12,4);printf("     Press Esc key to go to main menu ");gotoxy(40,0);
 		gotoxy(18,20);
		printf("                                  INSTRUCTIONS");   	
		gotoxy(19,20);
		printf(" _____________________________________________________________________________________");
		gotoxy(20,20);
		printf("| The object of the game is to shoot all enemy missiles before they enter your range. |");
		gotoxy(21,20);
		printf("| Use enter key to shoot.Shoot all your enemies using the limited supply of bullets,  | ");
		gotoxy(22,20);
		printf("| which renews if bullet does not miss its target, before your health drains out.     |");
		gotoxy(23,20);
		printf("|_____________________________________________________________________________________|");
		 wait1:if(kbhit)
		  v=getkey();
			if(v==27)mainmenu();
			goto wait1;}
    	if(y==5)
    	{system("cls");gotoxy(12,4);printf("     Press Esc key to go to main menu ");gotoxy(40,0);
		FILE *fp;int hs;
	    fp=fopen("highscorebt.dat","r");
        fscanf(fp,"%d",&hs);
        fclose(fp);
		gotoxy(19,20);
		printf(" ____________ ____");gotoxy(20,20);
		printf("| High score | %d |",hs);gotoxy(21,20);
		printf("|____________|____|");
		 wait2:if(kbhit)
		 	v=getkey();
			if(v==27)mainmenu();goto wait2;
		}
        if(y==6)
    	{int n;
		exit:
		n=1;
    	
    	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),270);
		    		
		    		gotoxy(25,35);
		    		printf(" ____________________________________________________________________");
		    		gotoxy(26,35);
		    		printf("|                   Do you really want to exit?                      |");
		    		gotoxy(27,35);
		    		printf("|          YES                                       NO              |");
		    		gotoxy(28,35);
		    		printf("|____________________________________________________________________|");
		    		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),245);
		           gotoxy(27,46);
				   printf("YES");
				   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		
		
		
		
		
		
			w2:
					 if(kbhit){
			int v=getkey();	
		 	if(v==3)goto left1;
		 	if(v==4)goto right1;
		 	if(v==5)goto enter2; 
			 if(v==27)mainmenu();}
			right1:
		          {if(n!=2)
		           n=n+1;
		           SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),270);
		    		
		    		gotoxy(25,35);
		    		printf(" ____________________________________________________________________");
		    		gotoxy(26,35);
		    		printf("|                   Do you really want to exit?                      |");
		    		gotoxy(27,35);
		    		printf("|          YES                                       NO              |");
		    		gotoxy(28,35);
		    		printf("|____________________________________________________________________|");
		    		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),245);
		           gotoxy(27,88);
				   printf("NO");
				   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		           if(kbhit){
		 	int v=getkey();	
		 	if(v==3)goto left1;
		 	if(v==4)goto right1;
		 	if(v==5)goto enter2;
			 if(v==27)mainmenu(); }}
		 	
		 	goto w2;
		 	
		 	left1:
		          {if(n!=1)
		           n=n-1;
		           SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),270);
		    		
		    		gotoxy(25,35);
		    		printf(" ____________________________________________________________________");
		    		gotoxy(26,35);
		    		printf("|                   Do you really want to exit?                      |");
		    		gotoxy(27,35);
		    		printf("|          YES                                       NO              |");
		    		gotoxy(28,35);
		    		printf("|____________________________________________________________________|");
		    		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),245);
		           gotoxy(27,46);
				   printf("YES");
				   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		           if(kbhit){
		 	int v=getkey();	
		 	if(v==3)goto left1;
		 	if(v==4)goto right1;
		 	if(v==5)goto enter2;
			 if(v==27)mainmenu(); }}
		    		
			goto w2;	
			
			
			
			enter2:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		system("cls");if(n==1)exit(1);else mainmenu();}






}

	int main(){cursor();mainmenu();}
