#include <iostream>
using namespace std;

class list
{
    int data;
    list *next;

    public:
    list(){};
    void ekle(int);
    void sil(int);
    int say();
    void listele();
};
list *head;

void list::ekle(int sayi){
    list *newlist = new list;
    newlist->data = sayi;
    newlist->next = 0;
    list *p = head; //listede dolamak icin headi gosteren bi pointer
    if(p==0){
        head = newlist;
    }
    else{
        while(p -> next != 0)
            p = p ->next;
        p -> next = newlist; //en sona gelince elemani ekler
    }
}

void list::sil(int x){
    list *p = head; //headi tutacak pointer
    list *temp = p; //daha sonra kodda gerektigi durumda p'nin bir onceki elemanin tutacak pointer

    if(p == 0){
        cout<<"List is empty!";
    } //listenin bos oldugu durum
    
    else if (p-> next == 0 && p -> data == x){
        delete p;
        head = 0;
    } //bir tane elemanin silidigi durum
   
    else if(p == head && p -> data == x){
        head = p-> next;
        delete p;
    } //silinecek eleman ilk degere esitse
    
    else {
         p = p-> next;
        while(p)// listenin sonuna kadar
        {
            if(p -> data == x){
                
                temp -> next  = p -> next; 
                break; //elemani bulduysan bir onceki elemanin nextine pnin nextini ata
            }       

           p = p->next; //elemani bir oynat
           temp = temp ->next;   //bir onceki elemani bir oynat   

        } 
        if(p == 0)
            cout<<"aradiginiz eleman listede yok"<<endl:
        else
            delete p; //p'yi sil
    }
}

int list::say(){
    int x;
    list *p = head;
    while(p){
        p = p->next;
        x++;
    }
    return x;
}

void list::listele(){
    list *p = head;
    int i = 1;
    if(p == 0)
        cout<<"liste bos";
    
    else{
        while(p){
        cout<< i <<". deger = "<< p -> data<<endl;
        p = p -> next;
        i++;
    }   
    }
    
}




int main(){
    
    list a ; //list class olustur
    char ch;
    int b;
    
    while(1)
    {
        cout<<"********************************"<<endl<<"Eklemek icin  ---->E"<<endl<<"Silmek icin ------>S"<<endl<<"Saymak icin ------>Y"<<endl<<"Listelemek icin -->L"<<endl
        <<"Cikis icin ------->C"<<endl<<"********************************"<<endl<<endl;
        cin>>ch;

        switch (ch)
        {
        case 'E':
            cin>>b;
            a.ekle(b);
            break;
        
        case 'S':
            cin>>b;
            a.sil(b);
            break;
        
        case 'Y':
            cout<<a.say();
            break;
        
        case 'L':
            a.listele();
            break;            
        
        case 'C':
            break;

        default:
            cout<<"Gecerli bir secim yapiniz.";
            break;
        }}
      
      system("PAUSE");
      return 0;  
    }
 
