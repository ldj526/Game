#include <iostream>
#include <time.h>
using namespace std;
int iNum[25];

int main()
{
	srand((unsigned int)time(NULL));
	
	for (int i = 0; i < 25; i++)
		iNum[i] = i + 1;

	int tmp, idx1, idx2;
	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		tmp = iNum[idx1];
		iNum[idx1] = iNum[idx2];
		iNum[idx2] = tmp;
	}
	int iBingo = 0;
	while (true) {
		system("cls");
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (iNum[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << iNum[i * 5 + j] << '\t';
			}
			cout << '\n';
		}
		cout << "빙고 수 : " << iBingo << '\n';
		
		// 빙고 수가 5 이상일 때 게임 종료
		if (iBingo >= 5)
			break;

		cout << "숫자를 입력하세요(0 : 종료) : ";
		int iInput;
		cin >> iInput;
		if (iInput == 0)
			break;
		else if (iInput < 1 || iInput > 25)
			continue;

		// 중복 입력을 체크하기 위한 변수
		bool bAcc = true;
		// 모든 숫자를 차례대로 검사해서 입력한 숫자와 같은 숫자가 있는지 찾아낸다.
		for (int i = 0; i < 25; i++)
		{
			// 같은 숫자가 있을 경우
			if (iInput == iNum[i]) {
				// 숫자를 찾았을 경우 중복된 숫자가 아니므로 bAcc 변수를 false로 바꿔준다.
				bAcc = false;
				iNum[i] = INT_MAX;
				break;
			}
		}
		if (bAcc)
			continue;
		iBingo = 0;
		int line = 0, row = 0;
		for (int i = 0; i < 5; i++)
		{
			// 한 줄을 체크하기 전에 먼저 0으로 별 개수를 초기화
			line = row = 0;
			for (int j = 0; j < 5; j++)
			{
				// 가로 별 개수를 구한다.
				if (iNum[i * 5 + j] == INT_MAX)
					line++;
				// 세로 별 개수를 구한다.
				if (iNum[j * 5 + i] == INT_MAX)
					row++;
			}
			// j for문을 빠져나오고 나면 현재 줄의 가로 별 개수가 몇개인지 line 변수에 들어간다.
			if (line == 5)
				iBingo++;
			if (row == 5)
				iBingo++;
		}
		// 왼쪽 상단 -> 오른쪽 하단 대각선
		line = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (iNum[i] == INT_MAX)
				line++;
		}
		if (line == 5)
			iBingo++;

		// 오른쪽 상단 -> 왼쪽 하단 대각선
		line = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (iNum[i] == INT_MAX)
				line++;
		}
		if (line == 5)
			iBingo++;
	}
}
