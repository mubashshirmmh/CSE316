#include<iostream>
using namespace std;
int queue1[50],front1=0,rear1=0,n=50;
int queue2[50],front2=0,rear2=0,m=50;
void push1(int val)
{
	if(front1==0 && rear1==n)
	cout<<"\nQueue is full";
	else
	{
		queue1[rear1]=val;
		rear1++;
	}
}
void push2(int val)
{
	if(front2==0 && rear2==m)
	cout<<"\nQueue is full";
	else
	{
		queue2[rear2]=val;
		rear2++;
	}
}
pop1(int val)
{
	int f,k,no;
	if(front1==rear1)
	cout<<"\nQueue is empty";
	else
    {
    	for(int j=0;j<=n;j++)
    	{
    		if(queue1[j]==val)
    		{
    			no=queue1[j];
    			k=j;
    			break;
			}
		}
		f=front1;
		for(int i=k;i>f;i--)
		{
			queue1[k]=queue1[k-1];
		}
		front1--;
    }	
}
void pop2(int val)
{
	int f,k,no;
	if(front2==rear2)
	cout<<"\nQueue is empty";
	else
    {
    	for(int j=0;j<=n;j++)
    	{
    		if(queue2[j]==val)
    		{
    			no=queue2[j];
    			k=j;
    			break;
			}
		}
		f=front2;
		for(int i=k;i>f;i--)
		{
			queue2[k]=queue2[k-1];
		}
		front2--;
    }	
}
bool search1(int val)
{
	if(rear1==front1)
	cout<<"\nQueue is empty";
	else
	{
		for(int i=front1;i<=rear1;i++)
		{
			if(val==queue1[i])
			return true;
			else 
			return false;
		}
	}
}
bool search2(int val)
{
	if(rear2==front2)
	cout<<"\nQueue is empty";
	else
	{
		for(int i=front2;i<=rear2;i++)
		{
			if(val==queue2[i])
			return true;
			else 
			return false;
		}
	}
}
int popindex(int index)
{
	int no;
	if(front2==rear2)
	cout<<"\nQueue is empty";
	else
	{
		no=queue2[index];
		front2--;
	}
	return no;
}
struct process{
	int pid,p,at,bt;
};
int main()
{
	int a,i,j,k,min=100,z,l;
	cout<<"\nEnter No. of processes:";
	cin>>a;
	process process1[a];
	int arr[a];
	for(i=0;i<a;i++)
	
	{
		process1[i].pid=i+1;
		cout<<"\nEnter Priority of "<<i+1<<" process:";
		cin>>process1[i].p;
		cout<<"\nEnter Arrival Time of "<<i+1<<" process:";
		cin>>process1[i].at;
		cout<<"\nEnter Burst Time of "<<i+1<<" process:";
		cin>>process1[i].bt;
	}
	for(j=0;j>=0;j++)             //complexity=j
	{
		for(i=0;i<a;i++)             //complexity=a*j
		{
			if(process1[i].at<=j && !search1(process1[i].pid) && !search2(process1[i].pid) && process1[i].bt>0)
			{
				push1(process1[i].pid);
			}
		}
		for(i=0;i<a;i++)             //complexity=a*j
		{
			if(process1[i].at<=j && process1[i].bt>0 && !search2(process1[i].p))
			{
				if(process1[i].p>min)
				{
					min=process1[i].p;
				}
			}
		}
		if(front1!=rear1)                //complexity=1*j
		{
			for(i=0;i<a;i++)                         //complexity=a*j
			{
				if(process1[i].p==min)              //complexity=1*j
				{
					process1[i].bt-=1;
					if(j>0 && z!=process1[i].pid && z!=-1)     //complexity=1*j
					{
						pop1(z);
						push2(z);
					}
					z=process1[i].pid;
					//prev=min;
					if(process1[i].bt==0)          //complexity=1*j
					{
						arr[process1[i].pid]=j;
						pop1(process1[i].pid);
						z=-1;
					}
					break;
				}
			}
		}
		if(front1==rear1)                              //complexity=1*j
		{
			if(front2!=rear2)                          //complexity=1*j
			{
				l=popindex(front2);
				for(i=0;i<a;i++)                       //complexity=a*j
				{
					if(process1[i].pid==l && process1[i].bt>0)   //complexity=1*j
					{
						process1[i].bt-=1;
						if(process1[i].bt==0)                    //complexity=1*j
						{
							arr[process1[i].pid]=j;
						}
						push2(process1[i].pid);
					}
				}
			}
		}
		if(front1==rear1 && front2==rear2)                          //comlexity=1*j
		{
			break;
		}
	}
	for(i=1;i<a;i++)                                                 //complexity=a
	{
		cout<<"\nProcess ID :\t\t"<<i<<"\nCompletion Time :\t\t "<<arr[i];
		cout<<"\nWaiting Time :\t\t"<<arr[i]-(process1[i].at+process1[i].bt);
		cout<<"\nTurn Around Time :\t\t"<<arr[i]-process1[i].at;
	}
}
