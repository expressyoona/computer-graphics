#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;

struct Mark {
	float mark;
};

struct Array {
	string name;
	Mark arr[3];
};

int main() {
	Mark m1 = {6.4};
	Mark m2 = {6.7};
	Mark m3 = {3.4};
	Mark m[] = {m1, m2, m3};
	Array arr = {"Hoang", m[3]};
	cout<<arr.arr[0].mark;
}
