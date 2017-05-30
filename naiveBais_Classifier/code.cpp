#include<bits/stdc++.h>
#define row 70
#define col 60
int image[100][100][4]; 
int p,n; 
int count;
int main(){
	FILE *train_input = fopen("facedatatrain","r");
	FILE *train_output = fopen("facedatatrainlabels","r");
	if(train_input==NULL || train_output==NULL){
		printf("ERROR");
		return 0;
	}
	for(int i=0;i<451;i++){
		char output[10];
		fgets(output,10,train_output);
		if(output[0]=='0') n+=1;
		else p+=1;
		for(int j=0;j<70;j++){
			char input[100];
			fgets(input,100,train_input);
			for(int i=0;i<60;i++){
				if(input[i]=='#'&&output[0]=='0')	image[j][i][0]+=1;
				else if(input[i]=='#'&&output[0]=='1')	image[j][i][1]+=1;
				else if(input[i]==' '&&output[0]=='0')	image[j][i][2]+=1;
				else if(input[i]==' '&&output[0]=='1')	image[j][i][3]+=1;
			}
		}
	}
	fclose(train_input);
	fclose(train_output);
	FILE *test_input = fopen("facedatatest","r");
	FILE *test_output = fopen("facedatatestlabels","r");
	if(test_input==NULL){
		printf("ERROR");
		return 0;
	}
	for(int i=0;i<150;i++){
		char output[10];
		double yes=0,no=0;
		char input[100];
		int mat[100][100];
		fgets(output,10,test_output);
		for(int i=0;i<70;i++){		
			fgets(input,100,test_input);	
			for(int j=0;j<60;j++){
				mat[i][j] = input[j];
			}
		}
				
		for(int i=0;i<70;i++){
			for(int j=0;j<60;j++){
				if(mat[i][j]=='#'){
					yes+=log((1.0*image[i][j][1]+1)/(p+2));
					no+=log((1.0*image[i][j][0]+1)/(n+2));
				}
				else{
					yes+=log((1.0*image[i][j][3]+1)/(p+2));
					no+=log((1.0*image[i][j][2]+1)/(n+2));
				}
			}
		}
		yes+=log(p/451.0);
		no+=log(n/451.0);
		int ans = yes>no;
		count+=(ans==(output[0]-'0'));
	}
	printf("accuracy=%lf\n",count*1.0/150);
	return 0;
}














