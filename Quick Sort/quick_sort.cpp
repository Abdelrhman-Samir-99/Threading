#include <iostream>
#include <thread>
using namespace std;


const int N = 1e5 + 5;

int a[N];

void swap(int *x, int *y) {
	// Using this function to sawp by reference.
	int t = *x;
	*x = *y;
	*y = t;
}

int partition(int low, int high) {
	int pivot = a[high];
	int i = low - 1;
	for(int j = low; j <= high - 1; ++j) {
		if(a[j] <= pivot) {
			++i;
			swap(&a[i], &a[j]);
		}
	}
	++i;
	swap(&a[i], &a[high]);
	return i;
}

void quick_Sort(int low, int high) {
	if(low < high) {
		int pos = partition(low, high);
		std:: thread first(quick_Sort, low, pos - 1);
		quick_Sort(pos + 1, high);
		first.join();
	}
}


int main() {
	int n;
	puts("Enter a value greater than or equal to 4 : ");
	scanf("%d", &n);
	if(n < 4) {
		puts("You are dummy");
		exit(0);
	}
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	quick_Sort(1, n );
	for(int i = 1; i <= n; ++i)
		printf("%d ", a[i]);
}
