#include <iostream>
using namespace std;

class list {
private:
    int data;
    int priority;
    list* next;

public:
    list(int d, int p) : data(d), priority(p), next(nullptr) {}

    void ekle(int, int);
    void sil(int);
    void listele();
    int say();
};

list* head = nullptr;

void list::ekle(int sayi, int priority) {
    list* newlist = new list(sayi, priority);
    list* p = head;

    if (!p || priority < head->priority) {
        newlist->next = head;
        head = newlist;
    }
    else {
        while (p->next && p->next->priority <= priority) {
            p = p->next;
        }
        newlist->next = p->next;
        p->next = newlist;
    }
}

void list::sil(int priority) {
    list* p = head;
    list* prev = nullptr;

    while (p) {
        if (p->priority == priority) {
            if (prev) {
                prev->next = p->next;
            }
            else {
                head = p->next;
            }
            delete p;
            return;
        }
        prev = p;
        p = p->next;
    }
}

int list::say() {
    int x = 0;
    list* p = head;
    while (p) {
        p = p->next;
        x++;
    }
    return x;
}

void list::listele() {
    list* p = head;
    int i = 1;
    if (!p) {
        cout << "Liste bos" << endl;
    }
    else {
        while (p) {
            cout << i << "= oncelik: " << p->priority << ", veri: " << p->data << endl;
            p = p->next;
            i++;
        }
    }
}

int main() {
    list a(0, 0);
	char ch;
    int data, priority;

    while (true) {
        cout << "********************************" << endl
             << "Eklemek icin  ----> E" << endl
             << "Silmek icin ------> S" << endl
             << "Saymak icin ------> Y" << endl
             << "Listelemek icin --> L" << endl
             << "Cikis icin ------> C" << endl
             << "********************************" << endl << endl;
        cin >> ch;

        if (ch == 'C') break;

        switch (ch) {
            case 'E':
                cout << "Eklemek istediginiz veriyi giriniz (Sayi):" << endl;
                cin >> data;
                cout << "Eklemek istediginiz verinin onceligini giriniz"<<endl;
                cin >> priority;
                a.ekle(data, priority);
                break;

            case 'S':
                cout << "Silmek istediginiz onceligi giriniz:" << endl;
                cin >> priority;
                a.sil(priority);
                break;

            case 'Y':
                cout << "Kuyruktaki eleman sayisi: " << a.say() << endl << endl;
                break;

            case 'L':
                a.listele();
                break;

            default:
                cout << "Lutfen menudeki secenekleri seciniz." << endl << endl;
        }
    }

    return 0;
}
