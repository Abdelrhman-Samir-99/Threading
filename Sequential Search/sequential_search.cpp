#include <iostream>
#include <thread>
using namespace std;

const int mxN = 1e5 + 5;

int a[mxN];
bool found;

// doing sequential search for each quarter.
void do_Work(int low, int high, int value) {
	for(int i = low; i <= high && !found; ++i)
		if(a[i] == value)
			found = true;
}

int main() {
	puts("Enter the number of items and it should be greater than or equal to 4 : ");
	int n;
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

	// Waiting for all the thread to finish.
	first.join();
	second.join();
	third.join();
	fourth.join();

	if(found)
		puts("Found");
	else
		puts("Not exist");
}
