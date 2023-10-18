#include <iostream>

using namespace std;

void addition(int m, int n) {
	int** x = new int* [m];
	int** y = new int* [m];
	int** z = new int* [m];
	int input;

	for (int i = 0; i < m; i++) {
		x[i] = new int[n];
		for (int j = 0; j < n; j++) {
			cin >> input;
			x[i][j] = input;
		}
	}

	for (int i = 0; i < m; i++) {
		y[i] = new int[n];
		for (int j = 0; j < n; j++) {
			cin >> input;
			y[i][j] = input;
		}
	}

	for (int i = 0; i < m; i++) {
		z[i] = new int[n];
		for (int j = 0; j < n; j++) {
			z[i][j] = x[i][j] + y[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << z[i][j] << " ";
		}
		cout << endl;
	}
}

void subtraction(int m, int n) {
	int** x = new int* [m];
	int** y = new int* [m];
	int** z = new int* [m];
	int input;

	for (int i = 0; i < m; i++) {
		x[i] = new int[n];
		for (int j = 0; j < n; j++) {
			cin >> input;
			x[i][j] = input;
		}
	}

	for (int i = 0; i < m; i++) {
		y[i] = new int[n];
		for (int j = 0; j < n; j++) {
			cin >> input;
			y[i][j] = input;
		}
	}

	for (int i = 0; i < m; i++) {
		z[i] = new int[n];
		for (int j = 0; j < n; j++) {
			z[i][j] = x[i][j] - y[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << z[i][j] << " ";
		}
		cout << endl;
	}
}

void multiplication(int m, int n, int s) {
	int** x = new int* [m];
	int** y = new int* [n];
	int** z = new int* [m];
	int input;

	for (int i = 0; i < m; i++) {
		x[i] = new int[n];
		for (int j = 0; j < n; j++) {
			cin >> input;
			x[i][j] = input;
		}
	}

	for (int i = 0; i < n; i++) {
		y[i] = new int[s];
		for (int j = 0; j < s; j++) {
			cin >> input;
			y[i][j] = input;
		}
	}

	for (int i = 0; i < m; i++) {
		z[i] = new int[s];
		for (int j = 0; j < s; j++) {
			int value = 0;
			for (int k = 0; k < n; k++) {
				value += x[i][k] * y[k][j];
			}
			z[i][j] = value;
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < s; j++) {
			cout << z[i][j] << " ";
		}
		cout << endl;
	}
}

void transpose(int m, int n) {
	int** x = new int* [m];
	int** z = new int* [n];
	for (int i = 0; i < n; i++) {
		z[i] = new int[m];
	}
	int input;

	for (int i = 0; i < m; i++) {
		x[i] = new int[n];
		for (int j = 0; j < n; j++) {
			cin >> input;
			x[i][j] = input;
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			z[j][i] = x[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << z[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {

	char operation;
	int m, n, s;
	cin >> operation;
	switch (operation) {
	case 'a':
		cin >> m >> n;
		addition(m,n);
		break;
	case 's':
		cin >> m >> n;
		subtraction(m, n);
		break;
	case 'm':
		cin >> m >> n >> s;
		multiplication(m, n, s);
		break;
	case 't':
		cin >> m >> n;
		transpose(m, n);
		break;
	default:
		break;
	}

	return 0;
}