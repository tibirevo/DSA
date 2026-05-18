#include "ExtendedTest.h"
#include "ShortTest.h"

#include "Map.h"


#include <iostream>
using namespace std;

//ADT Map - reprasentiert mithilfe einer DLL von Paaren der Form (key, value).
//trebuie sa verific daca un container este o submultime altui container.

int main() {
	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}
