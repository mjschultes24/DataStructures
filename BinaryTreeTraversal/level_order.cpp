#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int N;
	cin >> N;
	
	vector<string> V (N);
	vector<int> L (N);
	vector<int> R (N);
	
	string VTemp;
	int LTemp;
	int RTemp;
	
	for (int i = 0; i < N; i++) {
		cin >> VTemp >> LTemp >> RTemp;
		V[i] = VTemp;
		L[i] = LTemp;
		R[i] = RTemp;
	}
	
	int large = 0;
	
	for int i 0; i < N; i++ {
		if (L[i] > large) {
			large = L[i];
		}
	}
	
	cout << "Leftmost value is " << V[large];
 
    return 0;
}