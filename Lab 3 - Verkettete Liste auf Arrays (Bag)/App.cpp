#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

//ADT Bag - reprasentiert mithilfe einer DLLA von Paaren der Form (Element, Frequenz)

//overload - operatorul de egalitate

int main() {

	testAll();
	cout << "Short tests over" << endl;
	testAllExtended();

	cout << "All test over" << endl;
}
