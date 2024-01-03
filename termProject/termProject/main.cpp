#include <windows.h>
#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <thread>
#include <chrono>
#include <conio.h>
#include <vector>
#include <iomanip>
#include "Cursor.h"
#include "Decorator.h"
#include <cstdlib>
void printString(int i);
void eraseString(int i);
void input(int c);
void strCompare();

std::string userInput;
std::vector<MyString> v;
int MAXWIDTH = 16;
int END = 0;
bool isGameStart = true;
bool isAllYPass = false;

void printString(int i) { // 화면에 문자열 출력하는 함수
	Cursor::gotoxy(v[i].x, v[i].y);
	std::cout << v[i].word;
}

void eraseString(int i) { // 화면에서 문자열을 지우는 함수
	if (v[i].isPrint) { // 화면에 문자열이 출력되어있다면
		Cursor::gotoxy(v[i].x, v[i].y);
		for (int i = 0; i < MAXWIDTH-1; i++) {
			std::cout << " "; // 지우기
		}
	}
}
void input(int c) { // 사용자 입력과 관련된 로직 함수임.
	if (c == '\b') { // 백스페이스 누를때
		if (userInput.length() != 0) {
			Cursor::gotoxy(6 + userInput.length() - 1, 23);
			std::cout << " ";
			userInput.pop_back();
		}
	}
	else if (c != '\r') { // 엔터키 제외한 다른 키
		Cursor::gotoxy(6 + userInput.length(), 23);
		printf("%c", c);
		userInput.push_back(c);
	}
	else if (c == '\r') { // 엔터 키
		strCompare();
		Cursor::gotoxy(6, 23);
		for (int i = 0; i < userInput.length(); i++)
			std::cout << " ";
		userInput.clear();
		//ending();
	}
}
void strCompare() { // 사용자가 입력한 문자열이 옳게 타이핑됐는지 확인
	for (int i = 0; i < v.size(); i++) {
		if (userInput.compare(v[i].word) == 0) { // 문자열이 같으면
			v[i].isCorrect = true; // 맞게 타이핑 된 상태를 저장.
			eraseString(i);
			v[i].word = "";
		}
	}
}
void setRandomX() { // x축을 5등분 후 문자열이 생성될 위치를 가운데로 조정함.
	for (int i = 0; i < v.size(); i++) {
		int temp = rand() % 5 + 1;
		if (temp == 1) {
			int rx = MAXWIDTH/2; // 16/2
			v[i].x = rx;
		}
		else if (temp == 2) {
			int rx = MAXWIDTH + MAXWIDTH/2;
			v[i].x = rx;
		}
		else if (temp == 3) {
			int rx = 2*MAXWIDTH + MAXWIDTH/2;
			v[i].x = rx;
		}
		else if (temp==4){
			int rx = 3*MAXWIDTH + MAXWIDTH/2;
			v[i].x = rx;
		}
		else {
			int rx = 4 * MAXWIDTH + MAXWIDTH / 2;
			v[i].x = rx;
		}
	}
}
void drawBorder() { // 경계선 그린 함수
	Cursor::gotoxy(0, 21);
	std::cout << "---------------------------------------------------------------------------------------------\n\n";
	std::cout << "입력: ";

}
bool whenGameEnd() { // 게임이 끝났는지를 확인
	int count = v.size();
	for (int i = 0; i < v.size(); i++) {
		if (!v[i].isPrint) {
			count--;
		}
	}
	if (count == 0) {
		isAllYPass = true;
	}
	return isAllYPass;
}

void randomSpeed() { // 하강하는 속도를 주기적으로 랜덤하게 조정하는 함수
	if (END % 5 == 0) {
		for (int i = 0; i < v.size(); i++) {
			if (v[i].y > 0) {
				int rs = rand()%5 + 1;
				v[i].speed = rs;
			}
			
		}
	}
}
void gameEnd() { // 게임이 끝나고 몇개나 맞췄는지 확인하는 함수
	int c = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].isCorrect) {
			c++;
		}
	}
	Cursor::gotoxy(0, 0);
	std::cout << "##########\n";
	std::cout << "점수 : " << c << "/ 20\n";
	std::cout << "##########";
}
bool setWindowSize(int width, int height) { // 사용자의 콘솔창을 강제적으로 조정하는 함수
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT windowSize;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = width - 1; // 너비
	windowSize.Bottom = height - 1; // 높이

	return SetConsoleWindowInfo(hStdout, TRUE, &windowSize);
}

int main() {
	Cursor::hideCursor();	// 커서 숨기기
	setWindowSize(120, 30); // 120, 30 으로 콘솔창 조정.

	//std::vector<MyString> v;
	srand(static_cast<unsigned int>(time(0)));
    int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;

    RandomStringComponent* generator = new BasicString(); // Decorator.h 의 generator 
	
    std::cout << "타자게임을 시작합니다." << std::endl;
	std::cout << "총 20개의 단어가 나옵니다." << std::endl;
	std::cout << "20개가 나오고 게임이 종료되면 점수가 나옵니다." << std::endl;
	std::cout << "옵션을 선택하실거라면 번호가 같게 입력해주세요" << std::endl;
	std::cout << "1. Alphabet 옵션 : ";
	std::cin >> choice1;
	std::cout << "\n2.Number 옵션 : ";
	std::cin >> choice2;
	std::cout << "\n3.Special 옵션 : ";
	std::cin >> choice3;
    
	if (choice1 == 1) {
		if (choice2 == 2) {
			if (choice3 == 3) { // 1, 2, 3
				generator = new AlphabetDecorator(generator);
				generator = new NumberDecorator(generator);
				generator = new SpecialDecorator(generator);
			}
			else { // 1, 2
				generator = new AlphabetDecorator(generator);
				generator = new NumberDecorator(generator);
			}
		}
		else {
			if (choice3 == 3) { // 1, 3
				generator = new AlphabetDecorator(generator);
				generator = new SpecialDecorator(generator);
			}
			else { // 1
				generator = new AlphabetDecorator(generator);
			}
		}

	}
	else if (choice2 == 2) {
		if (choice3 == 3) { // 2, 3
			generator = new NumberDecorator(generator);
			generator = new SpecialDecorator(generator);
		}
		else { // 2
			generator = new NumberDecorator(generator);
		}

	}
	else { // 3만 선택됐을 때
		generator = new SpecialDecorator(generator);
	}

	for (int i = 0; i < 20; i++) { // 생성된 문자열을 벡터에 넣기
		std::string temp = generator->getRandomString();
		v.push_back(MyString(temp));
	}
	setRandomX();

	system("cls"); 
	int c;
	clock_t time1 = clock();
	int count = 1;
	while (isGameStart) { // 게임 시작
		if (_kbhit()) {
			c = _getch();
			input(c);
		}
		if (clock() - time1 > 2000) { // 2초마다 문자열 나오게 함
			for (int i = 0; i < count; i++) {
				drawBorder();
				randomSpeed();
				eraseString(i);
				v[i].y += v[i].speed; // 주기적으로 바뀌는 속도를 반영
				if (v[i].y >= 21) { // 경계선을 넘어갔을때 로직 처리
					v[i].isPrint = false;
					v[i].word = "";
					eraseString(i);
				}
				else {				
					printString(i);
					if (v[i].y == 0) { // 최상단에 문자열 출력하기위한 세팅 및 speed값 주기
						v[i].speed = 1;
					}
				}
				
			}
			if (count < 20) {
				count++;
			}
			time1 = clock();
		}
		END++;
		if (whenGameEnd()) {
			isGameStart = false;
		}
	}
	gameEnd();

    return 0;
}