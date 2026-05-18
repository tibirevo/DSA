#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

//ADT SortedMultiMap - reprasentiert mithilfe einer Hashtabelle mit coalesced Verkettung wo Paaren der Form (key, value) gespeichert werden.
//Wenn ein Schlussel mehrere entsprechende Werte hat, dann kommt es in mehreren Paaren vor. In dem Constructor des Iterators erstelle ein sortiertes Array von Elementen und benutze es fur die Iterierung.

//iterator pe valorile unei chei date. in comnstructor primim o cheie. cu next iteram prin valorile respectivei chei.

int main(){
    testAll();
	testAllExtended();

    std::cout<<"Finished SMM Tests!"<<std::endl;
	system("pause");
}
