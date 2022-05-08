#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <Windows.h>
#define ll long long
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0) 
using namespace std;

void print(string s)
{
	for (int i = 0; i < s.length(); i++) {
		Sleep(10);
		cout << s[i];
	}
}

void setColor(int forgC)
{
	// Function to set the foreground color of the command line interface
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		// Mask out all but the background attribute, and add in the forgournd     color
		wColor = (csbi.wAttributes & 0xF0) + (forgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

class Flatten {
	int n, m, p, q;
	// Input 3-Dimensional Array
	vector<vector<vector<int>>> threeDArray;
	// 1-Dimensional Array to be stored in
	vector<int> newArray;

public:
	Flatten(int n, int m, int p) {
		this->n = n;
		this->m = m;
		this->p = p;
		this->q = n * m * p;
		threeDArray = vector<vector<vector<int>>>(n, vector<vector<int>>(m, vector<int>(p)));
		newArray = vector<int>(q);
	}

	void storeInput() {
		print("Please enter all the "); cout << this->q; print(" elements."); cout << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < p; k++) {
					cin >> threeDArray[i][j][k];
				}
			}
		}
	}

	void print3D() {
		setColor(11);
		cout << "====================================================3D MATRIX===========================================================" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < p; k++) {
					Sleep(10);
					cout << threeDArray[i][j][k] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		setColor(6);
	}

	void print1D() {
		setColor(11);
		cout << "====================================================1D MATRIX===========================================================" << endl;
		for (int i = 0; i < q; i++) {
			Sleep(10);
			cout << newArray[i] << " ";
		}
		cout << endl;
	}

	void convert3DInto1D() {
		int y = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < p; k++) {
					newArray[y] = threeDArray[i][j][k];
					y++;
				}
			}
		}
	}

	int oneDIndex(int i, int j, int k) {
		if (i >= n || i < 0 || j >= m || j < 0 || k >= p || k < 0)
			return -1; // Not valid index
		return i * m * p + j * p + k; // We will skip i 2D matrices then skip j rows then k columns
	}

	int oneDValue(int i) {
		if (i >= q || i < 0)
			return -1; // Not valid index
		return newArray[i];
	}
};

int main() {
	IO;
	int n, m, p, i, j, k;
	setColor(6);
	cout << "===========================================WELCOME TO MATRIX FLATTEN APP================================================" << endl;
	print("Please enter the 3 dimensions you want ...."); cout << endl;
	setColor(4);
	cout << "N = ";
	cin >> n;
	cout << endl << "M = ";
	cin >> m;
	cout << endl << "P = ";
	cin >> p; 
	cout << endl;
	setColor(6);
	Flatten flat(n, m, p);
	flat.storeInput();
	flat.print3D();
	flat.convert3DInto1D();
	flat.print1D();

	// Infinite loop to get indices and break when -1 entered
	while (1) {
		setColor(6);
		print("Enter the 3D index: (If you want to stop enter -1)"); cout << endl;
		setColor(4);
		cout << "i = ";
		cin >> i;
		if (i == -1)
			return 0;
		cout << endl << "j = ";
		cin >> j;
		if (j == -1)
			return 0;
		cout << endl << "k = ";
		cin >> k;
		if (k == -1)
			return 0;
		cout << endl;
		setColor(6);
		if (i == -1 || j == -1 || k == -1)
			break;
		int index = flat.oneDIndex(i, j, k);
		if (index == -1) {
			setColor(4);
			print("ERROR: Please enter valid index."); cout << endl;
			continue;
		}
		setColor(11);
		print("Index of ["); cout << i << "][" << j << "][" << k << "] = " << index;
		print(" With value = "); cout << flat.oneDValue(index) << endl;
	}

	return 0;

}