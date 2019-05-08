#include <iostream>

using namespace std;

int main() {
	
	// INPUT 
	
	int N;
	cin >> N;
	
	int array1[N];
	
	int n;
	
	// Initialize array1
	
	for (int i = 0; i < N; i++) {
		cin >> n;
		array1[i] = n;
	}
	
	// Sort
	
	int temp;
	
	for (int i = 0; i < N; i++) {
		temp = array1[i];
		
		for (int j = i; j >= 1; j--) {
			if (array1[j] < array1[j-1]) {
				temp = array1[j];
				array1[j] = array1[j-1];
				array1[j-1] = temp;
			}
			
			else 
				break;
		}
	}
	
	// OUTPUT
	
	
	for (int i = 0; i < N; i++) {
		n = array1[i];
		cout << n << endl;
	}
	
	// DONE
	
	return 0;
}