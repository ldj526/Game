#include <iostream>
#include <time.h>
#include <conio.h>	// console input ouput 헤더파일. 콘솔창에서 입출력하는 기능
using namespace std;
int iNum[25];

int main()
{
  srand((unsigned int)time(NULL));	// 난수 생성
	for (int i = 0; i < 24; i++)
		iNum[i] = i + 1;
	iNum[24] = INT_MAX;
	int iStarIndex = 24;
	
	// Shuffle
	int tmp, idx1, idx2;
	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 24;
		idx2 = rand() % 24;

		tmp = iNum[idx1];
		iNum[idx1] = iNum[idx2];
		iNum[idx2] = tmp;
	}
	
	while (true) {
		system("cls");		// 화면을 지워주는 것
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++) {
				if (iNum[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << iNum[i * 5 + j] << '\t';
			}
			cout << '\n';
		}
		// 모두 맞추었을 경우
		bool win = true;
		for (int i = 0; i < 24; i++)
		{
			if (iNum[i] != i + 1) {
				win = false;
				break;
			}
		}
		if (win) {
			cout << "숫자를 모두 맞췄습니다.\n";
			break;
		}
		cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료\n";
		char cInput = _getch();		// 콘솔창에서 Enter를 안치고 문자를 누르는 순간 반환하고 종료. <conio.h>
		if (cInput == 'q' || cInput == 'Q')
			break;
		switch (cInput) {
		case 'w':
		case 'W':
			if (iStarIndex > 4) {
				iNum[iStarIndex] = iNum[iStarIndex - 5];
				iNum[iStarIndex - 5] = INT_MAX;
				iStarIndex -= 5;
			}
			break;
		case 's':
		case 'S':
			if (iStarIndex < 20) {
				iNum[iStarIndex] = iNum[iStarIndex + 5];
				iNum[iStarIndex + 5] = INT_MAX;
				iStarIndex += 5;
			}
			break;
		case 'a':
		case 'A':
			if (iStarIndex % 5 != 0) {
				iNum[iStarIndex] = iNum[iStarIndex - 1];
				iNum[iStarIndex - 1] = INT_MAX;
				iStarIndex--;
			}
			break;
		case 'd':
		case 'D':
			if (iStarIndex % 5 != 4) {
				iNum[iStarIndex] = iNum[iStarIndex + 1];
				iNum[iStarIndex + 1] = INT_MAX;
				iStarIndex++;
			}
			break;
		}
	}
	cout << "게임을 종료합니다.\n";
}
