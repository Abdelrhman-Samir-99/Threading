#include <iostream>
#include <algorithm>
using namespace std;

const int mxN = 1e5 + 5;
int a[mxN];

int main() {
	// Main usage of this program is using it with a bash script to generate random test cases,
	// and make sure that our solutions are correct.
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i)
		printf("%d ", a[i]);
}
