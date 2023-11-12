#include <iostream>
#include <string>
#include <queue>
#include <map>

using namespace std;

class Node {
public:
    Node* left;
    Node* right;
    char data;
    int freq;
    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

struct NodeCompare {
    bool operator()(Node* a, Node* b) {
        return (a->freq > b->freq);
    }
};

class HuffmannTree {
	private:
	    Node* root;
	
	public:
	    HuffmannTree() : root(nullptr) {}
	    	void createHuffmannTree(const string& text) {
	    priority_queue<Node*, vector<Node*>, NodeCompare> pq;
	    map<char, int> charFreqMap;
	
	    // Calculate characters' frequency
	    for (char c : text) {
	        charFreqMap[c]++;
	    }
	
	    // Create nodes for each character and frequency, and push them into the queue
	    for (const auto& entry : charFreqMap) {
	        Node* newNode = new Node(entry.first, entry.second);
	        pq.push(newNode);
	    }
	
	    // Build Huffman tree and populate Huffman codes
	    while (pq.size() > 1) {
	        Node* left = pq.top();
	        pq.pop();
	        Node* right = pq.top();
	        pq.pop();
	
	        Node* mergedNode = new Node('$', left->freq + right->freq);
	        mergedNode->left = left;
	        mergedNode->right = right;
	        pq.push(mergedNode);
	    }
	    root = pq.top();
	
		}
	
		void printHuffmannCodes(Node* root, string code, map<char, string>& huffmannCodes) {
		if (root == nullptr) {
		    return;
		}
		
		// Character leaf node
		// Print the character and its code
		if (root->data != '$') {
		    huffmannCodes[root->data] = code;
		    cout << "'" << root->data << "' " << code << endl;
		}
		
		printHuffmannCodes(root->left, code + "0", huffmannCodes);
		printHuffmannCodes(root->right, code + "1", huffmannCodes);
		}
		
		
		
		// Encode a message using Huffman codes
		string encodeMessage(const string& message, const map<char, string> huffmannCodes) {
		string encodedMessage;
		for (char c : message) {
		    if (huffmannCodes.find(c) != huffmannCodes.end()) {
		        encodedMessage += huffmannCodes.at(c);
		    }
		}
		return encodedMessage;
		}
		
		string decodeMessage(const string& encodedMessage) {
		    
			string decodedMessage;
		    Node* current = root;  // Start at the root of the Huffman tree
		
		    for (char bit : encodedMessage) {
		        if (bit == '0') {
		            current = current->left;
		        } else if (bit == '1') {
		            current = current->right;
		        }
		
		        // If we reach a leaf node, add the character to the decoded message and reset to the root
		        if (current->left == nullptr && current->right == nullptr) {
		            decodedMessage += current->data;
		            current = root;
		        }
		    }
		
		    return decodedMessage;
		}
		
		Node* getRoot() { return root; }
	};


int main() {
    string text;
    cout<<"Enter a text to be encoded: ";
    cin>>text;
    HuffmannTree huffmannTree;
    huffmannTree.createHuffmannTree(text);

    map<char, string> huffmannCodes;
    
    huffmannTree.printHuffmannCodes(huffmannTree.getRoot(), "", huffmannCodes);
    cout << "---------------------------" << endl;

    string encodedMessage = huffmannTree.encodeMessage(text, huffmannCodes);

    cout << "Original Message: " << text << endl;
    cout << "Encoded Message: " << encodedMessage << endl; // Print the encoded message
    
    string decodedMessage = huffmannTree.decodeMessage(encodedMessage);
	cout << "Decoded Message: " << decodedMessage << endl;	// Print the decoded message

    return 0;
}

