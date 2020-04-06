#include<iostream>
using namespace std;

void merge(int *, int , int);
void sort(int *, int , int );


int main(void)
{
	int *ar;
	ar = new int[32];
	int *i;
	int j, k, casee;
	cin>>casee;
	for(i=ar,j=0;j<casee;i++,j++) cin>>*i;
	
	merge(ar, 0, casee);
	
	for(i=ar,j=0;j<casee;i++,j++) cout<<*i<<" ";
	cout<<endl;
	
}

void sort(int *ar, int start, int end)
{
	int i, k;
	int time = end - start;
	for(k=0;k<time;k++)
	{
		for(i=start;i<end-1;i++)
		{	
			if(ar[i] > ar[i+1]) 
			{
				int tmp = ar[i];
				ar[i] = ar[i+1];
				ar[i+1] = tmp;
			}
		}
	}
	/*cout<<"check: ";
	for(i=0;i<casee;i++) cout<<ar[i]<<" ";
	cout<<endl<<"check end"<<endl;*/

}

void merge(int *ar, int start, int end)
{
	int i, j, k, flag = 0;
	int arr[32];
	int med = (end + start) / 2;
	cout<<"start: "<<start<<" end: "<<end<<" med: "<<med<<endl;
	if(end - start < 5)
	{
		sort(ar, start, end);
		return;
	}
	
	else
	{
		merge(ar, start, med);
		merge(ar, med, end);
	}
	for(i = start, j = med, k = start ;k<end;k++)
	{

		if(ar[i] <= ar[j])
		{
			arr[k] = ar[i];
			i++;
			if(i == med)
			{
				flag = 1;
				break;
			}
		}
		else if(ar[i] > ar[j])
		{
			arr[k] = ar[j];
			j++;
			if(j == end)
			{
				flag = 2;
				break;
			}
		}
	}
	k++;
	if(flag == 1) for(;k<end;k++, j++) arr[k] = ar[j];
	
	if(flag == 2) for(;k<end;k++, i++) arr[k] = ar[i];
	
	for(k = start;k<end;k++) ar[k] = arr[k];
}
