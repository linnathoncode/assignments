#include <iostream>
using namespace std;

class list
{
    char data;
    list *next;
	list *last;
	
    public:
    list(){};
    void ekle(int);
    void listele();
    void askerSec(int, int);
	int say();
        
};

list *head = 0;

void list::ekle(int askerSayisi ){
    
	if(askerSayisi< 1 || askerSayisi > 25)cout<<"Asker Sayisi 1 ile 10 arasinda olmalidir."<<endl;

	else{
		
		last = 0; // son elemanin pointerini null yapar
		
		for(int i = 0; i < askerSayisi; i++){
	
			list *newlist = new list;
			newlist->data = char(65 + i);
		    newlist->next = 0;
		    list *p = head; //listede dolasmak icin headi gosteren bi pointer
			
			if(p==0){
				head = newlist;
		    	last = newlist;
			}
		    else{
		    	last ->next = newlist; //yeni nodeu listenin sonuna ekleme
		    	last = newlist; //last nodeu guncelleme
		    	last -> next = head; // son elemani basa pointleme
				        
		    }
		}
		
	}  
	
}

void list::listele(){
    list *p = head;
    if(p == 0)cout<<"liste bos";
    
    else{
        do{
        cout<<p -> data<<" ";
        p = p -> next;
    	} while(p != head); //heade ulasana kadar tum listeyi yazar  
    }
    
}

void list::askerSec(int n, int askerSayisi){
	list *seciliAsker = head;
	list *prev = head;
	list *silinecekAsker;
	
	
	
	cout<<"liste: ";
	listele();
	cout<<endl;
	
	for(int j=0; j < askerSayisi - 1; j++){
		for(int i = 0; i < n - 1; i++){
			
			prev = seciliAsker;
			seciliAsker = seciliAsker ->next;
		} 
		silinecekAsker = seciliAsker;
		prev -> next = seciliAsker ->next;   //silinen nodeun nextini bir onceki nodeun nexti yapar
		seciliAsker = seciliAsker -> next;	//seciliAskeri bir sonraki node yapar
		
		cout<<"Cikarilan asker:"<< silinecekAsker -> data<<endl;
			
	}
	
	delete silinecekAsker;	
	cout<<"Gorev icin secilen asker: "<< prev->data<<endl; 	

}



int main(){
	list a;
	int askerSayisi;
	int n;	
	
	cout<<"Asker sayisi giriniz. (1 - 25 arasi) "<<endl;
	cin>>askerSayisi;
	cout<<"N degerini giriniz. "<<endl;
	cin>>n;
	
	a.ekle(askerSayisi);
	a.askerSec(n, askerSayisi);	
	
}
