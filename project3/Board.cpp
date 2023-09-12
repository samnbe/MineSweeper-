#include "Board.h"
using namespace std;

Board::Board() {
	runMode = true;
	debugMode = false;
	isPaused = false;
	leaderBoardOpen = false;
	row = 0;
	col = 0;
	numMines = 0;
}

void Board::SetCols(int _col) {
	col = _col;
}

void Board::SetRows(int _row) {
	row = _row;
}

void Board::SetNumMines(int _mines) {
	numMines = _mines;
}

void Board::StartGame() {
	this->runMode = true;
}

void Board::EndGame() {
	this->runMode = false;
}

//draws whole board, tiles, buttons, mines, flags
void Board::DrawBoard(sf::RenderWindow& window, Tile** (&tile), Mines* (&mine), vector<Numbers>& nums, vector<Flags>& flags, vector<SetNum>& counts, vector<Buttons>& buttons, bool contGame, bool debugMode) {
	int index = 0;
	if (contGame) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				index = CheckMinePosition(tile[i][j], mine);
				if (index != -1 && tile[i][j].IsOpen()) {
					window.draw(tile[i][j].GetSprite());
					window.draw(mine[index].GetSprite());

				}
				else {
					window.draw(tile[i][j].GetSprite());
					for (unsigned int k = 0; k < nums.size(); k++) {
						if (tile[i][j].IsOpen()) {
							if (nums[k].spriteT.getPosition().x == tile[i][j].spriteT.getPosition().x && nums[k].spriteT.getPosition().y == tile[i][j].spriteT.getPosition().y)
								window.draw(nums[k].GetSprite());
						}
					}
				}
			}
		}

		if (CheckWin(tile, mine, flags)) {
			window.draw(buttons[2].GetSprite());
		}
		if (!CheckWin(tile, mine, flags)) {
			window.draw(buttons[0].GetSprite());
		}
	}
	
	

	if (!contGame || debugMode) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				index = CheckMinePosition(tile[i][j], mine);
				if (index != -1) {
					window.draw(tile[i][j].GetSprite());
					window.draw(mine[index].GetSprite());
				}
				else {
					window.draw(tile[i][j].GetSprite());
					for (unsigned int k = 0; k < nums.size(); k++) {
						if (tile[i][j].IsOpen()) {
							if (nums[k].spriteT.getPosition().x == tile[i][j].spriteT.getPosition().x && nums[k].spriteT.getPosition().y == tile[i][j].spriteT.getPosition().y)
								window.draw(nums[k].GetSprite());
						
						}
					}
				}
			}
		}
		if (!contGame) {
			window.draw(buttons[1].GetSprite());
		}
		if (CheckWin(tile, mine, flags)) {
			window.draw(buttons[2].GetSprite());
		}
	}

	for (unsigned int i = 0; i < flags.size(); i++) {
		window.draw(flags[i].GetSprite());
	}
	if (flags.size() <= (unsigned)numMines) {
		index = numMines - flags.size();
		counts[0].SetPosition(33, (((float)row + 0.5f) * 32) + 16);
		window.draw(counts[0].GetSprite());
		counts[index / 10].SetPosition(54, (((float)row + 0.5f) * 32) + 16);
		window.draw(counts[index / 10].GetSprite());
		counts[index % 10].SetPosition(75, (((float)row + 0.5f) * 32) + 16);
		window.draw(counts[index % 10].GetSprite());
	}
	else if (flags.size() > (unsigned)numMines) {
		counts[10].SetPosition(12, (((float)row + 0.5f) * 32) + 16);
		window.draw(counts[10].GetSprite());
		index = flags.size() - numMines;
		if (index >= numMines * 2) {
			counts[index / 100].SetPosition(33, (((float)row + 0.5f) * 32) + 16);
			window.draw(counts[index / 100].GetSprite());
			counts[(index / 10) % 10].SetPosition(54, (((float)row + 0.5f) * 32) + 16);
			window.draw(counts[(index / 10) % 10].GetSprite());
			counts[index % 10].SetPosition(75, (((float)row + 0.5f) * 32) + 16);
			window.draw(counts[index % 10].GetSprite());
		}
		else {
			counts[0].SetPosition(33, (((float)row + 0.5f) * 32) + 16);
			window.draw(counts[0].GetSprite());
			counts[index / 10].SetPosition(54, (((float)row + 0.5f) * 32) + 16);
			window.draw(counts[index / 10].GetSprite());
			counts[index % 10].SetPosition(75, (((float)row + 0.5f) * 32) + 16);
			window.draw(counts[index % 10].GetSprite());
		}
	}
	window.draw(buttons[3].GetSprite());
	window.draw(buttons[4].GetSprite());
	window.draw(buttons[5].GetSprite());
}

//draws the revealed tiles for the puase button functionality 
void Board::DrawRevealedTiles(sf::RenderWindow& window, Tile** (&revealedtile), bool contGame) {
	if (contGame) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (revealedtile[i][j].GetFakeReveal()) {
					window.draw(revealedtile[i][j].GetSprite());
				}
			}
		}
	}
}

//link the tiles to its neighboring tiles
void Board::LinkTileNeighbors(Tile** (&tile)) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (i == 0) {
				tile[i][j].neighbors[0] = nullptr;
				tile[i][j].neighbors[1] = nullptr;
				tile[i][j].neighbors[7] = nullptr;
				if (j == 0) {
					tile[i][j].neighbors[2] = &tile[0][1];
					tile[i][j].neighbors[3] = &tile[1][1];
					tile[i][j].neighbors[4] = &tile[1][0];
					tile[i][j].neighbors[5] = nullptr;
					tile[i][j].neighbors[6] = nullptr;
				}
				if (j != 0 && j != col - 1) {
					tile[i][j].neighbors[2] = &tile[i][j + 1];
					tile[i][j].neighbors[3] = &tile[i + 1][j + 1];
					tile[i][j].neighbors[4] = &tile[i + 1][j];
					tile[i][j].neighbors[5] = &tile[i + 1][j - 1];
					tile[i][j].neighbors[6] = &tile[i][j - 1];
				}
				if (j == col - 1) {
					tile[i][j].neighbors[6] = &tile[i][j - 1];
					tile[i][j].neighbors[5] = &tile[i + 1][j - 1];
					tile[i][j].neighbors[4] = &tile[i + 1][j];
					tile[i][j].neighbors[2] = nullptr;
					tile[i][j].neighbors[3] = nullptr;
				}
			}
			else if (i != 0 && i != row - 1) {
				if (j == 0) {
					tile[i][j].neighbors[0] = &tile[i - 1][j];
					tile[i][j].neighbors[1] = &tile[i - 1][j + 1];
					tile[i][j].neighbors[2] = &tile[i][j + 1];
					tile[i][j].neighbors[3] = &tile[i + 1][j + 1];
					tile[i][j].neighbors[4] = &tile[i + 1][j];
					tile[i][j].neighbors[5] = nullptr;
					tile[i][j].neighbors[6] = nullptr;
					tile[i][j].neighbors[7] = nullptr;
				}
				else if (j == col - 1) {
					tile[i][j].neighbors[0] = &tile[i - 1][j];
					tile[i][j].neighbors[1] = nullptr;
					tile[i][j].neighbors[2] = nullptr;
					tile[i][j].neighbors[3] = nullptr;
					tile[i][j].neighbors[4] = &tile[i + 1][j];
					tile[i][j].neighbors[5] = &tile[i + 1][j - 1];
					tile[i][j].neighbors[6] = &tile[i][j - 1];
					tile[i][j].neighbors[7] = &tile[i - 1][j - 1];
				}
				else if (j != 0 && j != col - 1) {
					tile[i][j].neighbors[0] = &tile[i - 1][j];
					tile[i][j].neighbors[1] = &tile[i - 1][j + 1];
					tile[i][j].neighbors[2] = &tile[i][j + 1];
					tile[i][j].neighbors[3] = &tile[i + 1][j + 1];
					tile[i][j].neighbors[4] = &tile[i + 1][j];
					tile[i][j].neighbors[5] = &tile[i + 1][j - 1];
					tile[i][j].neighbors[6] = &tile[i][j - 1];
					tile[i][j].neighbors[7] = &tile[i - 1][j - 1];
				}
			}
			else if (i == row - 1) {
				tile[i][j].neighbors[3] = nullptr;
				tile[i][j].neighbors[4] = nullptr;
				tile[i][j].neighbors[5] = nullptr;
				if (j == 0) {
					tile[i][j].neighbors[2] = &tile[i][j + 1];
					tile[i][j].neighbors[1] = &tile[i - 1][j + 1];
					tile[i][j].neighbors[0] = &tile[i - 1][j];
					tile[i][j].neighbors[6] = nullptr;
					tile[i][j].neighbors[7] = nullptr;
				}
				if (j != 0 && j != col - 1) {
					tile[i][j].neighbors[0] = &tile[i - 1][j];
					tile[i][j].neighbors[1] = &tile[i - 1][j + 1];
					tile[i][j].neighbors[2] = &tile[i][j + 1];
					tile[i][j].neighbors[6] = &tile[i][j - 1];
					tile[i][j].neighbors[7] = &tile[i - 1][j - 1];

				}
				if (j == col - 1) {
					tile[i][j].neighbors[0] = &tile[i - 1][j];
					tile[i][j].neighbors[7] = &tile[i - 1][j - 1];
					tile[i][j].neighbors[6] = &tile[i][j - 1];
					tile[i][j].neighbors[2] = nullptr;
					tile[i][j].neighbors[1] = nullptr;
				}
			}
		}
	}
}

//set each tile positon 
void Board::SetTilePositions(Tile** (&tile)) {
	float x = 0.0f;
	float y = 0.0f;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			tile[i][j].SetPosition((float)x, (float) y);
			x += 32.0f;
		}
		x = 0;
		y += 32.0f;
	}
}

//set mines randomly around board 
void Board::SetMinePositions(Tile** (&tile), Mines* (&mine)) {
	vector<int> randWidth;
	vector<int> randHeight;
	for (int i = 0; i < numMines; i++) {
		int height = SetRandom::RandInt(0, row - 1);
		randHeight.push_back(height);
		int width = SetRandom::RandInt(0, col - 1);
		randWidth.push_back(width);
	}
	if (CheckMineDuplicates(randWidth, randHeight)) {
		randWidth.clear();
		randHeight.clear();
		SetMinePositions(tile, mine);
	}
	else {
		for (int i = 0; i < numMines; i++) {
			mine[i].SetPosition(tile[randHeight[i]][randWidth[i]].spriteT.getPosition().x, tile[randHeight[i]][randWidth[i]].spriteT.getPosition().y);
			tile[randHeight[i]][randWidth[i]].SetMine();
		}
	}
}

//check if tile has mine 
int Board::CheckMinePosition(Tile(&tile), Mines* (&mine)) {
	for (int i = 0; i < numMines; i++) {
		if (tile.spriteT.getPosition().x == mine[i].spriteT.getPosition().x && tile.spriteT.getPosition().y == mine[i].spriteT.getPosition().y) {
			return i;
		}
	}
	return -1;
}

//checks if tile has multiple mines
bool Board::CheckMineDuplicates(vector<int>& randWidth, vector<int>& randHeight) {
	for (unsigned int i = 0; i < randHeight.size(); i++) {
		for (unsigned int j = i + 1; j < randHeight.size(); j++) {
			if (randHeight[i] == randHeight[j] && i != j) {
				if (randWidth[i] == randWidth[j]) {
					return true;
				}
			}
		}
	}
	return false;
}

//set number of surrounding mines for a tile 
void Board::SetNumberMines(vector<Numbers>& nums, Tile** (&tile)) {
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			count = tile[i][j].CheckNeighborTiles();
			if (count != 0) {
				if (!tile[i][j].IsMine()) {
					Numbers n(count);
					n.SetPosition(tile[i][j].spriteT.getPosition().x, tile[i][j].spriteT.getPosition().y);
					nums.push_back(n);
				}
			}
		}
	}
}

//adds flag 
void Board::AddFlag(std::vector<Flags>& flags, Tile& tile) {
	Flags f;
	f.SetPosition(tile.spriteT.getPosition().x, tile.spriteT.getPosition().y);
	flags.push_back(f);
	tile.PlaceFlag();
}

//removes flag
void Board::RemoveFlag(std::vector<Flags>& flags, Tile& tile) {
	for (unsigned int i = 0; i < flags.size(); i++) {
		if (flags[i].spriteT.getPosition().x == tile.spriteT.getPosition().x && flags[i].spriteT.getPosition().y == tile.spriteT.getPosition().y)
			flags.erase(flags.begin() + i);
	}
	tile.RemoveFlag();
}

//makes number vector 
void Board::MakeNumVect(std::vector<SetNum>& counts) {
	for (int i = 0; i <= 10; i++) {
		SetNum c(i);
		counts.push_back(c);
	}
}

//make buttons vector, sets all thier properties  
void Board::MakeButtonsVect(std::vector<Buttons>& buttons) {
	Buttons a("face_happy");
	a.SetPosition((((float)col / 2.0f) * 32) - 32, ((float)row + 0.5f)* 32);
	Buttons b("face_lose");
	b.SetPosition((((float)col / 2.0f) * 32) - 32, ((float)row + 0.5f) * 32);
	Buttons c("face_win");
	c.SetPosition((((float)col / 2.0f) * 32) - 32, ((float)row + 0.5f) * 32);
	Buttons d("debug");
	d.SetPosition(((float)col * 32) - 304, ((float)row + 0.5f) * 32);
	Buttons e("play");
	e.SetPosition(((float)col * 32) - 240, ((float)row + 0.5f) * 32);
	Buttons f("leaderboard");
	f.SetPosition(((float)col * 32) - 176, ((float)row + 0.5f) * 32);
	
	buttons.push_back(a);
	buttons.push_back(b);
	buttons.push_back(c);
	buttons.push_back(d);
	buttons.push_back(e);
	buttons.push_back(f);
}

//change button to pause 
void Board::ChangeToPause(std::vector<Buttons>& buttons) {
	Buttons e("pause");
	e.SetPosition(((float)col * 32) - 240, ((float)row + 0.5f) * 32);
	buttons[4] = e;
}

//change button to play 
void Board::ChangeToPlay(std::vector<Buttons>& buttons) {
	Buttons e("play");
	e.SetPosition(((float)col * 32) - 240, ((float)row + 0.5f) * 32);
	buttons[4] = e;
}

bool Board::GetIsPaused() {
	return this->isPaused;
}

void Board::ChangePauseBool() {
	isPaused = !isPaused;
}

bool Board::GetGameState() {
	return this->runMode;
}

//reset board properties, new vectors for mines, numbers
void Board::ResetBoard(std::vector<Numbers>& numbers, std::vector<Flags>& flags, Tile** (&tile), Mines* (&mine)) {
	numbers.clear();
	flags.clear();
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			tile[i][j].ResetTile();
	}
	SetMinePositions(tile, mine);
	SetNumberMines(numbers, tile);
	StartGame();
}

void Board::SetDebugMode(bool debug) {
	this->debugMode = debug;
}

bool Board::GetDebugMode() {
	return this->debugMode;
}

//checks if game is won
bool Board::CheckWin(Tile** (&tile), Mines* (&mine), vector<Flags>& flags) {
	int mineCount = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (tile[i][j].IsOpen() && CheckMinePosition(tile[i][j], mine) == -1)
				mineCount++;
		}
	}
	if (mineCount == (row * col) - numMines) {
		flags.clear();
		for (int i = 0; i < numMines; i++) {
			Flags f;
			f.SetPosition(mine[i].GetSprite().getPosition().x, mine[i].GetSprite().getPosition().y);
			flags.push_back(f);
		}
		return true;
	}
	else {
		return false;
	}
}

bool Board::GetLeaderOpen() {
	return leaderBoardOpen;
}

void Board::ChangeLeaderOpen() {
	this->leaderBoardOpen = !leaderBoardOpen;
}












