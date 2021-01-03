# include <iostream>
# include <iomanip>
# include <string>
# include <math.h>
# include <fstream>
# include <bits/stdc++.h> 
# include <time.h>

using namespace std;

#define ALPHABET_SIZE (26) 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 

string history_stack[100];
int top=-1;

struct Node 
{ 
    string eng;
	string fre; 
    struct Node* next; 
}; 

class node 
{
public:
	string data;
	string syn;
	node *parent;
	node *leftChild;
	node *rightChild;

	node()
	{
		data = '0';
		syn = '0';
		parent = NULL;
		leftChild = NULL;
		rightChild = NULL;
	}
	
};

class bst 
{
	
public:
	node* root;

	bst()
	{
	 root = NULL; 
	 }
	void insert(string data, string);
	void display(node*, int);
	node* search1(string data);
	node* search2(string syn);
	void deletion(node *z);
	void transplant(node* u, node* v);
	node* successor(node* currentNode);

};

void bst::insert(string data, string syn)
{
	node* newNode = new node();
	newNode->data = data;
	newNode->syn = syn;
	if (root == NULL)
	{
		root = newNode;
	}
	else
	{
		node* tempNode = new node();
		node* backTempNode = new node();
		tempNode = root;

		while (tempNode != NULL)
		{
			backTempNode = tempNode;
			if (tempNode->data <= newNode->data)
			{
				tempNode = tempNode->rightChild;
			}
			else
			{
				tempNode = tempNode->leftChild;
			}
		}

		newNode->parent = backTempNode;
		if (backTempNode->data <= newNode->data)
		{
			backTempNode->rightChild = newNode;
		}
		else
		{
			backTempNode->leftChild = newNode;
		}
	}
}

void bst::display(node *Node, int level)
{
	if (root == NULL)
	{
		cout << "Dictionary is empty." << endl;
	}
	else
	{
		if (Node->rightChild != NULL)
		{
			display(Node->rightChild, level + 1);
		}

		if (Node != root)
		{
			for (int i = 0; i < level + 1; i++)
			{
				cout << "      ";
			}
		}
		else
		{
			cout << "Root->";
		}

		cout << Node->data << ":" << Node->syn << endl;

		if (Node->leftChild != NULL)
		{
			display(Node->leftChild, level + 1);
		}
	}

}

node* bst::search1(string Data)
{
	node* tempNode = new node();
	tempNode = root;
	while (tempNode != NULL)
	{
		if (tempNode->data == Data)
		{
			return tempNode;
		}
		else
		{
			if (tempNode->data <= Data)
			{
				tempNode = tempNode->rightChild;
			}
			else
			{
				tempNode = tempNode->leftChild;
			}
		}
	}
	return NULL;
}

node* bst::search2(string syn)
{
	node* tempNode = new node();
	tempNode = root;
	while (tempNode != NULL)
	{
		if (tempNode->syn == syn)
		{
			return tempNode;
		}
		else
		{
			if (tempNode->syn <= syn)
			{
				tempNode = tempNode->rightChild;
			}
			else
			{
				tempNode = tempNode->leftChild;
			}
		}
	}
	return NULL;
}


node* bst::successor(node* currentNode)
{
	node* tempNode = new node();
	node* backTempNode = new node();
	tempNode = currentNode;

	if (tempNode->rightChild != NULL)
	{
		tempNode = tempNode->rightChild;
		while (tempNode != NULL)
		{
			backTempNode = tempNode;
			tempNode = tempNode->leftChild;
		}
		return backTempNode;
	}
	else
	{
		backTempNode = tempNode;
		tempNode = tempNode->parent;
		while (tempNode != NULL && tempNode->rightChild == backTempNode)
		{
			backTempNode = tempNode;
			tempNode = tempNode->parent;
		}
		return tempNode;
	}
}


void bst::transplant(node* u, node* v)
{
	if (u->parent == NULL)
	{
		root = v;
	}
	else
	{
		if (u == u->parent->leftChild)
		{
			u->parent->leftChild = v;
		}
		else
		{
			u->parent->rightChild = v;
		}
	}
	if (v != NULL)
	{
		v->parent = u->parent;
	}
}


void bst::deletion(node *z)
{
	if (z->leftChild == NULL)
	{
		transplant(z, z->rightChild);
	}
	else
	{
		if (z->rightChild == NULL)
		{
			transplant(z, z->leftChild);
		}
		else
		{
			node* succesor = new node();
			succesor = successor(z);
			if (succesor->parent != z)
			{
				transplant(succesor, succesor->rightChild);
				succesor->rightChild = z->rightChild;
				succesor->rightChild->parent = succesor;
			}
			transplant(z, succesor);
			succesor->leftChild = z->leftChild;
			succesor->leftChild->parent = succesor;
		}
	}
	delete z;
}

struct TrieNode 
{ 
	struct TrieNode *children[ALPHABET_SIZE]; 
	bool isWordEnd; 
}; 

struct TrieNode *getNode(void) 
{ 
	struct TrieNode *pNode = new TrieNode; 
	pNode->isWordEnd = false; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
		pNode->children[i] = NULL; 

	return pNode; 
} 
 
void insert(struct TrieNode *root, const string key) 
{ 
	struct TrieNode *pCrawl = root; 

	for (int level = 0; level < key.length(); level++) 
	{ 
		int index = CHAR_TO_INDEX(key[level]); 
		if (!pCrawl->children[index]) 
			pCrawl->children[index] = getNode(); 

		pCrawl = pCrawl->children[index]; 
	} 
	
	pCrawl->isWordEnd = true; 
} 
 
bool search(struct TrieNode *root, const string key) 
{ 
	int length = key.length(); 
	struct TrieNode *pCrawl = root; 
	for (int level = 0; level < length; level++) 
	{ 
		int index = CHAR_TO_INDEX(key[level]); 

		if (!pCrawl->children[index]) 
			return false; 

		pCrawl = pCrawl->children[index]; 
	} 

	return (pCrawl != NULL && pCrawl->isWordEnd); 
} 
 
bool isLastNode(struct TrieNode* root) 
{ 
	for (int i = 0; i < ALPHABET_SIZE; i++) 
		if (root->children[i]) 
			return 0; 
	return 1; 
} 
 
void suggestionsRec(struct TrieNode* root, string currPrefix) 
{ 
	if (root->isWordEnd) 
	{ 
		cout << currPrefix; 
		cout << endl; 
	}
	
	if (isLastNode(root)) 
		return; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
	{ 
		if (root->children[i]) 
		{ 

			currPrefix.push_back(97 + i); 
			
			suggestionsRec(root->children[i], currPrefix); 
		} 
	} 
} 

int printAutoSuggestions(TrieNode* root, const string query) 
{ 
	struct TrieNode* pCrawl = root; 

	int level; 
	int n = query.length(); 
	for (level = 0; level < n; level++) 
	{ 
		int index = CHAR_TO_INDEX(query[level]); 

		if (!pCrawl->children[index]) 
			return 0; 

		pCrawl = pCrawl->children[index]; 
	} 
	 
	bool isWord = (pCrawl->isWordEnd == true); 


	bool isLast = isLastNode(pCrawl); 
	
	if (isWord && isLast) 
	{ 
		cout << query << endl; 
		return -1; 
	}  
	if (!isLast) 
	{ 
		string prefix = query; 
		suggestionsRec(pCrawl, prefix); 
		return 1; 
	} 
}

struct TrieNode2 
{ 
	struct TrieNode2 *children[ALPHABET_SIZE]; 
	bool isWordEnd; 
}; 

struct TrieNode2 *getNode2(void) 
{ 
	struct TrieNode2 *pNode = new TrieNode2; 
	pNode->isWordEnd = false; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
		pNode->children[i] = NULL; 

	return pNode; 
} 
 
void insert2(struct TrieNode2 *root, const string key) 
{ 
	struct TrieNode2 *pCrawl = root; 

	for (int level = 0; level < key.length(); level++) 
	{ 
		int index = CHAR_TO_INDEX(key[level]); 
		if (!pCrawl->children[index]) 
			pCrawl->children[index] = getNode2(); 

		pCrawl = pCrawl->children[index]; 
	} 
	
	pCrawl->isWordEnd = true; 
} 
 
bool search2(struct TrieNode2 *root, const string key) 
{ 
	int length = key.length(); 
	struct TrieNode2 *pCrawl = root; 
	for (int level = 0; level < length; level++) 
	{ 
		int index = CHAR_TO_INDEX(key[level]); 

		if (!pCrawl->children[index]) 
			return false; 

		pCrawl = pCrawl->children[index]; 
	} 

	return (pCrawl != NULL && pCrawl->isWordEnd); 
} 
 
bool isLastNode2(struct TrieNode2* root) 
{ 
	for (int i = 0; i < ALPHABET_SIZE; i++) 
		if (root->children[i]) 
			return 0; 
	return 1; 
} 
 
void suggestionsRec2(struct TrieNode2* root, string currPrefix) 
{ 
	if (root->isWordEnd) 
	{ 
		cout << currPrefix; 
		cout << endl; 
	}
	
	if (isLastNode2(root)) 
		return; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
	{ 
		if (root->children[i]) 
		{ 

			currPrefix.push_back(97 + i); 
			
			suggestionsRec2(root->children[i], currPrefix); 
		} 
	} 
} 

int printAutoSuggestions2(TrieNode2* root, const string query) 
{ 
	struct TrieNode2* pCrawl = root; 

	int level; 
	int n = query.length(); 
	for (level = 0; level < n; level++) 
	{ 
		int index = CHAR_TO_INDEX(query[level]); 

		if (!pCrawl->children[index]) 
			return 0; 

		pCrawl = pCrawl->children[index]; 
	} 
	 
	bool isWord = (pCrawl->isWordEnd == true); 


	bool isLast = isLastNode2(pCrawl); 
	
	if (isWord && isLast) 
	{ 
		cout << query << endl; 
		return -1; 
	}  
	if (!isLast) 
	{ 
		string prefix = query; 
		suggestionsRec2(pCrawl, prefix); 
		return 1; 
	} 
}

void push(string word)
{
  history_stack[++top].assign(word);
}

void display()
{
	cout<<top<<endl;
	if(top==-1)
		printf("No elements have been searched");
	else
	{
		printf("Your search history is:\n");
		for(int i=0;i<=top;i++)
			cout<<history_stack[i]<<endl;
	}
}

void count()
{
	string tem[100],tem1[100],w,x;
	int i,j,k=0,flag=0,coun=0;
	for(i=0;i<=top;i++)
		tem[i]=history_stack[i];
	for(i=0;i<=top;i++)
	{
		flag=0;
		w=tem[i];
		for(j=0;j<i;j++)
		{
			x=tem[j];
			if(w.compare(x)==0)
				flag=1;
		}
		if(flag==0)
		{
			tem1[k++]=w;
		}
	}
	printf("Search Frequency is:\n");
	printf("Word\t\tCount\n");
	for(i=0;i<k;i++)
	{
		coun=0;
		w=tem1[i];
		for(j=0;j<=top;j++)
		{
			x=tem[j];
			if(w.compare(x)==0)
			{
				coun++;
			}
		}
		cout<<w<<"\t\t"<<coun<<endl;
	}
}

void printRandom(struct Node *head) 
{ 
    if (head == NULL) 
       return; 
  
    srand(time(NULL)); 
  
    string result = head->eng; 
    string result2 = head->fre;
  
    struct Node *current = head; 
    int n; 
    for (n=2; current!=NULL; n++) 
    { 
        if (rand() % n == 0) 
        {
           result.assign(current->eng);
           result2.assign(current->fre);
  		}
        // Move to next node 
        current = current->next; 
    } 
  
    cout<<result<<"\t"<<result2<<endl; 
} 
  

struct Node *newNode(string en,string fr) 
{ 

    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
  
    new_node->eng.assign(en); 
    new_node->fre.assign(fr);
    
    new_node->next =  NULL; 
  
    return new_node; 
} 
  
void ins_list(struct Node** head_ref, string en,string fr) 
{ 
    struct Node* new_node = new Node(); 
    
    new_node->eng.assign(en); 
    new_node->fre.assign(fr);
    
	new_node->next = (*head_ref); 
  
    (*head_ref) = new_node; 
}

string getString(char x) 
{ 
    string s(1, x); 
    return s;    
} 

void menu()
{
	char ch;
	string inttemp;
	string p;
	node *temp = new node();
	struct Node *head = NULL; 
	bst myTree;
	int select;
	struct TrieNode* root = getNode();
	struct TrieNode2* root2 = getNode2();
	fstream newfile;
	newfile.open("words.txt",ios::in); //open a file to perform read operation using file object
    if (newfile.is_open())
	{   //checking whether the file is open
        string tp[2];
        int i=0;
        while(getline(newfile, tp[(i++)%2])){ //read data from file object and put it into string.
            if(i%2==0)
            {
            	myTree.insert(tp[0],tp[1]);
				insert(root,tp[0]);
				insert2(root2,tp[1]);
				ins_list(&head,tp[0],tp[1]);
        	}
		}
        newfile.close(); //close the file object.
    }
	do
	{
		cout<<endl<<endl<<"\t\t\t\tTRANSLATOR"<<endl<<endl;
		cout << "0. Exit" << endl;
		cout << "1. Insert" << endl;
		cout << "2. Display" << endl;
		cout << "3. English Search" << endl;
		cout << "4. French Search" << endl;
		cout << "5. Delete" << endl;
		cout << "6. Search words under given prefix(ENG)" << endl;
		cout << "7. Search words under given prefix(FRE)" << endl;
		cout << "8. Display Search History" << endl;
		cout << "9. Random Word of the day" << endl;
		cout << "10. Index(ENG)"<<endl;
		cout << "11. Index(FRE)"<<endl;
		cout << endl << "Enter your selection:" << endl;
	
		cin >> select;

		switch (select)
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			do
			{ 
				string data;
				string syn;
				cout << "Enter the word (English,French meaning): ";
				cin >> data >> syn;
				myTree.insert(data, syn);
				insert(root,data);
				ins_list(&head,data,syn);
				cout << endl << "Do you want another word? [y or n]" << endl;
				cin >> ch;
			} while (ch != 'n');
			break;
		}
		case 2:
		{
			myTree.display(myTree.root, 0);
			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		case 3:
		{
			cout << "Enter English word:";
			cin >> inttemp;
			push(inttemp);
			temp = myTree.search1(inttemp);
			if (temp != NULL)
			{
				cout << temp->data << ": " << temp->syn << endl;
			}
			else
			{
				cout << "It isn't in Dictionary!" << endl;
			}

			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		case 4:
		{
			cout << "Enter French word:";
			cin >> p;
			push(p);
			temp = myTree.search2(p);
			if (temp != NULL)
			{
				cout << temp->syn << ": " << temp->data << endl;
			}
			else
			{
				cout << "It isn't in Dictionary!" << endl;
			}

			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		case 5:
		{
			cout << "Enter the word that you want delete: ";
			cin >> inttemp;
			temp = myTree.search1(inttemp);
			if (temp == NULL)
			{
				cout << inttemp << " isn't in Dictionary" << endl;
			}
			else
			{
				myTree.deletion(temp);
				cout << inttemp << " removed from Dictionary." << endl;
			}
			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		case 6:
		{
			string pre;
			cout<<"Enter the prefix(ENG): ";
			cin>>pre;
			int comp = printAutoSuggestions(root, pre); 
			if (comp == -1) 
				cout << "No other strings found with this prefix\n"; 
			
			else if (comp == 0) 
				cout << "No string found with this prefix\n"; 

			break;
		}
		case 7:
		{
			string pre;
			cout<<"Enter the prefix(FRE): ";
			cin>>pre;
			int comp = printAutoSuggestions2(root2, pre); 
			if (comp == -1) 
				cout << "No other strings found with this prefix\n"; 
			
			else if (comp == 0) 
				cout << "No string found with this prefix\n"; 

			break;
		}
		case 8:
		{
			display();
			count();
			break;
		}
		case 9:
		{
			cout<<"\t\t\tWORD OF THE DAY"<<endl;;
			cout<<"ENG\t\tFRE"<<endl;
			printRandom(head);
			break;
		}
		case 10:
		{
			int cho;
			
			cout<<"Display English words starting with: "<<endl;
			cout<<"1.\ta"<<endl;
			cout<<"2.\tb"<<endl;
			cout<<"3.\tc"<<endl;
			cout<<"4.\td"<<endl;
			cout<<"5.\te"<<endl;
			cout<<"6.\tf"<<endl;
			cout<<"7.\tg"<<endl;
			cout<<"8.\th"<<endl;
			cout<<"9.\ti"<<endl;
			cout<<"10.\tj"<<endl;
			cout<<"11.\tk"<<endl;
			cout<<"12.\tl"<<endl;
			cout<<"13.\tm"<<endl;
			cout<<"14.\tn"<<endl;
			cout<<"15.\to"<<endl;
			cout<<"16.\tp"<<endl;
			cout<<"17.\tq"<<endl;
			cout<<"18.\tr"<<endl;
			cout<<"19.\ts"<<endl;
			cout<<"20.\tt"<<endl;
			cout<<"21.\tu"<<endl;
			cout<<"22.\tv"<<endl;
			cout<<"23.\tw"<<endl;
			cout<<"24.\tx"<<endl;
			cout<<"25.\ty"<<endl;
			cout<<"26.\tz"<<endl;
			
			cout<<"Enter your choice: ";
			cin>>cho;
			
			if((cho>26)||(cho<=0))
			{
				cout<<"Invalid Input!"<<endl;
			}
			else
			{
				int comp = printAutoSuggestions(root, getString(cho+96)); 
				if (comp == -1) 
					cout << "No other strings found with this prefix\n"; 				
				else if (comp == 0) 
					cout << "No string found with this prefix\n"; 
			}
				
			break;
		}
		case 11:
		{
			int cho;
			
			cout<<"Display French words starting with: "<<endl;
			cout<<"1.\ta"<<endl;
			cout<<"2.\tb"<<endl;
			cout<<"3.\tc"<<endl;
			cout<<"4.\td"<<endl;
			cout<<"5.\te"<<endl;
			cout<<"6.\tf"<<endl;
			cout<<"7.\tg"<<endl;
			cout<<"8.\th"<<endl;
			cout<<"9.\ti"<<endl;
			cout<<"10.\tj"<<endl;
			cout<<"11.\tk"<<endl;
			cout<<"12.\tl"<<endl;
			cout<<"13.\tm"<<endl;
			cout<<"14.\tn"<<endl;
			cout<<"15.\to"<<endl;
			cout<<"16.\tp"<<endl;
			cout<<"17.\tq"<<endl;
			cout<<"18.\tr"<<endl;
			cout<<"19.\ts"<<endl;
			cout<<"20.\tt"<<endl;
			cout<<"21.\tu"<<endl;
			cout<<"22.\tv"<<endl;
			cout<<"23.\tw"<<endl;
			cout<<"24.\tx"<<endl;
			cout<<"25.\ty"<<endl;
			cout<<"26.\tz"<<endl;
			
			cout<<"Enter your choice: ";
			cin>>cho;
			
			if((cho>26)||(cho<=0))
			{
				cout<<"Invalid Input!"<<endl;
			}
			else
			{
				int comp = printAutoSuggestions2(root2, getString(cho+96)); 
				if (comp == -1) 
					cout << "No other strings found with this prefix\n"; 				
				else if (comp == 0) 
					cout << "No string found with this prefix\n"; 
			}
				
			break;
		}
		default:
			break;
		}

	} while (select != 0);
}



int main()
{

	menu();
	return 0;
}
