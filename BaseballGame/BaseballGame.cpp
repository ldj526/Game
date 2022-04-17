#include <iostream>
#include <time.h>
using namespace std;
int random[3], input[3];

int main()
{
	srand((unsigned int)time(NULL));	// 초당 seed 값이 변화해서 난수 생성
	for (int i = 0; i < 3; i++)
	{
		random[i] = (rand() % 9) + 1;
		for (int j = 0; j < i; j++)
		{
			if (random[i] == random[j] && i != j)
				i--;
		}
	}
	int count = 1;
	while (true) {
		cout << "[" << count << "번 째 게임]" << '\n';
		while (true) {
			cout << "3개의 숫자를 입력하세요.(1 ~ 9까지, 중복X)" << '\n';
			cin >> input[0] >> input[1] >> input[2];
			if (input[0] < 1 || input[0] > 9 || input[1] < 1 || input[1] > 9 || input[2] < 1 || input[2] > 9) {
				cout << "범위를 다시 확인해주세요.\n";
				continue;
			}
			else if (input[0] == input[1] || input[1] == input[2] || input[2] == input[0]) {
				cout << "중복된 값입니다.\n";
				continue;
			}
			break;
		}
		int ball = 0, strike = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (input[i] == random[j])
					if (i == j)
						strike++;
					else
						ball++;
			}
		}
		if (strike > 0 || ball > 0)
			cout << "스트라이크 : " << strike << ", 볼 : " << ball << '\n' << '\n';
		else
			cout << "아웃" << '\n' << '\n';
		if (strike == 3) {
			cout << "승리했습니다." << '\n';
			break;
		}
		count++;
	}
}
