#include <iostream>
#include <time.h>
using namespace std;
int Lotto[45];

int main()
{
    srand((unsigned int)time(NULL));	// 난수 생성
	for (int i = 0; i < 45; i++)	// Lotto 배열에 1 ~ 45 값 넣어주기
		Lotto[i] = i + 1;

	// Shuffle
	int tmp, idx1, idx2;
	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		tmp = Lotto[idx1];
		Lotto[idx1] = Lotto[idx2];
		Lotto[idx2] = tmp;
	}
	for (int i = 0; i < 6; i++)
		cout << Lotto[i] << '\t';
	cout << '\n';
	cout << "보너스번호 : " << Lotto[6] << '\n';
}
