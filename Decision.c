#include<stdio.h>
#include<stdlib.h>

int n;
float counts[6]={0},totcount[6]={0};
float gin[6],GINI[3];

struct items
{
	int outlook,humidity;
	int wind,tennis;
}day[20];

struct node
{
	int data;
	struct node *left,*right;
};

struct node* create(int val)
{
	struct node *new=(struct node*)malloc(sizeof(struct node));
	new->data=val;
	new->left=NULL;
	new->right=NULL;
	return new;
}

void counter()
{
	int i;
	for(i=0;i<n;i++)
	{
		if(day[i].outlook==0)
			totcount[0]++;
		if(day[i].outlook==1)
			totcount[1]++;
		if(day[i].humidity==0)
			totcount[2]++;
		if(day[i].humidity==1)
			totcount[3]++;
		if(day[i].wind==0)
			totcount[4]++;
		if(day[i].wind==1)
			totcount[5]++;

		if(day[i].outlook==0 && day[i].tennis==1)
			counts[0]++;
		if(day[i].outlook==1 && day[i].tennis==1)
			counts[1]++;
		if(day[i].humidity==0 && day[i].tennis==1)
			counts[2]++;
		if(day[i].humidity==1 && day[i].tennis==1)
			counts[3]++;
		if(day[i].wind==0 && day[i].tennis==1)
			counts[4]++;
		if(day[i].wind==1 && day[i].tennis==1)
			counts[5]++;
	}
}

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




int main()
{

	int i;
	printf("Enter Number of inputs:\n");
	scanf("%d",&n);

	for(i=0;i<n;i++)
	{
		printf("Details of Day %d:\n",i+1);
		printf("Input the OUTLOOK:\n(0) for Sunny\t(1) for rainy\n");
		scanf("%d",&day[i].outlook);
		printf("Input the HUMIDITY:\n(0) for NORMAL\t(1) for HIGH\n");
		scanf("%d",&day[i].humidity);
		printf("Input the WIND:\n(0) for WEAK\t(1) for STRONG\n");
		scanf("%d",&day[i].wind);
		printf("PLAY TENNIS?:\n(0) for NO\t(1) for YES\n");
		scanf("%d",&day[i].tennis);
	}
	printf("-----------Entered Details---------------\n");
	printf("Day\tOUTLOOK\tHUMIDITY\tWIND\tTENNIS\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t",i+1);
		if(day[i].outlook==0)
			printf("Sunny\t");
		else if(day[i].outlook==1)
			printf("Rainy\t");
		else
			printf("INVALID\t");
		
		if(day[i].humidity==1)
			printf("HIGH\t\t");
		else if(day[i].humidity==0)
			printf("NORMAL\t\t");
	        else	
			printf("INVALID\t");

		if(day[i].wind==0)
			printf("WEAK\t");
		else if(day[i].wind==1)
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
}
