#include <iostream>
#include <thread>
using namespace std;

const int mxN = 1e5 + 5;
int a[mxN];
bool found;

// doing binary search for each quarter.
void do_Work(int low, int high, int value) {
	while(low <= high && !found) {
		int mid = (low + high) / 2;
		if(a[mid] == value) {
			found = true;
			return;
		}
		if(a[mid] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
}

int main() {
	int n;
	puts("Enter the number of items and it should be greater or equal to 4 : ");
	scanf("%d", &n);
	if(n < 4) {
		puts("You are dummy");
		exit(0);
	}
	
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);

	puts("Enter the value i will look for : ");
	int v;
	scanf("%d", &v);
	
	int low = 1, high = n / 4;
	std::thread first(do_Work, low, high, v);
	low = high + 1, high = n * 2 / 4;
	std::thread second(do_Work, low, high, v);
	low = high + 1, high = n * 3 / 4;
	std::thread third(do_Work, low, high, v);
	low = high + 1, high = n;
	std::thread fourth(do_Work, low, high, v);

	// Waiting for all the threads to finish.
	first.join();
	second.join();
	third.join();
	fourth.join();
	
	if(found)
		puts("Found");
	else
		puts("Not exist");
}
