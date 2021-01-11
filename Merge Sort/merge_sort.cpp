#include <iostream>
#include <thread>
using namespace std;


const int N = 1e5 + 5;

int a[N];


inline void merge(int low, int mid, int high) {

	// the purpose of the merging function is to make a sorted array from two smaller sorted arrays.
	// in O(A + B) where A -> length of the first array, B -> length of the second array.
	
	int len1 = mid - low + 1, len2 = high - mid;
	int Left[len1], Right[len2];
	int i, j;

	for(i = 0; i < len1; ++i)
		Left[i] = a[i + low];

	for(i = 0; i < len2; ++i)
		Right[i] = a[i + mid + 1];

	int ptr = low;
	i = j = 0;

	// this loop will just iterate until we finish one array.
	while(i < len1 && j < len2) {
		if(Left[i] <= Right[j])
			a[ptr] = Left[i++];
		else
			a[ptr] = Right[j++];
		++ptr;
	}
	
	// this will happen if j = len2
	while(i < len1) {
		a[ptr] = Left[i++];
		++ptr;
	}

	// this will happen if i = len1
	// only one of those loops should work but NEVER both i believe.
	while(j < len2) {
		a[ptr] = Right[j++];
		++ptr;
	}
}
 

inline void merge_sort(int low, int high) {
	// The purpose of the this function is to partition the array.
	// (I THINK) not quite sure but it will run (1, 2, 4, 8, 16, 32, ...),
	// always as a power of 2, so i think the Big O for it should be O(2 ^ (Ceil(log2 N))).
	int mid = (low + high) / 2;
	if(low < high) {
		merge_sort(low, mid);
		merge_sort(mid + 1, high);
		merge(low, mid, high);
	}
}

int main() {
	puts("Enter the number of the elements and should be greater than 4 : ");
	int n;
	scanf("%d", &n);
	if(n < 4) {
		puts("You are dummy");
		exit(0);
	}
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
		 

	// the idea is that we will do merge sort for each quarter.
	int low = 1, high = n / 4;
	std::thread first(merge_sort, low, high);
	low = high + 1, high = n * 2 / 4;
	std::thread second(merge_sort, low, high);
	low = high + 1, high = n * 3 / 4;
	std::thread third(merge_sort, low, high);
	low = high + 1, high = n;
	std::thread fourth(merge_sort, low, high);

	first.join();
	second.join();
	third.join();
	fourth.join();

	// then we will do (MERGING ONLY) with 2 quarters at a time.
	low = 1, high = n * 2 / 4;
	std::thread second_first(merge, low, n / 4, high);
	low = high + 1, high = n;
	std::thread second_second(merge, low, n * 3 / 4, high);

	second_first.join();
	second_second.join();

	// then just one simple merge between 2 + 2.
	// note that we used Merging function not merge function,
	// because each quarter is already sorted.
	low = 1, high = n;
	merge(low, n * 2 / 4, high);
	for(int i = 1; i <= n; ++i)
		printf("%d ", a[i]);
}
