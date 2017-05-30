#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#define row 70
#define column 60
using namespace std;
int pos_f[row+10][column+10][2];
int neg_f[row+10][column+10][2];
int p;
int n;
void train(int r,string x,int result)
{
	int n=x.size();
	n--;
	if(result)
	{
		for(int i=0;i<n;i++)
		{
			if(x[i]=='#')
				pos_f[r][i][0]++;
			else
				pos_f[r][i][1]++;
		}
	}
	else
	{
		for(int i=0;i<n;i++)
		{
			if(x[i]=='#')
				neg_f[r][i][0]++;
			else
				neg_f[r][i][1]++;
		}
	}
}
bool empty(string x)
{
	for(int i=0;i<x.size();i++)
		if(x[i]=='#')
			return false;
	return true;
}
void testing(double* pos,double *neg,int r,string x)
{
	int n=x.size();
	n--;
	for(int i=0;i<n;i++)
	{
		if(x[i]=='#')
		{
			*pos=(*pos)*(pos_f[r][i][0]/(p*1.0));
			*neg=(*neg)*(neg_f[r][i][0]/(n*1.0));
		}
		else
		{
			*pos=(*pos)*(pos_f[r][i][1]/(p*1.0));
			*neg=(*neg)*(neg_f[r][i][1]/(n*1.0));
		}
	}
	
}
int main()
{
	ifstream training("facedatatrain");
	ifstream training_result("facedatatrainlabels");
	if(training.is_open() && training_result.is_open())
	{
		string line;
		string line_result;
		
		int temp=0;
		
		while(getline(training_result,line_result))
		{
			if(atoi(&line_result[0]))
				p++;
			else
				n++;
			temp++;
			bool reading=false;
			int i;
			for(i=0;i<row;i++)
			{
				if(getline(training,line))
				{
					/*if(empty(line))
					{
						if(reading)
							break;
						i=-1;
						reading=false;
					}
					else*/
					{
						reading=true;
						train(i,line,atoi(&line_result[0]));
					}
					
				}
			}
			//cout<<"Trained "<<temp<<" -->"<<i<<" Rows, Result-->"<<line_result<<endl;
		}
		//cout<<p<<" "<<n<<endl;
		cout<<"Trained!\n";
		training.close();
		training_result.close();
	}
	else
	{
		cout<<"Error opening training file\n";
		exit(1);
	}


	/***************************Testing********************************/
	ifstream test("facedatatest");
	ifstream test_result("facedatatestlabels");
	if(test.is_open() && test_result.is_open())
	{
		string line,line_result;
		double confusion[2][2]={0}; //tp tn fp fn
		while(getline(test_result,line_result))
		{
			int c=atoi(&line_result[0]);
			double pos_p=1,neg_p=1; //positive predicted and negative predicted
			bool reading=false;
			int i;
			for(i=0;i<row;i++)
			{
				if(getline(test,line))
				{
					/*if(empty(line))
					{
						if(reading)
							break;
						i=-1;
						reading=false;
					}
					else*/
					{
						reading=true;
						testing(&pos_p,&neg_p,i,line);
					}
					
				}
				//cout<<pos_p<<" "<<neg_p<<endl;
			}
			
			pos_p*=(1.0*p)/(p+n);neg_p*=(1.0*n)/(p+n);
			//cout<<pos_p<<" "<<neg_p<<endl;
			int predicted=(pos_p>neg_p)?1:0;

			confusion[c][predicted]++;
		}
		double sum=0;
		for(int i=0;i<2;i++)
		{
			for(int j=0;j<2;j++)
			{
				cout<<confusion[i][j]<<" ";
				sum+=(confusion[i][j]);
			}
				
			cout<<endl;
		}
		cout<<"Accuracy is "<<((confusion[0][0]+confusion[1][1])/(sum))<<endl;
	}
	else
	{
		cout<<"Error opening test files\n";
		exit(1);
	}

}
