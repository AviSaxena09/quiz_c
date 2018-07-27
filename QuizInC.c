#include<string.h>
#include <stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>

int selected[10],alloted[10];		//Questions selected randomly are stored and selected option marks//
char opted[10],category[10][50];	//Saving results//

//structure defined for type candidiate//
struct candidiate{
	char name[50];
	char rollno[12];
	char clg[50];
}c;

	//To accept Data from the candidiate//
struct candidiate getData(struct candidiate c){
			system("cls");
			printf("\t\t\t\t\tWELCOME\n");
			printf("\nEnter your Name					:				");
			gets(c.name);
			printf("\nEnter your roll number				:				");
			gets(c.rollno);
			printf("\nEnter your College name				:				");
			gets(c.clg);
			
			return c;
		}
	//Display candidiate info//
void displayName(struct candidiate c){
			system("cls");
			printf("\nName		:				%s",c.name);
			printf("\nRoll Number	:				%s",c.rollno);
			printf("\nCollege		:				%s",c.clg);
			printf("\n");
		}
		
		
	//To display the result after the quiz//
void result(struct candidiate c, int score)
	{
			displayName(c);
			printf("\nCongratulations !!! ");
			printf("\nYou have completed the quiz.");
			printf("You have got %d correct out of 10 questions.",score);
						
	}

///////////////////////////////////////////
//Structure defined for question//
struct Question{
	char cat[50];
	char ques[400];
	char choice[4][100];
	char ans;
}q[30];

//Function returns the marks for each question after taking input for each question"
int display(struct Question q,int qno, struct candidiate c)
	{
		system("cls");
		displayName(c);
		int flag=0;
		char a;
		printf("\nCategory					:	%s",q.cat);
		printf("\nQ%d ) %s",qno,q.ques);
		printf("\n\nPLEASE SELECT ONLY ONE OPTION FROM BELOW");
		printf("\n\nA.	%s",q.choice[0]);
		printf("\n\nB.	%s",q.choice[1]);
		printf("\n\nC.	%s",q.choice[2]);
		printf("\n\nD.	%s",q.choice[3]);
		printf("\n\n\n\nEnter your Choice	:	");
		fflush(stdin);
		scanf("%c",&a);
		a=toupper(a);
		opted[qno-1]=a;
		strcpy(category[qno-1],q.cat);
				
		if(a==q.ans || q.ans==(a-32) )
			{
				flag=1;
			}
		else
			{
				flag=0;
			}
		
		return flag;
	}

//Display the result i=of each question one by one//
void displayQ(struct Question q ,int qno, struct candidiate c)
	{
		char a;
		printf("\n\nHere are your Answers :");
		printf("\n\nQ%d ) %s",qno,q.ques);
		printf("\n\nA.	%s",q.choice[0]);
		printf("\n\nB.	%s",q.choice[1]);
		printf("\n\nC.	%s",q.choice[2]);
		printf("\n\nD.	%s",q.choice[3]);
		printf("\nYou entered		:	%c",opted[qno-1]);
		printf("\nCorrect Anwer		:	%c",q.ans);
		printf("\nMarks Alloted		:	%d",selected[qno-1]);
	}

/////////////////////////////////////
//To write inside a file//
void write(){
		printf("Enter no. of Records");
		int i,n;
		scanf("%d",&n);
		FILE *fp;
		struct Question qq;
		fp=fopen("QuestionBank.txt", "w" );
		for(i=1;i<=n;i++)
			{
				fflush(stdin);
				printf("\nEnter Category		:	");
				gets(qq.cat);
				printf("\nEnter Ques			:	");
				gets(qq.ques);
				printf("Enter Choices		:	");
				printf("Enter choice A	:	");
				gets(qq.choice[0]);
				printf("Enter choice B	:	");
				gets(qq.choice[1]);
				printf("Enter choice C	:	");
				gets(qq.choice[2]);
				printf("Enter choice D	:	");
				gets(qq.choice[3]);
				printf("Enter correct choice	:	");
				scanf("%c",&qq.ans);
				printf("confirm");
				int chh;
				scanf("%d",&chh);
				if(chh==1)
				fwrite(&qq,sizeof(qq),1,fp);
				else
				i--;
			}
			fclose(fp);
	}

//To read from the file//
void read(){
	int i;
	FILE *fp;
	fp=fopen("QuestionBank.txt", "r");
	for(i=0;i<30;i++)
	{
		fread(&q[i],sizeof(q[i]),1,fp);
	}	
}
//to initialize the arrays and select random question//


void init(){
	int i=0,j,s,f;
	//Intialize Select array to -1//
	for(i=0;i<30;i++)
		{
			selected[i]=0;
			alloted[i]=-1;
		}

	for(i=0;i<10;i++){
		srand(time(NULL));
		j=rand()%30;
		while(1){
			f=1;
			j=rand()%30;
			for(s=0;s<i;s++){
				
				if(alloted[s]==j){
				f=0;		
				}
			}	
			if(f==1){
			alloted[i]=j;
			break;
			}
		}		
	}		
}

//To calculate the marks//
int cal()
	{
	int i,score=0;
	for(i=0;i<10;i++)
	{
		score+=selected[i];
	}
	return score;
	}

//To conduct a quiz a candidiate//
void quiz(struct candidiate c)
{
	int i;
	read();
	init();
	for(i=0;i<10;i++)
	{
		selected[i] = display(q[alloted[i]],i+1,c);
	}

}

//To compute the result and display the category wise result one by one//
void completed(struct candidiate c , int score)
{
			int i;
			for(i=0;i<10;i++)
			{
				system("cls");
				result(c,score);
				displayQ(q[i],i+1,c);				
				fflush(stdout);
				getch();
			}
			
			system("cls");
			int j=0,s=0;
			for(i=0;i<10;i++)
			{
				for(j=i+1;j<10;j++)
				{
					if(strcmpi(category[i],category[j])==0)
					{
						selected[i]+=selected[j];
						strcpy(category[j],"-1");
					}
				}
			}
			
			printf("Category Wise Marking");
			for(i=0;i<10;i++)
			{
				if(strcmpi(category[i],"-1")!=0)
				{
					printf("\n%d > Category : %s	",s+1,category[i]);
					printf("\n\t\tMarks : %d",selected[i]);
					s++;
				}
			}
			
			printf("\n\nYour total Score is %d out of 10",score);
			
}

//Main function//
int main(){
	system("cls");
	int i,score;
	struct candidiate c;
	c=getData(c);
	quiz(c);
	score=cal();
	completed(c,score);
	return 1;
}
