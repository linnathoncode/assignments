#include <iostream>

using namespace std;

class node{
	public:
		int data;
		int priority;
		node *next;
};



class priority_list{

	private:
		node *head = 0;

	public:
		
		void queue(int, int);
		void dequeue(int);
		void list();
};

// listeye oncelige bagli ekleme
void priority_list::queue(int data, int priority){
	
	node *newnode = new node;  //nodea degerleri atama
 	newnode -> data = data;
	newnode -> priority = priority;
	
	node *p = head;  //listenin basina pointer atama
	
	if(head == 0 || priority < head ->priority){
		newnode -> next = head;  //liste bossa veya eklenecek nodeun onceligi listenin basindan yuksekse
		head = newnode;          //yeni node listenenin basi olur 
	}
	else{
		while(p -> next && priority >= p -> next -> priority){ //yeni nodedan dusuk bir onceligi bulana kadar listede dolasir
			p = p -> next;										//listenin sonuna gelirse durur
		}
		newnode -> next = p ->next;   //buldugu yere yeni nodeu yerlestirir
		p -> next = newnode;
	}
	
}

void priority_list::dequeue(int priority){
	
	node *p = head;
	node *prev = 0;
	
	while(p){
		if(p -> priority == priority){  //silinmek istenen oncelik degerini bulduysa ondan once bir deger var mi diye bakar
			if(prev) prev -> next = p ->next; //eger varsa onun nextini silinecek degerin nexti yapar
			else head = p -> next;				//silinecek degerden once bir eleman yoksa, silinecek deger listenin basidir
			delete p;							//listenin basini silinecek elemanin nextini yapar
			return;
		}
		else{         //silinmek istenen oncelik degerini bulamadiysa pointerlari listede bi ilerletir
			prev = p;
			p = p -> next;
		}
	}
		
}

void priority_list::list(){
	
	node *p = head;
	int i = 1;
	
	if(!p) cout<< "Liste Bos! "<<endl;
	
	else{
		while(p){
			cout<<i<<". Eleman = "<<p->data<<", Onceligi = "<< p->priority<<endl;
			p = p -> next;
			i++;
		}
	}
	cout<<endl;
}



int main(){
	priority_list a;
	
	char ch;
    int data, priority;

    while (true) {
        cout << "********************************" << endl
             << "Eklemek icin  ----> E" << endl
             << "Silmek icin ------> S" << endl
             << "Listelemek icin --> L" << endl
             << "Cikis icin ------> C" << endl
             << "********************************" << endl << endl;
        cin >> ch;

        if (ch == 'C') break;

        switch (ch) {
            case 'E':
                cout << "Eklemek istediginiz veriyi giriniz (Sayi):" << endl;
                cin >> data;
                cout << "Eklemek istediginiz verinin onceligini giriniz:"<<endl;
                cin >> priority;
                a.queue(data, priority);
                break;

            case 'S':
                cout << "Silmek istediginiz onceligi giriniz:" << endl;
                cin >> priority;
                a.dequeue(priority);
                break;		

            case 'L':
                a.list();
                break;

            default:
                cout << "Lutfen menudeki secenekleri seciniz." << endl << endl;
        }
    }

    return 0;
	
}
