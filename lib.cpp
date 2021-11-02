#include "lib.h"
#include <iostream>
#include <cmath>

using namespace std;

// Массив в котором хронятся исходный данные по количеству шаров в каждой урны
//   R  G  B
static const int data[3][3] = {
	{5, 6, 7},
	{6, 8, 9},
	{7, 6, 5}
};
int N = 5;

// Функция подсчитывает третий пункт с помощью функции подсчитывающей первый пункт
double three(int R, int vr){
	double count = 0;

	for(int i = 0; i <= R; i++) count += one(2, i, vr);

	return 1 - count;
}

// Функция подсчитывает второй пункт с помощью функции подсчитывающей первый пункт
double two(int R, int vr){
	double count = 0;

	for(int i = 0; i <= R; i++) count += one(1, i, vr);

	return count;
}

// Функция перебирает все варианты распределения шаров между урнами и с помощью функции kol_a или kol_b подсчитывает первый пункт
double one(int b, int R, int vr){
	double count = 0;

	for(int i = 0; i <= data[0][b] && i <= R; i++)
		for(int j = 0; j <= (data[1][b]-i) && j <= (R-i); j++)
			if (!vr) count += kol_a(b, i, j, R-i-j);
			else count += kol_b(b, i, j, R-i-j);

	return count;
}

// Функция возвращает вероятность вытащить ii, j, и k шаров color цвета (0 - R, 1 - G, 2 - B) из первой, второй и третьей урны соответственно.
// Вероятность считается при условии случая a), т.е. если шары возвращаются в кучу.
double kol_a(int color, int ii, int j, int l){
	int all;
	int k[] = {ii, j, l};
	double count = 1;

	for (int i = 0; i < 3; ++i){
		all = data[i][0] + data[i][1] + data[i][2];

		// Тут подсчитывается вероятность вытащить k[i] шаров color цвета из определенной урны, формула:
		// (data[i][color] / all)^k[i] * (all - data[i][color] / all)^(N - k[i]) * perm(N, k[i])
		// где 
		// data[i][color] - количество шаров нужного цвета в куче
		// all - количество всех шаров в куче
		// k[i] - сколько шаров нужно вытащить
		// perm(N, k[i]) - количество перестановок при данном случае
		count *= pow(double(data[i][color])/double(all), k[i]) * pow(double(all - data[i][color])/double(all), N - k[i]) * perm(N, k[i]);
	}

	return count;
}

// Функция возвращает вероятность вытащить ii, j, и k шаров color цвета (0 - R, 1 - G, 2 - B) из первой, второй и третьей урны соответственно.
// Вероятность считается при условии случая б), т.е. если шары не возвращаются в кучу.
double kol_b(int color, int ii, int j, int l){
	int all;
	int k[] = {ii, j, l};
	double count = 1;

	for (int i = 0; i < 3; ++i){
		all = data[i][0] + data[i][1] + data[i][2];

		// Тут подсчитывается вероятность вытащить k[i] шаров color цвета из определенной урны, формула:
		// (data[i][color]! / (data[i][color] - k[i])! * (all - data[i][color])! / (all - data[i][color] - N + k[i])!) / (all! / (all - N)!)* perm(N, k[i])
		// где 
		// data[i][color] - количество шаров нужного цвета в куче
		// all - количество всех шаров в куче
		// k[i] - сколько шаров нужно вытащить
		// perm(N, k[i]) - количество перестановок при данном случае
		count *= double(fk(data[i][color], data[i][color] - k[i], 0) * fk(all - data[i][color], all - data[i][color] - N + k[i], 0)) / double(fk(all, all - N, 0)) * perm(N, k[i]);
	}

	return count;
}

//Функция выполняет подсчет числа перестановок используя функцию fk() для оптимального подсчета факториалов
int perm(int n, int m){
	if (m == 0) return 1;
	else if (m < n - m) return fk(n, n - m, m);
	else return fk(n, m, n - m);
}

// В функцию fk() передаются три значения для оптимального подсчета факториала или комбинаций, по результату работы функция аналогична выражению max! / (min! * zn!)
//
// Для избежания переполнения переменных при подсчете значений больших факториалов использованы две идеи:
// 1) Функция не считает значение max!, а сразу считает значение max! / min!, т.е. просто умножает все значения от min до max;
// 2) Если функция фиксирует переполнение переменной при подсчете max! / min!, то она выводит предупреждение о возможности снижения точности вычислений
//    и затем делит результат вычислений на zn, в последствии уменьшая значение zn на 1.
int fk(int max, int min, int zn){
	if (max == min) return 1;

	int count = max;
	int temp;

	for(--max; max > min; max--){
		temp = count * max;

		if (temp / max == count) count = temp;
		else { //обработка переполнения переменной
			cout << "Переменная переполнена! Точность вычислений может быть снижена." << endl;

			if(!zn){ //На случай, если программа уже не сможет делить на zn, поскольку zn = 0
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