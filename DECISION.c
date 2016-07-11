
//-------------------------------------<<START>>----------------------------------------------
//A C Program to input a specific set of training instructions, and based on that build the 
//decision tree and then take  input of characters and decide the class of the set of attributes

#include<stdio.h>
#include<stdlib.h>

//Global declaration

int YES=799,NO=999;
static int gName=0;
FILE *outputFile;
int n,max,inp[3];
float counts[6]={0},totcount[6]={0};
float gin[6],GINI[3];
//-------------------------------------------------------------------------------------------------
//Array of Structure for day elements

struct
{
	int property[3];
	int tennis;

}day[20];
//------------------------------------------------------------------------------------------------
//A tree node structure
struct node
{
	int data;
	struct node *left,*right;
}*root=NULL;
//------------------------------------------------------------------------------------------------
//Function to create node
struct node* create()
{
	struct node *new=(struct node*)malloc(sizeof(struct node));
	new->left=NULL;
	new->right=NULL;
	return new;
}

//-------------------------------------------------------------------------------------------------
//Function to count the attribute values and also count the classes related to attribute values

void counter()
{
	int i;
	for(i=0;i<n;i++)
	{
		if(day[i].property[0]==0)
			totcount[0]++;
		if(day[i].property[0]==1)
			totcount[1]++;
		if(day[i].property[1]==0)
			totcount[2]++;
		if(day[i].property[1]==1)
			totcount[3]++;
		if(day[i].property[2]==0)
			totcount[4]++;
		if(day[i].property[2]==1)
			totcount[5]++;

		if(day[i].property[0]==0 && day[i].tennis==1)
			counts[0]++;
		if(day[i].property[0]==1 && day[i].tennis==1)
			counts[1]++;
		if(day[i].property[1]==0 && day[i].tennis==1)
			counts[2]++;
		if(day[i].property[1]==1 && day[i].tennis==1)
			counts[3]++;
		if(day[i].property[2]==0 && day[i].tennis==1)
			counts[4]++;
		if(day[i].property[2]==1 && day[i].tennis==1)
			counts[5]++;
	}
}

//----------------------------------------------------------------------------------------------
//Function to calculate the GINI values of various attributes

void gini()
{
	int noval,i=0,j=0;
	float a,b,c;
	while(i<n)
	{
		noval=(totcount[i]-counts[i]);
		a=(counts[i]/totcount[i]);
		b=(noval/totcount[i]);
		c=(totcount[i]/n);
		gin[i]=((a*a)+(b*b));
		gin[i]=((gin[i])*c);
		i++;
		noval=(totcount[i]-counts[i]);
		a=(counts[i]/totcount[i]);
		b=(noval/totcount[i]);
		c=(totcount[i]/n);
		gin[i]=((a*a)+(b*b));
		gin[i]=((gin[i])*c);


		GINI[j]=gin[i-1]+gin[i];
		j++;
		i++;
	}
}

//----------------------------------------------------------------------------------------------------
//Function to find an attribute with maximum GINI value and return its index value
void maximum()
{
	float maxi=0;
	int i;
	for(i=0;i<3;i++)
	{
		if(GINI[i] > maxi)
		{
			max=i;
			maxi=GINI[i];
		}
	}
}

//------------------------------------------------------------------------------------------------------
//function for tree creation
void tree()
{
	int i;
	struct node *temp;
	for(i=0;i<3;i++)
	{
		temp=root;
		maximum();
		if(temp==NULL)
		{
			temp=create();
			root=temp;
		}
		else
		{
			while(temp->right!=NULL)
				temp=temp->right;
		}
		temp->data=max;
		temp->left=create();
		temp->left->data=YES;
		YES++;
		temp->right=create();
		GINI[max]=0;
	}
	temp=root;
	while(temp->right != NULL)
		temp=temp->right;

	temp->data=NO;
	NO++;
}

//--------------------------------------------------------------------------------------------------
//function for verifying the input data and determining the class
void verify(struct node* temp2)
{
	if(temp2)
	{
		if(temp2->data >= 999)
		{
			printf("NO you can't play tennis..!\n");
			exit(0);
		}
		else if(inp[temp2->data]==0 && temp2->left->data >= 799)
		{
			printf("YES you can play tennis..!!\n");
			exit(0);
		}
		else
			verify(temp2->right);
	}

}

//---------------------------------------------------------------------------------------------------
//function to take input from the user..
void input()
{
	struct node *temp1;
	temp1=root;
	printf("Enter the details:\n");
	printf("Input the OUTLOOK:\n(0) for Sunny\t(1) for rainy\n");
	scanf("%d",&inp[0]);
	printf("Input the HUMIDITY:\n(0) for NORMAL\t(1) for HIGH\n");
	scanf("%d",&inp[1]);
	printf("Input the WIND:\n(0) for WEAK\t(1) for STRONG\n");
	scanf("%d",&inp[2]);

	verify(temp1);
}

//------------------------------------------------------------------------------------------------------
//Function to plot the graph
void preorderDotDump (struct node* temp3, FILE* outputFile)
{

	if (temp3 != NULL) 
	{
		if(temp3->data==0)
			fprintf (outputFile, "%d [label=OUTLOOK,color=black];\n",temp3->data);
		else if(temp3->data==1)
			fprintf (outputFile, "%d [label=HUMIDITY,color=black];\n",temp3->data);
		else if(temp3->data==2)
			fprintf (outputFile, "%d [label=WIND,color=black];\n",temp3->data);
		else if(temp3->data >=999)
			fprintf (outputFile, "%d [label=NO,color=red];\n",temp3->data);
		else if(temp3->data>=799)
			fprintf (outputFile, "%d [label=YES,color=red];\n",temp3->data);

		if (temp3->left != NULL)
		{ 
			fprintf (outputFile, "%d -> %d[label=", temp3->data,temp3->left->data);
			if(temp3->data==0)
				fprintf(outputFile,"SUNNY,color=green];\n");
			else if(temp3->data==1)
				fprintf(outputFile,"NORMAL,color=green];\n");
			else if(temp3->data==2)
				fprintf(outputFile,"WEAK,color=green];\n");
		}


		if (temp3->right != NULL)
		{
			fprintf (outputFile, "%d -> %d[label=", temp3->data,temp3->right->data);
			if(temp3->data==0)
				fprintf(outputFile,"RAINY,color=blue];\n");
			else if(temp3->data==1)
				fprintf(outputFile,"HIGH,color=blue];\n");
			else if(temp3->data==2)
				fprintf(outputFile,"STRONG,color=blue];\n");
		}

		preorderDotDump (temp3->left, outputFile);

		preorderDotDump (temp3->right, outputFile);

	}

}

//-------------------------------------------------------------------------------------------------------
//Function to write graph attributes to a file
void dotDump(struct node* root, FILE *outFile)

{

	gName++;

	fprintf (outFile, "digraph BST {\n",gName);



	preorderDotDump (root, outFile);

	fprintf (outFile, "}\n");

}

//------------------------------------------------------------------------------------------------------------
//main driver function
int main()
{

	int i;
	FILE *pipe;
	outputFile = fopen ("decision.dot", "w");
	fclose (outputFile);

	printf("Enter Number of inputs:\n");
	scanf("%d",&n);

	for(i=0;i<n;i++)
	{
		printf("Details of Day %d:\n",i+1);
		printf("Input the OUTLOOK:\n(0) for Sunny\t(1) for rainy\n");
		scanf("%d",&day[i].property[0]);
		printf("Input the HUMIDITY:\n(0) for NORMAL\t(1) for HIGH\n");
		scanf("%d",&day[i].property[1]);
		printf("Input the WIND:\n(0) for WEAK\t(1) for STRONG\n");
		scanf("%d",&day[i].property[2]);
		printf("PLAY TENNIS?:\n(0) for NO\t(1) for YES\n");
		scanf("%d",&day[i].tennis);
	}
	printf("-----------Entered Details---------------\n");
	printf("Day\tOUTLOOK\tHUMIDITY\tWIND\tTENNIS\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t",i+1);
		if(day[i].property[0]==0)
			printf("Sunny\t");
		else if(day[i].property[0]==1)
			printf("Rainy\t");
		else
			printf("INVALID\t");

		if(day[i].property[1]==1)
			printf("HIGH\t\t");
		else if(day[i].property[1]==0)
			printf("NORMAL\t\t");
		else	
			printf("INVALID\t");

		if(day[i].property[2]==0)
			printf("WEAK\t");
		else if(day[i].property[2]==1)
			printf("STRONG\t");
		else
			printf("INVALID\t");

		if(day[i].tennis==0)
			printf("NO\t");
		else if(day[i].tennis==1)
			printf("YES\t");
		else
			printf("INVALID\t");
		printf("\n");
	}
	counter();
	gini();
	printf("GINI values:\n");
	for(i=0;i<3;i++)
		printf("%.3f\n",GINI[i]);
	tree();
	outputFile=fopen("decision.dot","a");

	if (outputFile != NULL) 
	{
		dotDump(root,  outputFile);

	}
	fclose (outputFile);
	pipe=popen("dot -Tps decision.dot -o decision.ps","w");

	pclose(pipe);	

	pipe=popen("evince decision.ps","r"); 

	pclose(pipe);
}
//------------------------------------------/^END^\-----------------------------------------------------
