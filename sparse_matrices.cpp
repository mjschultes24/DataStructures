#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

// Addition working, search function is not

template <class T>
struct node
{
    T info;
	int column;
    struct node<T> *next;
};

template <class T> 
class circular_llist
{
    public:
        void create_node();
        void add_begin(T value, int pos);
        void add_after(T value, int position);
        int search_element(T value);
        void display_list();
		int getter(int col);
		node<T> *last;
        circular_llist()
        {
            last = NULL;           
        }
};

template <class T>
class Matrix
{
	public:
		circular_llist<T> * array;
		int length;
		Matrix(int matrixSize);
		~Matrix();
		void print();
		void insert(int row, T value, int pos);
		int get_value(int r, int c);
		int search(int t, int rowss);
};

int size = 0;

int main()
{
	int rows = 0;
	int cols = 0;
	int term = 0;
	int colt = 0;
	int vale = 0;
	
	// User Interface
	cin >> rows;
	
	Matrix<int> matrixA(rows);
	Matrix<int> matrixB(rows);
	Matrix<int> matrixC(rows);
	
	for (int i = 0; i < rows; i++) {
		cin >> term;
		
		for (int j = 0; j < term; j++) {
			cin >> colt >> vale;
			matrixA.insert(i,vale,colt);
			
			if (colt > cols) {
				cols = colt;
			}
			
		}
	}
	
	cin >> rows;
	
	for (int i = 0; i < rows; i++) {
		cin >> term;
		
		for (int j = 0; j < term; j++) {
			cin >> colt >> vale;
			matrixB.insert(i,vale,colt);
			
			if (colt > cols) {
				cols = colt;
			}
			
		}
	}
	
	int a = 0;
	int b = 0;
	int sum = 0;
	
	// Add the two matrices
	for (int i = 0; i < rows; i ++) {
		
		for (int j = 0; j < cols; j++) {
			a = matrixA.get_value(i,j); 
			b = matrixB.get_value(i,j);
			sum = a + b;
			matrixC.insert(i,sum,j);
		}
	}
	
	// Searching the matrix C
	int searchX = 0;
	int element = 0;
	cin >> searchX;
	
	int searchC[searchX];
	
	for (int i = 0; i < searchX; i++) {
		cin >> element;
		searchC[i] = element;
	}
	
	for (int i = 0; i < searchX; i++) {
		cout << i + 1 << matrixC.search(searchC[i],rows) << endl;
	}
	
    return 0;
}
 
/*
 * Create Circular Link List (last node points to first node)
 */
template <class T> 
void circular_llist<T>::create_node()
{
    struct node<T> *temp;
    temp = new(struct node<T>);
    temp->info = 0;
	temp->column = 0;
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
	size++;
}
 
/*
 * Insertion of element at beginning 
 */
template <class T> 
void circular_llist<T>::add_begin(T value, int pos)
{
    struct node<T> *temp;
    temp = new(struct node<T>);
    temp->info = value;
	temp->column = pos;
    temp->next = last->next;
    last->next = temp;
	size++;
}
 
/*
 * Insertion of element at a particular place 
 */
template <class T> 
void circular_llist<T>::add_after(T value, int pos)
{
    struct node<T> *temp, *s;
    s = last->next;
    for (int i = 0;i < pos-1;i++)
    {
        s = s->next;
    }
    temp = new(struct node<T>);
    temp->next = s->next;
    temp->info = value;
    s->next = temp;
    /*Element inserted at the end*/
    if (s == last)
    { 
        last=temp;
    }
	size++;
}
 
/*
 * Search element in the list 
 */
template <class T> 
int circular_llist<T>::search_element(T value)
{
    struct node<T> *s;
    int counter = 0;
    s = last->next;
    while (counter != value)
    {
        counter++;
        s = s->next;
    }
    if (counter == value)    
    {            
        //cout<<"Element "<<s->info;
        //cout<<" found at position "<<counter<<endl;
        return(s->column);
    }
	else
    cout<<"\n"<<endl;
}
 
/*
 * Display Circular Link List 
 */
template <class T> 
void circular_llist<T>::display_list()
{
    struct node<T> *s;
    if (last == NULL)
    {
        cout<<"List is empty, nothing to display"<<endl;
        return;
    }
    s = last->next;
	cout<<s->info<<"("<<s->column<<")";
	s = s->next;
    while (s != last)
    {
        cout<<"->"<<s->info<<"("<<s->column<<")";
        s = s->next;
    }
    cout<<endl;
}

template <class T> 
int circular_llist<T>::getter(int col)
{
	struct node<T> *s;
    s = last->next;
	for (int i = 0;i < col-1;i++)
    {
        s = s->next;
    }
	return (s->info);
}

template <class T>
Matrix<T>::Matrix(int matrixSize)
{
	array = new circular_llist<T>[matrixSize];
	length = matrixSize;
	
	for (int i = 0; i < length; i++)
		array[i].create_node();
}

template <class T>
Matrix<T>::~Matrix() 
{
	delete [] array;
}

template <class T>
void Matrix<T>::print()
{
	cout << "\nMatrix:\n";
    for ( int i = 0; i < length; i++ )
    {
        cout << "Row " << i + 1 << ": ";
        array[i].display_list();
    }
	cout << "\n";
}

template <class T>
void Matrix<T>::insert(int row, T value, int pos)
{
	array[row].add_begin(value,pos);
}

template <class T> 
int Matrix<T>::get_value(int r, int c)
{
	return(array[r].getter(c));
}

template <class T> 
int Matrix<T>::search(int t, int rowss)
{
	for (int r = 0; r < rowss; r++)
		return(array[r].search_element(t));
}