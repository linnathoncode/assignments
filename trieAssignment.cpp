#include <iostream>
#define MAX_CHAR 26
using namespace std;

class trieNode
{
	public:
		char data;
		trieNode *children [MAX_CHAR];
		bool isEndOfWord;
		
		trieNode()
		{
			data = '\0';
			isEndOfWord = false;
			for(int i = 0; i< MAX_CHAR; i++) children[i] = '\0';
		}
};

class Trie
{	
	public:
		Trie()
		{ 
			root = new trieNode;
		}
		void insert(char word[MAX_CHAR]);	
		void remove(char word[MAX_CHAR]);
		bool search(char word[MAX_CHAR]);
		
	private:
		trieNode *root;	
			
};

void Trie::insert(char word[MAX_CHAR])
{
	trieNode * current = root;
	
	for(int i = 0; word[i] != '\0'; i++)
	{
		int index = word[i] - 'a';
		
		if(!current -> children[index])
		{
			current -> children[index]= new trieNode;
		}
		current = current-> children[index];
	}
	current -> isEndOfWord = true;	
}

void Trie::remove(char word[MAX_CHAR])
{	
	trieNode *current = root;
	int i = 0;
	
	// find the word
	while(word[i])
	{	int index = word[i] - 'a';
		current = current -> children[index];
		i++;
	}
	
	current -> isEndOfWord = false;
}

bool Trie::search(char word[MAX_CHAR])
{
	int i = 0;
	trieNode *current = root;

	
	while(word[i])
	{	
		int index = word[i] - 'a';
		if(!current -> children[index])
		{
			return false;
		}
		else
		{
			current = current ->children[index];
			i++;
		}
		
	}
	return current && current -> isEndOfWord; // returns true if only there is character
												// and its the last character of the given word

}

int main()
{
	Trie t;
	char word[MAX_CHAR];
	int menu;
		while(1){
			cout<<"1.Insert"<<endl;
			cout<<"2.Search"<<endl;
			cout<<"3.Remove"<<endl;
			cout<<"4.Exit"<<endl;
			cout<<"Do your selection:";
			cin>>menu;
			
			switch(menu)
			{
				case 1:
					cout<<"Enter a word to be inserted: ";
					cin>>word;
					t.insert(word);
					break;
				case 2:
					cout<<"Enter a word to be searched: ";
					cin>>word;
					if(t.search(word)) cout<<word<<" is in the dictionary."<<endl;
					else cout<<word<<" is not in the dictionary"<<endl;
					break;
				case 3:
					cout<<"Enter a word to be removed: ";
					cin>>word;
					if(!t.search(word)) cout<<word<<" is not in the dictionary."<<endl;
					else t.remove(word);
					break;
				case 4:
					exit(1);
				default:
					cout<<"Wrong Selection!"<<endl;	
			}
		}
	}
