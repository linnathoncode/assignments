#include <iostream>

using namespace std;

int loopEnteredMerge = 0;
int loopEnteredQuick = 0;
int loopEnteredHeap = 0;

void merge(int arr[], int l, int m, int r, float order)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	
	int L[n1], R[n2];
	
	for(i = 0; i < n1; i++)
	{
		L[i] = arr[l + i];
		loopEnteredMerge++;
	}
	
	for(j = 0; j < n2; j++)
	{
		R[j] = arr[j + 1 + m];
		loopEnteredMerge++;
	}
	
	i = 0;
	j = 0;
	k = l;
	while(i < n1 && j < n2)
	{
		if(order? L[i] >= R[j] :L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
		loopEnteredMerge++;
	}
	
	while(i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
		loopEnteredMerge++;
	}
	
	while(j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
		loopEnteredMerge++;
	}
}

void mergeSort(int arr[], int l, int r, float order)
{
	if(l < r)
	{
		int m = l+(r - l)/2;
		
		mergeSort(arr, l, m, order);
		mergeSort(arr, m+1, r, order);
		
		merge(arr, l, m, r, order);
	}

}

void quickSort(int arr[], int l, int r, float order)
{
	int i = l;
	int j = r;
	int temp;
	int pivot = arr[(l + r) / 2];
	
	while(i <= j)
	{
		while(order? arr[i] > pivot : arr[i]< pivot)
		{
			i++;
			loopEnteredQuick++;
		}
		while(arr[j] > pivot)
		{
			j--;
			loopEnteredQuick++;
		}
		if(i <= j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
 		}
		loopEnteredQuick++;
	}
	if(l < j) quickSort(arr, l, j, order);
	if(i < r) quickSort(arr, i, r, order);
}
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void heapify(int arr[], int n, int i, float order)
{
	int largest  = i; //initialize largest as the root
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	
	if(l < n && (order ? arr[l] < arr[largest] : arr[l] > arr[largest])) largest = l;
	if(r < n && (order ? arr[r]< arr[largest] : arr[r] > arr[largest])) largest = r;
	if(largest != i)
	{
		swap(arr[i], arr[largest]);
		//recursively heapify the affected subtree
		heapify(arr, n, largest, order);
	}
}	


void heapSort(int arr[], int n, float order)
{
	//building heap
	for(int i = n / 2 - 1; i >= 0; i--) 
	{
		heapify(arr, n, i, order);	
		loopEnteredHeap++;
	}
	
	//extract elements from the heap one by one
	for(int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]); // swapping root with the leaf node
		heapify(arr, i, 0, order); // call max heapify on the reduced heap	
		loopEnteredHeap++;

	}	
}	
int main()
{
	int arr[] =  {2,3,4,5,6,7,8,9,15};
	
	int size_arr = sizeof(arr) / sizeof(int);
	
	mergeSort(arr, 0, size_arr - 1, 1);
	quickSort(arr, 0, size_arr - 1, 1);
	heapSort(arr, size_arr, 0);
	cout<<"When sorted in the descending order:"<<endl<<endl;
	cout<<"Loops were used "<< loopEnteredMerge<<" times for the merge sort."<<endl;
	cout<<"Loops were used "<< loopEnteredQuick<<" times for the quick sort."<<endl;
	cout<<"Loops were used "<< loopEnteredHeap<<" times for the heap sort."<<endl<<endl;
	cout<<"--------------------------------"<<endl<<endl;
	
	loopEnteredMerge = 0;
	loopEnteredQuick = 0;
	loopEnteredHeap = 0;
	
	mergeSort(arr, 0, size_arr - 1, 0);
	quickSort(arr, 0, size_arr - 1, 0);
	heapSort(arr, size_arr, 0);
	cout<<"When sorted in the ascending order:"<<endl<<endl;
	cout<<"Loops were used "<< loopEnteredMerge<<" times for the merge sort."<<endl;
	cout<<"Loops were used "<< loopEnteredQuick<<" times for the quick sort."<<endl;
	cout<<"Loops were used "<< loopEnteredHeap<<" times for the heap sort."<<endl;
	
	return 0;
}
