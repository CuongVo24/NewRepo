#include <iostream>
using namespace std;
int sentinalLinearSearch(int a[], int n, int k);
int sentinalLinearSearch(int a[], int n, int k) {
	int last = a[n - 1];
	a[n - 1] = k;
	int i = 0;
	while (a[i] != k) {
		i++;
	}
	a[n - 1] = last;
	if (i < n - 1 || a[n-1] == k) {
		return i;
	}
	return -1;
}
int main() {
	int n;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int k;
	cin >> k;
	int rs = sentinalLinearSearch(a, n, k);
	cout << rs << endl;

	return 0;
}
