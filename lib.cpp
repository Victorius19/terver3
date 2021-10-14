#include "lib.h"
#include <iostream>
#include <cmath>

using namespace std;

//   R  G  B
static const int data[3][3] = {
	{11, 11, 10},
	{10, 10, 10},
	{11, 9, 5}
};
int N = 5;

double three(int R, int vr){
	double count = 0;

	for(int i = 0; i <= R; i++) count += one(2, i, vr);

	return 1 - count;
}

double two(int R, int vr){
	double count = 0;

	for(int i = 0; i <= R; i++) count += one(1, i, vr);

	return count;
}

double one(int b, int R, int vr){
	double count = 0;

	for(int i = 0; i <= data[0][b] && i <= R; i++)
		for(int j = 0; j <= (data[1][b]-i) && j <= (R-i); j++)
			for(int l = 0; l <= (data[2][b]-i-j) && l <= (R-i-j); l++)
				if (i + j + l == R)
					if (!vr) count += kol_a(b, i, j, l);
					else count += kol_b(b, i, j, l);

	return count;
}

double kol_a(int color, int ii, int j, int l){
	int all;
	int k[] = {ii, j, l};
	double count = 1;

	for (int i = 0; i < 3; ++i){
		all = data[i][0] + data[i][1] + data[i][2];

		count *= pow(double(data[i][color])/double(all), k[i]) * pow(double(all - data[i][color])/double(all), N - k[i]) * perm(N, k[i]);
	}

	return count;
}

double kol_b(int color, int ii, int j, int l){
	int all;
	int k[] = {ii, j, l};
	double count = 1;

	for (int i = 0; i < 3; ++i){
		all = data[i][0] + data[i][1] + data[i][2];

		count *= double(fk(data[i][color], data[i][color] - k[i], 0) * fk(all - data[i][color], all - data[i][color] - N + k[i], 0)) / double(fk(all, all - N, 0)) * perm(N, k[i]);
	}

	return count;
}

int perm(int n, int m){
	if (m == 0) return 1;
	else if (m < n - m) return fk(n, n - m, m);
	else return fk(n, m, n - m);
}

int fk(int max, int min, int zn){
	if (max == min) return 1;

	int count = max;
	int temp;

	for(--max; max > min; max--){
		temp = count * max;

		if (temp / max == count) count = temp;
		else { //обработка переполнения переменной
			cout << "Переменная переполнена! Точность вычислений может быть снижена." << endl;

			if(!zn){
				cout << "Программа не способна дать ответ, когда результирующее значение больше " << sizeof(int) << " байт." << endl;
				return -1;
			}

			count /= zn;
			zn--;
			max++;
		}
	}

	if(zn) count /= fk(zn, 0, 0);

	return count;
}