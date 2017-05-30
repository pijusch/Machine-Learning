#include<string.h>
#include<iostream>
#include<stdio.h>
#define nh 4
#define ni 960
#define no 2
#define epochs 150
using namespace std;
#include "neuralNet.h"
int c;
char clear[]="\033[H\033[J";
#define clear() printf("%s",clear)
void readData(FILE *fp){
	char fileName[100];
	char *pch;
	while(fgets(fileName,100,fp)!=0){
	fileName[strlen(fileName)-1]=0;
	pch = strtok(fileName,"/");
 	for(int i=1;i<=7;i++)
	pch = strtok(NULL,"/");
	char file[100] = "data/";
	strcat(file,pch);
	FILE *f= fopen(file,"rb");
	int m,n,maxgreyscaleval;
	char pgmtype[3];
	fscanf(f,"%s",pgmtype);
	fscanf(f,"%d %d\n%d",&m,&n,&maxgreyscaleval);
	fgetc(f);
	for(int i=0;i<32;i++)
	{
		int ch;
		for(int j=0;j<30;j++)
		{
			ch = fgetc(f);
			input[c][i*30+j] = ch*1.0/255;
		}
	}
	input[c][ni]=-1; //bias
	pch = strtok(pch,"_");
	pch = strtok(NULL,"_");
	pch = strtok(NULL,"_");
	pch = strtok(NULL,"_");
	if(strcmp(pch,"sunglasses")==0) output[c][0]=1;	
	else if(strcmp(pch,"open")==0) output[c][1]=1;
	c+=1;
 }
}

int main(){
 hiddenN[nh]=-1; //bias
 char fileName[100];

 FILE *trainingSet = fopen("straightrnd_train.list","r");
 readData(trainingSet);
 fclose(trainingSet);

 init();
 //initializeWeights(); //intialize weghts
 int d=0;
 for(int i=0;i<epochs;i++){   //Train the weights
  clear();
  printf("Progress\n----------------------------%d %c----------------------------\n",(i+1)*100/epochs,'%');
  for(current=0;current<c;current++){
   ffeed();
   backprop(); 
  }
 }

  for(current=0;current<c;current++){
 for(int i=0;i<no;i++)
 ffeed();
 int i;
 for(i=0;i<no;i++) if((double)(outputN[i]>0.5)!=output[current][i]) break;
 if(i==no) d+=1;
 }
 printf("training data accuracy %lf -- %d images\n",d*100.0/c,c);


 for(int i=0;i<1000;i++) for(int j=0;j<no;j++) output[i][j]=0;
 c=0;
 d=0;
 FILE *testingSet = fopen("straightrnd_test1.list","r");
 readData(testingSet);
 fclose(testingSet);

 for(current=0;current<c;current++){
 for(int i=0;i<no;i++)
 ffeed();
 int i;
 for(i=0;i<no;i++) if((double)(outputN[i]>0.5)!=output[current][i]) break;
 if(i==no) d+=1;
 }
 printf("testing data 1 accuracy %lf -- %d images\n",d*100.0/c,c);

 for(int i=0;i<1000;i++) for(int j=0;j<no;j++) output[i][j]=0;
 d=0;
 c=0;
testingSet = fopen("straightrnd_test2.list","r");
 readData(testingSet);
 fclose(testingSet);


 for(current=0;current<c;current++){
 ffeed();
 int i;
 for(i=0;i<no;i++) if((double)(outputN[i]>0.5)!=output[current][i]) break;
 if(i==no) d+=1;
 }
 printf("testing data 2 accuracy %lf -- %d images\n",d*100.0/c,c);
 return 0;
}












