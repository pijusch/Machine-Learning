#include<bits/stdc++.h>

double input[1000][ni+1];
double output[1000][no];
double hiddenN[nh+1];   // Hidden Layer Results
double outputN[no];  //  Output Layer Results
double deltah[ni+1][nh]; //delta  First set of weights 
double deltao[nh+1][no]; // delta Second set of weights
double wh[ni+1][nh]; // First set of weights 
double wo[nh+1][no]; // Second set of weights
double grado[no]; // gradient for output layer
double gradh[nh+1]; // gradient for hidden layer
double alpha =0.3; // Learning Rate
double momentum=0.3; //momentum
int current; // Current Input


void init(){ // Initialize weights
  srand(time(NULL));
  int i,j;
  for(i=0;i<=ni;i++) for(j=0;j<nh;j++) wh[i][j] =(((float)rand() / (double)RAND_MAX) * 0.2 - 0.1); 
  for(i=0;i<=nh;i++) for(j=0;j<no;j++) wo[i][j] =(((float)rand() / (double)RAND_MAX) * 0.2 - 0.1);
}


void initializeWeights()
{	srand(time(NULL));
	//set range
	double rH = 1/sqrt( (double) ni);
	double rO = 1/sqrt( (double) nh);
	//double rH = 4*sqrt( 6/((double) ni+no+1));
	//double rO = 4*sqrt( 6/((double) nh+2));
	
	//set weights between input and hidden 		
	//--------------------------------------------------------------------------------------------------------
	for(int i = 0; i <= ni; i++)
	{		
		for(int j = 0; j < nh; j++) 
		{
			//set weights to random values
			wh[i][j] = ( ( (double)(rand()%100)+1)/100  * 2 * rH ) - rH;
		}
	}
	
	//set weights between input and hidden
	//--------------------------------------------------------------------------------------------------------
	for(int i = 0; i <= nh; i++)
	{		
		for(int j = 0; j < no; j++) 
		{
			//set weights to random values
			wo[i][j] = ( ( (double)(rand()%100)+1)/100 * 2 * rO ) - rO;
		}
	}
}

double sigmoid(double x){ //Sigmoid Function
 return (double)1/((double)1+exp(double(-x)));
}

void ffeed(){

	for(int j=0; j < nh; j++)
	{
		//clear value
		hiddenN[j] = 0;				
		
		//get weighted sum of pattern and bias neuron
		for( int i=0; i <= ni; i++ ) hiddenN[j] += input[current][i]*wh[i][j];
		
		//set to result of sigmoid
		hiddenN[j] = sigmoid( hiddenN[j] );			
	}
	
	//Calculating Output Layer values - include bias neuron
	//--------------------------------------------------------------------------------------------------------
	for(int k=0; k < no; k++)
	{
		//clear value
		outputN[k] = 0;				
		
		//get weighted sum of pattern and bias neuron
		for( int j=0; j <= nh; j++ ) outputN[k] += hiddenN[j]*wo[j][k];
		
		//set to result of sigmoid
		outputN[k] = sigmoid( outputN[k] );
	}


}

void updateW(){
	//input -> hidden weights
	//--------------------------------------------------------------------------------------------------------
	for (int i = 0; i <= ni; i++)
	{
		for (int j = 0; j < nh; j++) 
		{
			//update weight
			wh[i][j] += deltah[i][j];	
			
		}
	}
	
	//hidden -> output weights
	//--------------------------------------------------------------------------------------------------------
	for (int j = 0; j <= nh; j++)
	{
		for (int k = 0; k < no; k++) 
		{					
			//update weight
			wo[j][k] += deltao[j][k];
		}
	}					

}

void backprop()
{		
	//modify deltas between hidden and output layers
	//--------------------------------------------------------------------------------------------------------
	for (int k = 0; k < no; k++)
	{
		//get error gradient for every output node
		grado[k] = outputN[k]*(1-outputN[k])*(output[current][k]-outputN[k]);
		
		//for all nodes in hidden layer and bias neuron
		for (int j = 0; j <= nh; j++) 
		{				
			//calculate change in weight
			deltao[j][k] = alpha*hiddenN[j]*grado[k] + momentum*deltao[j][k];

		}
	}

	//modify deltas between input and hidden layers
	//--------------------------------------------------------------------------------------------------------
	for (int j = 0; j < nh; j++)
	{
		//get error gradient for every hidden node
		double weightedSum = 0;
		for( int k = 0; k < no; k++ ) weightedSum += wo[j][k] * grado[k];
		gradh[j] = hiddenN[j]*(1-hiddenN[j])*weightedSum;

		//for all nodes in input layer and bias neuron
		for (int i = 0; i <= ni; i++)
		{
			//calculate change in weight 
			deltah[i][j] = alpha*input[current][i]*gradh[j] + momentum*deltah[i][j];

		}
	}
	updateW();
	
}

