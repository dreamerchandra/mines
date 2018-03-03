
#include<stdio.h>
#include<time.h>

//user_x user_y return current x and y position of the user at any time in the program and is promted with user variable
#define user_y user%10
#define user_x (user-user_y)/10

//randomize bomb location with time zone as per the system
#define ran_sec (timeinfo->tm_sec)%6
#define ran_min (timeinfo->tm_min)%6
#define ran_hrs (timeinfo->tm_hour)%6

char bombs[6][6],flag[6][6];
//returns bomb count sourrounding the area
int bombs_count(int i,int j){




int count=0;
if(bombs[i-1][j-1]=='b')count++;
if(bombs[i][j-1]=='b')count++;
if(bombs[i+1][j-1]=='b')count++;
if(bombs[i-1][j]=='b')count++;
if(bombs[i+1][j]=='b')count++;
if(bombs[i-1][j+1]=='b')count++;
if(bombs[i][j+1]=='b')count++;
if(bombs[i+1][j+1]=='b')count++;
return count;
}
int main(int args, int argc){


int user=00,used_flag,won;//user's current position is given by 2 digits xy x-rep row number y-rep column number
int i,j,user_ip;


//geting time stamp
time_t raw_time;
struct tm *timeinfo;
time(&raw_time);
timeinfo = localtime ( &raw_time );


//delete garbage values in bomb and flag
for(i=0;i<6;i++){




for(j=0;j<6;j++){
bombs[i][j]=' ';
flag[i][j]=' ';
}
}
//initializing bombs
for(i=0;i<6;i++){

bombs[0][0]=' ';


bombs[i][(ran_min+i)%6]='b';
bombs[i][(ran_sec+i)%6]='b';
}
/*showing bombs and bomb count near the area




for(i=0;i<6;i++){
printf("%d",i);
for(j=0;j<6;j++)
printf("\t%c",bombs[i][j]);
printf("\n\n");
}
printf("\n");
for(i=0;i<6;i++){
for(j=0;j<6;j++)
printf("\t%d",bombs_count(i,j));
printf("\n\n");
}*/
/*user moves documentation
i-row j-column
hot key documentation
1- i+1 j-1
2- i+1 j
3- i+1 j+1
4- i   j-1
5- flag/unflag current position
6- i   j+1
7- i-1 j-1
8- i-1 j
9- i-1 j+1
0- force end
*/


//user display dashboard
display_dashboard:
printf("\n\n\n");
printf("   0\t1\t2\t3\t4\t5\n");//show index
for(i=0;i<6;i++){


printf("%d",i);
for(j=0;j<6;j++){
if((user_x==i)&&(user_y==j))
printf("   %c%d",flag[i][j],bombs_count(i,j));
else
printf("    %c",flag[i][j]);
}
printf("\n");
}
//geting input from the user in order to play the game
get_ip:
scanf("%d",&user_ip);
//check if user dies
if((bombs[user_x][user_y]=='b')&&(flag[user_x][user_y]!='f')&&(user_ip!=5))
user_ip=108;

//map the input with the current dashboard
switch(user_ip){

case 0:
printf("\n\nThanks for playing...\n\n");
break;

case 1:
user=((user_x+1)%6)*10+((((user_y-1)<0)?5-user_y:user_y-1)%6);
goto display_dashboard;

case 2:
user=((user_x+1)%6)*10+user_y;
goto display_dashboard;

case 3:
user=((user_x+1)%6)*10+((((user_y+1)>6)?5-user_y:user_y+1)%6);
goto display_dashboard;

case 4:
user=((user_x)%6)*10+((((user_y-1)<0)?5-user_y:user_y-1)%6);
goto display_dashboard;

case 5:
flag[user_x][user_y]=(flag[user_x][user_y]=='f')?' ':'f';used_flag=0;
for(int i=0;i<6;i++){for(j=0;j<6;j++)if(flag[i][j]=='f')used_flag++;}
if(used_flag>10){flag[user_x][user_y]=' ';goto get_ip;}
else
goto display_dashboard;

case 6:
user=(user_x)*10+((((user_y+1)>6)?5-user_y:user_y+1)%6);
goto display_dashboard;

case 7:
user=((((user_x-1)<0)?5-user_x:user_x-1)%6)*10+((((user_y-1)<0)?5-user_y:user_y-1)%6);
goto display_dashboard;

case 8:
user=((((user_x-1)<0)?5-user_x:user_x-1)%6)*10+user_y;
goto display_dashboard;

case 9:
user=((((user_x-1)<0)?5-user_x:user_x-1)%6)*10+((((user_y+1)>6)?5-user_y:user_y+1)%6);
goto display_dashboard;

case 108:
printf("\n\nExploded by a bomb....BE CAREFULL NEXT TIME\n\n");
break;

default:
goto get_ip;
}

//final display
won=0;
for(i=0;i<6;i++){


for(j=0;j<6;j++){
printf("%c%c  ",bombs[i][j],flag[i][j]);
if((bombs[i][j]=='b')&&(flag[i][j]=='f'))won++;
}
printf("\n");
}
printf("\n\nYou have successfully found %d bombs\n Keep working on it.....\n You could be a champ",won);
printf("\nFeedBack are accepeted......");
scanf("%d",&won);
}
