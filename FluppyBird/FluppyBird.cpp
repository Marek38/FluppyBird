#include<iostream>
#include<fstream>
#include<sstream>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define PIPE_DIF 45
#define GAP_SIZE 7
#define GAP_SIZE_EASY 10
#define GAP_SIZE_MEDIUM 6
#define GAP_SIZE_HARD 4


using namespace std;

 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
char bird[2][6] = { '/','-','-','O','\\',' ',
					'|','_','_','_',' ','>' };

int birdPos = 6;
int score = 0;
int level = 0;

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) 
{
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void drawBorder(){ 
	
	for(int i=0; i<SCREEN_WIDTH; i++){
		gotoxy(i,0); cout<<"±";
		gotoxy(i,SCREEN_HEIGHT); cout<<"±";
	}
	
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(0,i); cout<<"±";
		gotoxy(SCREEN_WIDTH,i); cout<<"±";
	}
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(WIN_WIDTH,i); cout<<"±";
	}
}
void genPipe(int ind){//random cislo od 3 do 16
	gapPos[ind] = 3 + rand()%14; 
}
void drawPipe(int ind){ //vykreslenie pipov
	if( pipeFlag[ind] == true ){
		for(int i=0; i<gapPos[ind]; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"\033[92m|||\033[0m"; 
		}
		for(int i=gapPos[ind]+ GAP_SIZE; i<SCREEN_HEIGHT-1; i++){
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"\033[92m|||\033[0m"; 
		}
	} 
}
void drawPipeEasy(int ind) {
	if (pipeFlag[ind] == true) {
		for (int i = 0; i < gapPos[ind]; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "\033[92m|||\033[0m";
		}
		for (int i = gapPos[ind] + GAP_SIZE_EASY; i < SCREEN_HEIGHT - 1; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "\033[92m|||\033[0m";
		}
	}
}
void drawPipeMedium(int ind) {
	if (pipeFlag[ind] == true) {
		for (int i = 0; i < gapPos[ind]; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "\033[92m|||\033[0m";
		}
		for (int i = gapPos[ind] + GAP_SIZE_MEDIUM; i < SCREEN_HEIGHT - 1; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "\033[92m|||\033[0m";
		}
	}
}
void drawPipeHard(int ind) {
	if (pipeFlag[ind] == true) {
		for (int i = 0; i < gapPos[ind]; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "\033[92m|||\033[0m";
		}
		for (int i = gapPos[ind] + GAP_SIZE_HARD; i < SCREEN_HEIGHT - 1; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "\033[92m|||\033[0m";
		}
	}
}
void erasePipe(int ind){ //zmazanie pipov
	if( pipeFlag[ind] == true ){
		for(int i=0; i<gapPos[ind]; i++){ 
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"   "; 
		}
		for(int i=gapPos[ind]+ GAP_SIZE; i<SCREEN_HEIGHT-1; i++){
			gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"   "; 
		}
	}
}
void erasePipeEasy(int ind) {
	if (pipeFlag[ind] == true) {
		for (int i = 0; i < gapPos[ind]; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
		}
		for (int i = gapPos[ind] + GAP_SIZE_EASY; i < SCREEN_HEIGHT - 1; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
		}
	}
}
void erasePipeMedium(int ind) {
	if (pipeFlag[ind] == true) {
		for (int i = 0; i < gapPos[ind]; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
		}
		for (int i = gapPos[ind] + GAP_SIZE_MEDIUM; i < SCREEN_HEIGHT - 1; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
		}
	}
}
void erasePipeHard(int ind) {
	if (pipeFlag[ind] == true) {
		for (int i = 0; i < gapPos[ind]; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
		}
		for (int i = gapPos[ind] + GAP_SIZE_HARD; i < SCREEN_HEIGHT - 1; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
		}
	}
}

void drawBird(){ //vykreslenie vtaka
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+birdPos); cout<< bird[i][j];
		}
	}
}

void eraseBird(){ //zmazanie vtaka
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+birdPos); cout<<" ";
		}
	}
}


int collision() { //kolizia
	if (pipePos[0] >= 61) {
		if (birdPos<gapPos[0] || birdPos >gapPos[0] + GAP_SIZE) {
			return 1;
		}
	}
	return 0;
}
int collisionEasy() {
	if (pipePos[0] >= 61) {
		if (birdPos<gapPos[0] || birdPos >gapPos[0] + GAP_SIZE_EASY) {
			return 1;
		}
	}
	return 0;
}
int collisionMedium() {
	if (pipePos[0] >= 61) {
		if (birdPos<gapPos[0] || birdPos >gapPos[0] + GAP_SIZE_MEDIUM) {
			return 1;
		}
	}
	return 0;
}
int collisionHard() {
	if (pipePos[0] >= 61) {
		if (birdPos<gapPos[0] || birdPos >gapPos[0] + GAP_SIZE_HARD) {
			return 1;
		}
	}
	return 0;
}

void SleepTraining(int score) { //obtiaznost,rychlost pri zmene levelov
	if (score < 5){
		Sleep(150);
	}
	else if (score < 8) {
		Sleep(130);
	}
	else if (score < 10) {
		Sleep(120);
	}
	else if (score < 13) {
		Sleep(115);
	}
	else if (score < 15) {
		Sleep(110);
	}
	else if (score < 18) {
		Sleep(105);
	}
	else if (score < 20) {
		Sleep(100);
	}
	else if (score < 23) {
		Sleep(95);
	}
	else if (score < 25) {
		Sleep(90);
	}
	else if (score < 28) {
		Sleep(85);
	}
	else if (score < 30) {
		Sleep(80);
	}
	else if (score < 45) {
		Sleep(75);
	}
	else if (score < 60) {
		Sleep(70);
	}

}

void SleepEasy(int score) {
	if (score < 5) {

		Sleep(150);
	}
	else if (score < 10) {

		Sleep(140);
	}
	else if (score < 15) {

		Sleep(130);
	}
	else if (score < 20) {

		Sleep(120);
	}
	else if (score < 30) {

		Sleep(110);
	}

}


void SleepMedium(int score) {
	if (score < 5) {
		Sleep(120);
	}
	else if (score < 10) {
		Sleep(110);
	}
	else if (score < 15) {
		Sleep(100);
	}
	else if (score < 20) {
		Sleep(95);
	}
	else if (score < 30) {
		Sleep(90);
	}

}

void SleepHard(int score) {
	if (score < 5){

		Sleep(95);
	}
	else if (score < 10) {

		Sleep(90);
	}
	else if (score < 15) {

		Sleep(80);
	}
	else if (score < 20) {

		Sleep(75);
	}
	else if (score < 30) {

		Sleep(70);
	}

}

void scored(int score){
	// Create and open a text file
	ofstream MyFile("HighScore.txt");

	// Write to the file
	MyFile << score;

	// Close the file
	MyFile.close();
}

void highscore() {
	// Create a text string, which is used to output the text file
	string myText;

	// Read from the text file
	ifstream MyReadFile("HighScore.txt");

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(MyReadFile, myText)) {
		// Output the text from the file
		cout << myText;
	}

	// Close the file
	MyReadFile.close();
}


void gameover(){ //konecne okno
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\tPress any key to go back to menu.";
	int c =_getch();
}
void updateScore(){ //zobrazenie skore
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

void updateLevel()  { //zobrazenie levelu
	gotoxy(WIN_WIDTH + 7, 7); cout << "Level: " << level << endl;
}

void updateHighScore() { //zobrazenie posledneho skore
	gotoxy(WIN_WIDTH + 7, 9);
	cout << "LastSCR:";
	highscore();
	cout << endl;
}

void levelCounter(int score) { //pocitadlo levelov v zavislosti od skore
	if (score >= 5 && score < 10) {
		level = 1;
	}
	else if (score >= 10 && score < 15) {
		level = 2;
	}
	else if (score >= 15 && score < 20) {
		level = 3;
	}
	else if (score >= 20 && score < 30) {
		level = 4;
	}
	else if (score >= 30) {
		level = 5;
	}

}
void TrainingLevelCounter(int score) {
	if (score >= 5 && score < 8) {
		level = 1;
	}
	else if (score >= 8 && score < 10) {
		level = 2;
	}
	else if (score >= 10 && score < 13) {
		level = 3;
	}
	else if (score >= 13 && score < 15) {
		level = 4;
	}
	else if (score >= 15 && score < 18) {
		level = 5;
	}
	else if (score >= 18 && score < 20) {
		level = 6;
	}
	else if (score >= 20 && score < 23) {
		level = 7;
	}
	else if (score >= 23 && score < 25) {
		level = 8;
	}
	else if (score >= 25 && score < 28) {
		level = 9;
	}
	else if (score >= 28 && score < 30) {
		level = 10;
	}
	else if (score >= 30 && score < 45) {
		level = 11;
	}
	else if (score >= 45 && score < 60) {
		level = 12;
	}
	else if (score >= 60) {
		level = 13;
	}

}

void instructions(){
	
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Press spacebar to make bird fly";
	cout<<"\n\nPress any key to go back to menu";
	int c = _getch();
}
void playTainingCamp() {

	birdPos = 6;
	score = 0;
	pipeFlag[0] = 1;
	pipeFlag[1] = 0;
	pipePos[0] = pipePos[1] = 4;


	system("cls");
	drawBorder();
	genPipe(0);
	updateScore();
	updateLevel();
	updateHighScore();

	gotoxy(WIN_WIDTH + 5, 2); cout << "FLAPPY BIRD";
	gotoxy(WIN_WIDTH + 6, 4); cout << "----------";
	gotoxy(WIN_WIDTH + 6, 6); cout << "----------";
	gotoxy(WIN_WIDTH + 6, 8); cout << "----------";
	gotoxy(WIN_WIDTH + 7, 12); cout << "Control ";
	gotoxy(WIN_WIDTH + 7, 13); cout << "-------- ";
	gotoxy(WIN_WIDTH + 2, 14); cout << " Spacebar = jump";

	gotoxy(10, 5); cout << "Press any key to start";
	int c = _getch();
	gotoxy(10, 5); cout << "                      ";

	while (1) {

		if (_kbhit()) {
			char ch = _getch();
			if (ch == 32) {
				if (birdPos > 3)
					birdPos -= 3;
			}
			if (ch == 27) {
				break;
			}
		}

		drawBird();
		drawPipe(0);
		drawPipe(1);
		if (collision() == 1) {
			gameover();
			scored(score);
			level = 0;
			return;
		}
		SleepTraining(score);
		eraseBird();
		erasePipe(0);
		erasePipe(1);
		birdPos += 1;

		if (birdPos > SCREEN_HEIGHT - 2) {
			gameover();
			scored(score);
			level = 0;
			return;
		}

		if (pipeFlag[0] == 1)
			pipePos[0] += 2;

		if (pipeFlag[1] == 1)
			pipePos[1] += 2;

		if (pipePos[0] >= 40 && pipePos[0] < 42) {
			pipeFlag[1] = 1;
			pipePos[1] = 4;
			genPipe(1);
		}
		if (pipePos[0] > 68) {
			score++;
			updateScore();
			TrainingLevelCounter(score);
			updateLevel();
			updateHighScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPos[0] = gapPos[1];
		}

	}

}

void playEasy() {

	birdPos = 6;
	score = 0;
	pipeFlag[0] = 1;
	pipeFlag[1] = 0;
	pipePos[0] = pipePos[1] = 4;


	system("cls");
	drawBorder();
	genPipe(0);
	updateScore();
	updateLevel();
	updateHighScore();

	gotoxy(WIN_WIDTH + 5, 2); cout << "FLAPPY BIRD";
	gotoxy(WIN_WIDTH + 6, 4); cout << "----------";
	gotoxy(WIN_WIDTH + 6, 6); cout << "----------";
	gotoxy(WIN_WIDTH + 6, 8); cout << "----------";
	gotoxy(WIN_WIDTH + 6, 10); cout << "----------";
	gotoxy(WIN_WIDTH + 7, 12); cout << "Control ";
	gotoxy(WIN_WIDTH + 7, 13); cout << "-------- ";
	gotoxy(WIN_WIDTH + 2, 14); cout << " Spacebar = jump";

	gotoxy(10, 5); cout << "Press any key to start";
	int c = _getch();
	gotoxy(10, 5); cout << "                      ";

	while (1) {
		
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 32) {
				if (birdPos > 3)
					birdPos -= 3;
			}
			if (ch == 27) {
				break;
			}
		}

		drawBird();
		drawPipeEasy(0);
		drawPipeEasy(1);
		if (collisionEasy() == 1) {
			gameover();
			scored(score);
			level = 0;
			return;
		}
		SleepEasy(score);
		eraseBird();
		erasePipeEasy(0);
		erasePipeEasy(1);
		birdPos += 1;

		if (birdPos > SCREEN_HEIGHT - 2) {
			gameover();
			scored(score);
			level = 0;
			return;
		}

		if (pipeFlag[0] == 1)
			pipePos[0] += 2;

		if (pipeFlag[1] == 1)
			pipePos[1] += 2;

		if (pipePos[0] >= 40 && pipePos[0] < 42) {
			pipeFlag[1] = 1;
			pipePos[1] = 4;
			genPipe(1);
		}
		if (pipePos[0] > 68) {
			score++;
			updateScore();
			levelCounter(score);
			updateLevel();
			updateHighScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPos[0] = gapPos[1];
			
		}
	}

}

void playMedium() {

	birdPos = 6;
	score = 0;
	pipeFlag[0] = 1;
	pipeFlag[1] = 0;
	pipePos[0] = pipePos[1] = 4;


	system("cls");
	drawBorder();
	genPipe(0);
	updateScore();
	updateLevel();
	updateHighScore();

	gotoxy(WIN_WIDTH + 5, 2); cout << "FLAPPY BIRD";
	gotoxy(WIN_WIDTH + 6, 4); cout << "----------";
	gotoxy(WIN_WIDTH + 6, 6); cout << "----------";
	gotoxy(WIN_WIDTH + 6, 8); cout << "----------";
	gotoxy(WIN_WIDTH + 7, 12); cout << "Control ";
	gotoxy(WIN_WIDTH + 7, 13); cout << "-------- ";
	gotoxy(WIN_WIDTH + 2, 14); cout << " Spacebar = jump";

	gotoxy(10, 5); cout << "Press any key to start";
	int c = _getch();
	gotoxy(10, 5); cout << "                      ";

	while (1) {

		if (_kbhit()) {
			char ch = _getch();
			if (ch == 32) {
				if (birdPos > 3)
					birdPos -= 3;
			}
			if (ch == 27) {
				break;
			}
		}

		drawBird();
		drawPipeMedium(0);
		drawPipeMedium(1);
		if (collisionMedium() == 1) {
			gameover();
			scored(score);
			level = 0;
			return;
		}
		SleepMedium(score);;
		eraseBird();
		erasePipeMedium(0);
		erasePipeMedium(1);
		birdPos += 1;

		if (birdPos > SCREEN_HEIGHT - 2) {
			gameover();
			scored(score);
			level = 0;
			return;
		}

		if (pipeFlag[0] == 1)
			pipePos[0] += 2;

		if (pipeFlag[1] == 1)
			pipePos[1] += 2;

		if (pipePos[0] >= 40 && pipePos[0] < 42) {
			pipeFlag[1] = 1;
			pipePos[1] = 4;
			genPipe(1);
		}
		if (pipePos[0] > 68) {
			score++;
			updateScore();
			levelCounter(score);
			updateLevel();
			updateHighScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPos[0] = gapPos[1];
		}

	}

}

void playHard() {

	birdPos = 6;
	score = 0;
	pipeFlag[0] = 1;
	pipeFlag[1] = 0;
	pipePos[0] = pipePos[1] = 4;


	system("cls");
	drawBorder();
	genPipe(0);
	updateScore();
	updateLevel();
	updateHighScore();

	gotoxy(WIN_WIDTH + 5, 2); cout << "FLAPPY BIRD";
	gotoxy(WIN_WIDTH + 6, 4); cout << "----------";
	gotoxy(WIN_WIDTH + 6, 6); cout << "----------";
	gotoxy(WIN_WIDTH + 6, 8); cout << "----------";
	gotoxy(WIN_WIDTH + 7, 12); cout << "Control ";
	gotoxy(WIN_WIDTH + 7, 13); cout << "-------- ";
	gotoxy(WIN_WIDTH + 2, 14); cout << " Spacebar = jump";

	gotoxy(10, 5); cout << "Press any key to start";
	int c = _getch();
	gotoxy(10, 5); cout << "                      ";

	while (1) {

		if (_kbhit()) {
			char ch = _getch();
			if (ch == 32) {
				if (birdPos > 3)
					birdPos -= 3;
			}
			if (ch == 27) {
				break;
			}
		}

		drawBird();
		drawPipeHard(0);
		drawPipeHard(1);
		if (collisionHard() == 1) {
			gameover();
			scored(score);
			level = 0;
			return;
		}
		SleepHard(score);
		eraseBird();
		erasePipeHard(0);
		erasePipeHard(1);
		birdPos += 1;

		if (birdPos > SCREEN_HEIGHT - 2) {
			gameover();
			scored(score);
			level = 0;
			return;
		}

		if (pipeFlag[0] == 1)
			pipePos[0] += 2;

		if (pipeFlag[1] == 1)
			pipePos[1] += 2;

		if (pipePos[0] >= 40 && pipePos[0] < 42) {
			pipeFlag[1] = 1;
			pipePos[1] = 4;
			genPipe(1);
		}
		if (pipePos[0] > 68) {
			score++;
			updateScore();
			levelCounter(score);
			updateLevel();
			updateHighScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPos[0] = gapPos[1];
		}


	}

}


void gamemode() {

	system("cls");
	gotoxy(10, 5); cout << " ------------------------- ";
	gotoxy(10, 6); cout << " |      GAME MODE       | ";
	gotoxy(10, 7); cout << " -------------------------";
	gotoxy(10, 9); cout << "1. Level Training Camp";
	gotoxy(10, 10); cout << "2. Level Easy";
	gotoxy(10, 11); cout << "3. Level Medium";
	gotoxy(10, 12); cout << "4. Level Hard";
	gotoxy(10, 14); cout << "Select mode and let`s play ! ";
	char game = _getch();
	if (game == '1') playTainingCamp();
	if (game == '2') playEasy();
	else if (game == '3') playMedium();
	else if (game == '4') playHard();

}
int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	
	
	do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |      FLAPPY BIRD       | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Game Modes";
		gotoxy(10,10); cout<<"2. Instructions";	 
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: "; 
		char op = _getch();
		
		if (op == '1') gamemode();

		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	} while (1);


	return 0;
}
