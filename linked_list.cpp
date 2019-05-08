#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

/*
Michael Schultes
COP 3530 - Spring 2016
assign2.cpp
*/

struct node
{
    int info;
    struct node *next;
}*last;
 
class circular_llist
{
    public:
        void create_node(int value);
        void add_begin(int value);
        void add_after(int value, int position);
        void display_list();
        circular_llist()
        {
            last = NULL;           
        }
};

int main()
{
	circular_llist c1; // initialize list
	
    int n; // elements (initially)
	cin >> n;
	
	int * array = new int[n]; // cin from one line
	for (int i = 0; i < n; i++) {
		cin >> array[i];
	}
	
	c1.create_node(array[n-1]); // create the list
	
	for (int i = n-2; i > -1; i--) { // fill the list
		c1.add_begin(array[i]);
	}
	
	int m; // additional lists
	cin >> m;
	
	for (int i =0; i < m; i++) {
		int s; // steps
		cin >> s;
	
		int k; // elements
		cin >> k;

		for (int i = 0; i < k; i++) {
			cin >> array[i];
		}
	
		int position;
	
		for (int i = 0; i < k; i++) { // *** interleave algorithm  ***
			position = i + (i+1) * s;
			c1.add_after(array[i], position);
		}
	}

	c1.display_list(); // display list
	
    return 0;
}
 
/*
 * Create Linked List
 */
void circular_llist::create_node(int value)
{
    struct node *temp;
    temp = new(struct node);
    temp->info = value;
    if (last == NULL)
    {
        last = temp;
        temp->next = last;   
    }
    else
    {
        temp->next = last->next; 
        last->next = temp;
        last = temp;
    }
}
 
/*
 * Insertion of element at beginning 
 */
void circular_llist::add_begin(int value)
{
    if (last == NULL)
    {
        cout<<"First Create the list."<<endl;
        return;
    }
    struct node *temp;
    temp = new(struct node);
    temp->info = value;
    temp->next = last->next;
    last->next = temp;
}
 
/*
 * Insertion of element at a particular place 
 */
void circular_llist::add_after(int value, int pos)
{
    if (last == NULL)
    {
        cout<<"First Create the list."<<endl;
        return;
    }
    struct node *temp, *s;
    s = last->next;
    for (int i = 0;i < pos-1;i++)
    {
        s = s->next;
        if (s == last->next)
        {
            cout<<"There are less than ";
            cout<<pos<<" in the list"<<endl;
            return;
        }
    }
    temp = new(struct node);
    temp->next = s->next;
    temp->info = value;
    s->next = temp;
    /*Element inserted at the end*/
    if (s == last)
    { 
        last=temp;
    }
}
 
/*
 * Display Linked List 
 */
void circular_llist::display_list()
{
    struct node *s;
    if (last == NULL)
    {
        cout<<"List is empty, nothing to display"<<endl;
        return;
    }
    s = last->next;
    while (s != last)
    {
        cout<<s->info<<" ";
        s = s->next;
    }
    cout<<s->info<<endl;
}