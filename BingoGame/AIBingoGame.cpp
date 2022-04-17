#include <iostream>
#include <time.h>
using namespace std;
int iNum[25], aiNum[25];

enum AI_MODE
{
	AM_EASY = 1,
	AM_HARD
};

enum LINE_NUMBER
{
	LN_H1, 
	LN_H2, 
	LN_H3, 
	LN_H4, 
	LN_H5, 
	LN_V1,
	LN_V2,
	LN_V3,
	LN_V4,
	LN_V5,
	LN_LT,
	LN_RT
};

int main()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 25; i++)
	{
		iNum[i] = i + 1;
		aiNum[i] = i + 1;
	}

	int tmp, idx1, idx2;
	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		tmp = iNum[idx1];
		iNum[idx1] = iNum[idx2];
		iNum[idx2] = tmp;

		idx1 = rand() % 25;
		idx2 = rand() % 25;

		tmp = aiNum[idx1];
		aiNum[idx1] = aiNum[idx2];
		aiNum[idx2] = tmp;
	}

	int iBingo = 0, aiBingo = 0;
	int iAIMode;
	// AI 난이도 선택
	while (true) {
		system("cls");
		cout << "1. EASY" << '\n';
		cout << "2. HARD" << '\n';
		cout << "AI 모드를 선택하세요 : ";
		cin >> iAIMode;

		if (iAIMode >= AM_EASY && iAIMode <= AM_HARD)
			break;
	}
	
	// 선택 안된 목록 배열을 만들어준다.
	int iNoneSelect[25] = {};
	int iNoneSelectCount = 0;

	while (true) {
		system("cls");
		cout << "=============== Player Bingo ===============\n";
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
		cout << "Player 빙고 수 : " << iBingo << '\n' << '\n';
		
		cout << "=============== Computer Bingo ===============\n";
		switch (iAIMode)
		{
		case AM_EASY:
			cout << "AIMode : Easy" << '\n';
			break;
		case AM_HARD:
			cout << "AIMode : Hard" << '\n';
			break;
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (aiNum[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << aiNum[i * 5 + j] << '\t';
			}
			cout << '\n';
		}
		
		cout << "Computer 빙고 수 : " << aiBingo << '\n';
		if (iBingo >= 5) {
			cout << "Player 승리\n";
			break;
		}
		else if (aiBingo >= 5) {
			cout << "Computer 승리\n";
			break;
		}
		
		cout << "숫자를 입력하세요. (0 입력시 종료) : ";
		int iInput;
		cin >> iInput;
		if (iInput == 0)
			break;
		else if (iInput < 1 || iInput>25)
			continue;

		bool bAcc = true;
		for (int i = 0; i < 25; i++)
		{
			if (iNum[i] == iInput) {
				bAcc = false;
				iNum[i] = INT_MAX;
				break;
			}
		}
		if (bAcc)
			continue;
		for (int i = 0; i < 25; i++)
		{
			if (aiNum[i] == iInput) {
				aiNum[i] = INT_MAX;
				break;
			}
		}

		// AI가 선택을 한다. AI가 선택하는 것은 AI모드에 따라서 달라진다.
		
		switch (iAIMode)
		{
			// AI Easy 모드는 현재 AI의 숫자목록중 *로 바뀌지 않은 숫자 목록을 만들어서 그 목록중 하나를 선택하게 한다. (랜덤)
		case AM_EASY:
			// 선택안된 숫자 목록을 만들어준다.
			// 선택안된 숫자 개수는 목록을 만들 때 카운트된다.
			iNoneSelectCount = 0;
			for (int i = 0; i < 25; i++)
			{
				if (aiNum[i] != INT_MAX) {
					// *이 아닌 숫자일 경우 iNoneSelectCount를 인덱스로 활용한다.
					// 선택안된 목록에 추가할 때마다 개수를 1씩 증가시켜서 총 선택안된 개수를 구해준다.
					// 그런데 0부터 카운트가 시작이므로 0번에 넣고 ++해서 1개 추가되었다 라고 해준다.
					iNoneSelect[iNoneSelectCount] = aiNum[i];
					iNoneSelectCount++;
				}
			}
			// for문을 빠져나오게 되면 선택안된 목록이 만들어지고 선택안된 목록의 개수가 만들어지게 된다.
			// 선택안된 목록의 숫자 중 랜덤한 하나의 숫자를 얻어오기 위해 인덱스를 랜덤하게 구해준다.
			iInput = iNoneSelect[rand() % iNoneSelectCount];
			break;
		case AM_HARD:
			// 하드모드는 현재 숫자 중 빙고줄 완성 가능성이 가장 높은 줄을 찾아서
			// 그 줄에 있는 숫자 중 하나를 *로 만들어준다.
			int iLine = 0;
			int iStarCount = 0;
			int iSaveCount = 0;

			// 가로 세로 라인 중 가장 *이 많은 라인을 찾아낸다.
			for (int i = 0; i < 5; i++)
			{
				iStarCount = 0;
				for (int j = 0; j < 5; j++)
				{
					if (aiNum[i * 5 + j] == INT_MAX)
						iStarCount++;
				}
				// 별이 5개 미만이어야 빙고 줄이 아니고 기존에 가장 많은 라인의 별보다 커야 가장 별이 많은 라인이므로
				// 라인을 교체해주고 저장된 별 수를 교체한다.
				if (iStarCount < 5 && iSaveCount < iStarCount) {
					// 여기는 가로 라인 중 가장 별이 많은 라인을 체크하는 곳이다.
					// 가로 라인은 0 ~ 4로 의미를 부여했다.
					iLine = i;
					iSaveCount = iStarCount;
				}
			}
			// 가로 라인 중 가장 별이 많은 라인은 이미 구했다.
			// 이 값과 세로 라인들을 비교하여 별이 가장 많은 라인을 구한다.
			for (int i = 0; i < 5; i++)
			{
				iStarCount = 0;
				for (int j = 0; j < 5; j++)
				{
					if (aiNum[j * 5 + i] == INT_MAX)
						iStarCount++;
				}
				if (iStarCount < 5 && iSaveCount < iStarCount) {
					// 세로 라인은 5 ~ 9로 의미를 부여했다
					iLine = i + 5;
					iSaveCount = iStarCount;
				}
			}
			// 왼쪽 -> 오른쪽 대각선 체크
			iStarCount = 0;
			for (int i = 0; i < 25; i+=6)
			{
				if(aiNum[i] == INT_MAX)
					iStarCount++;
			}
			if (iStarCount < 5 && iSaveCount < iStarCount) {
				iLine = LN_LT;
				iSaveCount = iStarCount;
			}
			// 오른쪽 -> 왼쪽 대각선 체크
			iStarCount = 0;
			for (int i = 4; i <= 20; i += 4)
			{
				if (aiNum[i] == INT_MAX)
					iStarCount++;
			}
			if (iStarCount < 5 && iSaveCount < iStarCount) {
				iLine = LN_RT;
				iSaveCount = iStarCount;
			}
			// 모든 라인을 조사했으면 iLine에 가능성이 가장 높은 줄 번호가 저장되었다.
			// 그 줄에 있는 *이 아닌 숫자 중 하나를 선택하게 한다.
			
			// 가로 줄일 경우
			if (iLine <= LN_H5) {
				// 가로 줄일 경우 iLine이 0 ~ 4 사이의 값이다.
				for (int i = 0; i < 5; i++)
				{
					if (aiNum[iLine * 5 + i] != INT_MAX) {
						iInput = aiNum[iLine * 5 + i];
						break;
					}
				}
			}
			// 세로 줄일 경우
			else if (iLine <= LN_V5) {
				for (int i = 0; i < 5; i++)
				{
					if (aiNum[i * 5 + (iLine - 5)] != INT_MAX) {
						iInput = aiNum[i * 5 + (iLine - 5)];
						break;
					}
				}
			}
			// 왼쪽 -> 오른쪽 대각선일 경우
			else if (iLine == LN_LT) {
				for (int i = 0; i < 25; i+=6)
				{
					if (aiNum[i] != INT_MAX) {
						iInput = aiNum[i];
						break;
					}
				}
			}
			// 오른쪽 -> 왼쪽 대각선일 경우
			else if (iLine == LN_RT) {
				for (int i = 4; i <= 20; i += 4)
				{
					if (aiNum[i] != INT_MAX) {
						iInput = aiNum[i];
						break;
					}
				}
			}
			break;
		}
		// AI가 숫자를 선택했으므로 플레이어와 AI의 숫자를 *로 바꿔준다.
		for (int i = 0; i < 25; i++)
		{
			if (iNum[i] == iInput) {
				iNum[i] = INT_MAX;
				break;
			}
		}
		// AI 숫자를 바꿔준다.
		for (int i = 0; i < 25; i++)
		{
			if (aiNum[i] == iInput) {
				aiNum[i] = INT_MAX;
				break;
			}
		}

		iBingo = 0;
		aiBingo = 0;
		int line = 0, row = 0;
		int aiLine = 0, aiRow = 0;
		for (int i = 0; i < 5; i++)
		{
			line = row = 0;
			aiLine = aiRow = 0;
			for (int j = 0; j < 5; j++)
			{
				if (iNum[i * 5 + j] == INT_MAX)
					line++;
				if (iNum[j * 5 + i] == INT_MAX)
					row++; 
				
				if (aiNum[i * 5 + j] == INT_MAX)
					aiLine++;
				if (aiNum[j * 5 + i] == INT_MAX)
					aiRow++;
			}
			if (line == 5)
				iBingo++;
			if (row == 5)
				iBingo++;
			if (aiLine == 5)
				aiBingo++;
			if (aiRow == 5)
				aiBingo++;
		}

		line = 0;
		aiLine = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (iNum[i] == INT_MAX)
				line++;
			if (aiNum[i] == INT_MAX)
				aiLine++;
		}
		if (line == 5)
			iBingo++;
		if (aiLine == 5)
			aiBingo++;

		line = 0;
		aiLine = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (iNum[i] == INT_MAX)
				line++;
			if (aiNum[i] == INT_MAX)
				aiLine++;
		}
		if (line == 5)
			iBingo++;
		if (aiLine == 5)
			aiBingo++;
	}
}
