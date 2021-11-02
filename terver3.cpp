#include <iostream>
#include <cstdlib>
#include "lib.h"

using namespace std;

int main(int argc, char *argv[]){
	cout << "Пункт 1a) " << one(0, 4, 0) << endl;
	cout << "Пункт 1б) " << one(0, 4, 1) << endl;
	cout << "Пункт 2a) " << two(4, 0) << endl;
	cout << "Пункт 2б) " << two(4, 1) << endl;
	cout << "Пункт 3a) " << three(1, 0) << endl;
	cout << "Пункт 3б) " << three(1, 1) << endl;
}