#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;
//1,1 4,1 7,1 // 1,4 3,4 4,4 5,4 7,4 // 
bool star(int x, int y) {
	if (x % 3 == 1 && y % 3 == 1) {
		return false;
	}
	else {
		if ((x / 3) < 1 && (y / 3) < 1) {
			if (!(x == 1 && y == 1)) {return true; }
			return false;
		}
		else return star(x / 3, y / 3);
	}
}

int main() {
	int n;
	cin >> n;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (star(x,y)) {cout << "*";}
			else { cout << " "; }
		}
		cout << endl;
	}
}