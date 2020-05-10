
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#define TRUE 1
#define FALSE 0
using namespace std;

struct student //student database
{
	int key;
	int prn;
	char name[20];
	char branch[10];
	double year;
};

class Node 
{
  public:
  int key;
  int prn;
  char name[20];
  char branch[10];
  double year;
  Node *prev, *next;
  Node(int k, int p, char n[20], char b[20], double y) 
  	{
  		key=k;
		prn=p;
		strcpy(name,n);
		strcpy(branch,b);
		year=y;
   		prev=NULL;
   		next=NULL;
	}
};

class DoublyLinkedList 
{
  Node *front, *rear;
  int isEmpty() 
  {
      if(front==NULL)
	  return TRUE;
	  else
	  return FALSE;
  }
  public:
  DoublyLinkedList()
  {
   front=NULL;
   rear=NULL; 
  }
  Node* addtohead(int key, int prn, char name[20], char branch[20], double year) 
  {
      Node *page=new Node(key, prn, name, branch, year);
      if(!front && !rear) 
      {
          front=rear=page;
      }
      else 
	  {
          rear->next=page;
          page->prev=rear;
          rear=page;
      }
      return page;
  }
  void movetohead(Node *page) 
  {
      Node *temp=NULL, *temp1=NULL;
	  if(page==rear) 
	  {
          return;
      }
      if(page==front) 
	  {
          front=page->next;
          rear->next=page;
          page->prev=rear;
          rear=rear->next;
          front->prev=NULL;
          rear->next=NULL;
      }
      else 
	  {
          page->prev=temp;
          page->next=temp1;
          rear->next=page;
          page->prev=rear;
          rear=rear->next;
          temp->next=temp1;
          temp1->prev=temp;
          rear->next=NULL;
      }
  }
  void removefront()
  {
      if(isEmpty()) 
	  {
          return;
      }
      if(front==rear) 
	  {
          delete front;
          front=rear=NULL;
      }
      else 
	  {
          Node *temp=front;
          front=front->next;
          front->prev=NULL;
          delete temp;
      }
  }
  Node* getfront()
  {
      return front;
  }
};

class LRUCache
{
  int capacity, size;
  DoublyLinkedList *pageList;
  map<int, Node*> pageMap;
  public:
    LRUCache(int capacity) 
	{
      this->capacity=capacity;
      size=0;
      pageList=new DoublyLinkedList();
      pageMap=map<int, Node*>();
    }
	void get(int key) 
	{
      char n[20],b[20];
	  if(pageMap.find(key)==pageMap.end()) 
	   {
          cout<<"\nThis data is not present in the cache memory.";
       }
       else
       {
    	  int p=pageMap[key]->prn;
      	  strcpy(n,pageMap[key]->name);
      	  strcpy(b,pageMap[key]->branch);
      	  double y=pageMap[key]->year;
      	  pageList->movetohead(pageMap[key]);
      	  cout<<"\nPRN:"<<p<<"\nName:"<<n<<"\nBranch:"<<b<<"\nBatch:"<<y;
       }
    }
	void put(int key, int prn, char name[20], char branch[20], double year) 
	{
      if(pageMap.find(key)!=pageMap.end()) 
	  {
          pageMap[key]->prn=prn;
          strcpy(pageMap[key]->name,name);
          strcpy(pageMap[key]->branch,branch);
          pageMap[key]->year=year;
          pageList->movetohead(pageMap[key]);
          return;
      }
	  if(size==capacity) 
	  {
          int k=pageList->getfront()->key;
          pageMap.erase(k);
          pageList->removefront();
          size--;
      }
	  Node *page=pageList->addtohead(key,prn,name,branch,year);
      size++;
      pageMap[key]=page;
    }
};

int main() 
{
  int size, choice, n=-1, menu, k, c;
  student s[20];
  cout<<"\nInput the size of the cache memory:";
  cin>>size;
  LRUCache cache(size); 
  do{
  cout<<endl;
  cout<<"|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|";
  cout<<"\n1.Store data into Cache \n2.Retrieve data from Cache";
  cout<<"\nInput your choice:";
  cin>>choice;
  switch(choice)
  {
  	case 1: cout<<"\nSTORE";
  			n++;
  			cout<<"\nInput the student's following details to be stored in cache memory:";
  			cout<<"\nInput PRN:";
  			cin>>s[n].prn;
  			cout<<"Input Name:";
  			cin>>s[n].name;
  			cout<<"Input Branch:";
  			cin>>s[n].branch;
  			cout<<"Input Batch:";
  			cin>>s[n].year;
  			cout<<"Input key at which the data should be stored:";
  			cin>>s[n].key;
  			cache.put(s[n].key, s[n].prn, s[n].name, s[n].branch, s[n].year);
  			break;
  	case 2: cout<<"\nRETRIEVE";
  			cout<<"\nInput the key of the data you want to retrieve:";
  			cin>>k;
  			cache.get(k);
  			break;
  }
  cout<<"\nDo you want to continue? (1-YES 0-NO)  :";
  cin>>menu;
 }while(menu==1);
  return 0; 	
}
