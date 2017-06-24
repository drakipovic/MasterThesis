#include <cstdio>
#include <iostream>

using namespace std;



int main () {

	int a=0;
	int sol=0;
	
	for (int i=0; i<4; i++) {
		cin >>a;
		sol+=min (a, 12-a);
	}

	cout <<sol;

	return 0;
}
