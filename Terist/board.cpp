#include "board.h"
#include "piece.h"
#include "menu.h"

Board::Board() {
	width = 10;
	height = 20;
	for (int i = 0; i < height; ++i) {
		vector<int> v(width, 0);
		gameBoard.push_back(v);
	}
}
Board::~Board() {
	for (int i = 0; i < height; ++i) {
		gameBoard[i].clear();
	}
	gameBoard.clear();
}
int Board::getG(int x, int y) const {
	x = (x - 1) / 2;
	y = y - 1 - top;
	if (x < 0 || x >= width || y >= height)
		return -1;
	if (y < 0)
		return 0;
	return gameBoard[y][x];
}
void Board::ShowBorder() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(0, top);
	cout << (char)186;
	gotoxy(1 + width * 2, top);
	cout << (char)186;

	for (int i = 0; i < height; ++i) {
		gotoxy(0, top + 1 + i);
		cout << (char)186;
		gotoxy(1 + width * 2, top + 1 + i);
		cout << (char)186;
	}

	gotoxy(0, bottom);
	cout << (char)200;
	for (int i = 0; i < width * 2; ++i) {
		gotoxy(1 + i, bottom);
		cout << (char)205;
	}
	gotoxy(1 + width * 2, bottom);
	cout << (char)188;

	for (int i = 0; i < 3; ++i) {
		gotoxy(25, top + 4 + i * 5);
		cout << i + 1 << ".";
	}
}
void Board::ShowBoard() {
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			gotoxy(1 + 2 * i, 1 + top + j);
			if (gameBoard[j][i] != 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gameBoard[j][i]);
				cout << block;
			}
			else
				cout << "  ";
		}
	}
}
void Board::ShowQueue() {
	for (int i = 1; i <= 3; ++i)
		pQueue[i]->PreShow(i);
}
void Board::UnShowQueue() {
	for (int i = 1; i <= 3; ++i)
		pQueue[i]->UnShow();
}
void Board::AddBoard(Piece* p) {
	pQueue[0]->UnShow();
	for (int i = 0; i < 4; ++i) {
		int _x = (p->getCMove(i).x - 1) / 2;
		int _y = p->getCMove(i).y - 1 - top;
		gameBoard[_y][_x] = p->getColor();
	}
}
bool Board::EndBoard(Piece* p) {
	for (int i = 0; i < 4; ++i) {
		if (p->getCMove(i).y <= top) {
			gotoxy(30, 6);
			cout << "end";
			return true;
		}
	}
	return false;
}
void Board::ScoreBoard(int& linePlus) {
	vector<vector<int>> gameBoard2(height, vector<int>(width, 0));
	bool fullRow = true;
	int countH = height - 1;
	for (int j = height - 1; (j >= 0) && (countH >= 0); --j) {
		fullRow = true;
		for (int i = 0; i < width; ++i) {
			fullRow = true;
			if (gameBoard[j][i] == 0) {
				fullRow = false;
				i = width;
			}
		}
		if (!fullRow) {
			gameBoard2[countH--] = gameBoard[j];
		}
	}
	linePlus = countH;
	gameBoard = gameBoard2;
}
void Board::GeneratePiece() {
	int type = rand() % 7;//chon ngau nhien cac piece de dua vao hang doi
	//int type = 3;
	if (type == 0) {
		Piece* p1 = new PieceI;
		pQueue.push_back(p1);
	}
	else if (type == 1) {
		Piece* p1 = new PieceO;
		pQueue.push_back(p1);
	}
	else if (type == 2) {
		Piece* p1 = new PieceJ;
		pQueue.push_back(p1);
	}
	else if (type == 3) {
		Piece* p1 = new PieceL;
		pQueue.push_back(p1);
	}
	else if (type == 4) {
		Piece* p1 = new PieceT;
		pQueue.push_back(p1);
	}
	else if (type == 5) {
		Piece* p1 = new PieceZ;
		pQueue.push_back(p1);
	}
	else if (type == 6) {
		Piece* p1 = new PieceS;
		pQueue.push_back(p1);
	}
}
void Board::DeletePieces() {
	for (int i = 0; i < pQueue.size(); ++i) {
		delete pQueue[i];
	}
	pQueue.clear();
}
void Board::Hold() {
	GeneratePiece();
	pQueue[1]->UnShow();
	pQueue[0]->PreShow(4);
	for (int i = 0; i < pQueue.size(); ++i) {
		pQueue[0]->UnShow();
	}
	pQueue.push_back(pQueue[0]);
	pQueue.erase(pQueue.begin());
	pQueue[0]->PreShow(5);
	pQueue[0]->MoveRight(*this);
	pQueue[0]->MoveLeft(*this);
	pQueue[0]->PreShow();
	pQueue[4]->PreShow(4);
	ShowQueue();
}
void Board::UnHold() {
	for (int i = 0; i <= top; ++i) {
		gotoxy(width * 2 + 2, i);
		cout << "                              ";
	}
	iter_swap(pQueue.begin(), pQueue.end() - 1);
	pQueue[4]->PreShow(4);
	pQueue[0]->PreShow(5);
}
void Board::Play() {
	ShowBorder();
	srand((unsigned)time(NULL));
	for (int i = 0; i < 4; ++i) {//hang doi gom 4 piece, cac piece se tuan tu roi xuong
		GeneratePiece();
	}
	ShowQueue();
	time_t originalTime = double(clock());
	time_t originalTimeBottom = double(clock());
	time_t nowTime = double(clock());
	double timeLeft = -1.0;
	double timeMax = 1.0;
	char keyboard = 'a';
	PauseGame* pauseGame = new PauseGame(false, 0);
	bool firstHold = true;
	bool isHold = false;
	int level = 1;
	int line = 0;
	pQueue[0]->PreShow();

	while (true) {
		if (timeLeft <= timeMax) {
			if (!pauseGame->getIsPausing() && !pQueue[0]->BottomCheck(*this)) {
				timeLeft = -1.0;
				originalTimeBottom = double(clock());
				pQueue[0]->MoveDownTime(*this, originalTime, level);
			}
			if (pQueue[0]->BottomCheck(*this) && timeLeft != -1.0) {//kiem tra xem piece co cham day hay chua
				nowTime = double(clock());
				timeLeft = ((double)nowTime - (double)originalTimeBottom) / double(CLOCKS_PER_SEC);
			}

			if (_kbhit())
			{
				char keyboard = _getch();
				if (!pauseGame->getIsPausing()) {
					if (!pQueue[0]->BottomCheck(*this) && timeLeft != -1.0) {
						originalTimeBottom = double(clock());
						originalTime = double(clock());
						timeLeft = -1.0;
						pQueue[0]->MoveDownTime(*this, originalTime, level);
					}
					else if (keyboard == 'm' && pQueue[0]->RotateCheck(*this, 1)) {
						pQueue[0]->RotateRight();
					}
					else if (keyboard == 'n' && pQueue[0]->RotateCheck(*this, 3)) {
						pQueue[0]->RotateLeft();
					}
					else if (keyboard == 'd') {
						pQueue[0]->MoveRight(*this);
					}
					else if (keyboard == 'a') {
						pQueue[0]->MoveLeft(*this);
					}
					else if (keyboard == 's') {
						pQueue[0]->MoveDown(*this);
					}
					else if (keyboard == 'h' && firstHold && !isHold) {
						firstHold = false;
						isHold = true;
						pQueue[0]->UnShow();
						this->Hold();
						pQueue[0]->PreShow();
					}
					else if (keyboard == 'h' && !firstHold && !isHold) {
						isHold = true;
						pQueue[0]->UnShow();
						this->UnHold();
					}
				}
				if (keyboard == 'p') {//Dung game
					pauseGame->setIsPausing();
					if (pauseGame->getIsPausing()) {
						pauseGame->MakeMenuTable();
						pauseGame->MakeTitle();
						pauseGame->ContentPauseGame();

					}
					else {//Tiep tuc game
						pauseGame->UnshownPause();
						originalTime = double(clock());
					}
				}
				if (keyboard == 'b') {
					this->DeletePieces();
					return;
				}
			}
		}
		if (pQueue[0]->BottomCheck(*this) && timeLeft == -1.0) {//kiem tra xem piece co cham day hay chua
			nowTime = double(clock());
			originalTimeBottom = double(clock());
			timeLeft = ((double)nowTime - (double)originalTimeBottom) / double(CLOCKS_PER_SEC);
		}
		if (timeLeft > timeMax) {
			if (EndBoard(pQueue[0]) && pQueue[0]->BottomCheck(*this))
				break;

			AddBoard(pQueue[0]);
			int linePlus = 0;
			ScoreBoard(linePlus);
			line += linePlus;
			if (line >= 10) {//Xoa 10 dong thi +1 level
				line -= 10;
				level++;
			}
			ShowBoard();

			delete pQueue[0];
			pQueue.erase(pQueue.begin());
			GeneratePiece();
			if (pQueue.size() > 4)
				iter_swap(pQueue.end() - 2, pQueue.end() - 1);

			originalTime = double(clock());
			ShowQueue();
			isHold = false;
			timeLeft = -1.0;
			originalTimeBottom = double(clock());
			originalTime = double(clock());
			pQueue[0]->PreShow();
			pQueue[1]->PreShow(1);
		}
	}
}