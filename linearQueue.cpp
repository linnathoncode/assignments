#include <iostream>
#include <stdio.h>
#define MAX 50
using namespace std;

int kuyruk[MAX];
int head = -1;
int tail = -1;


void push(){
	int number;
	printf("Kuyruga eklenecek sayiyi giriniz \n");
	scanf("%d", &number);
	
	//if queue is empty initialize it
	if(head == -1){
		head = 0;
		tail = 0;
		kuyruk[head] = number;
	}
	
	//overflow check
	else if(tail == MAX - 1){
		printf("Error: overflow \n");
		return;
	}
	
	//add 1 to the tail then add the number
	else{
		tail++;
		kuyruk[tail] = number;
	}
	printf("%d sayisini kuyruga eklediniz \n", number);
}

void pop(){
	
	//if queue is not initialized or empty return error
	if(head == -1 ||  head > tail){
		printf("Error: underflow \n");
		return;
	}
	
	//if there is one last queue member deinitialize the queue
	else if(head == tail){
		printf("%d sayisini kuyruktan cikardiniz \n", kuyruk[head]);
		head = -1;
		tail = -1;
	}
	
	//remove one from the queue
	else{
		printf("%d sayisini kuyruktan cikardiniz \n", kuyruk[head]);
		head++;
	}
	
}

//show the queue
void show(){
	printf("Kuyrukta bulunan elemanlar sirasiyla: \n");
	for(int i = head; i <= tail; i++){
		printf("%d ", kuyruk[i]);
	}
	printf("\n");
}

//exit
void exit(){
	return;
}

int main(){
	int secim;
	while(1){
		printf("\n");
		printf("1 - Eleman ekle \n");
		printf("2 - Eleman sil \n");
		printf("3 - Kuyrugu goster \n");
		printf("4 - Cik \n");
		printf("Seciminizi giriniz \n\n");
		scanf("%d", &secim);
		switch(secim){
			case 1:
				push();
			break;
			case 2:
				pop();
			break;
			case 3:
				show();
			break;
			case 4:
				exit();
			default:
				printf("Yanlis bir secim girdiniz. \n");
		}		
	}
}





