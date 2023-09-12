#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include "Tile.h"
#include "SmallClasses.h"

class Board {
	bool runMode;
	bool debugMode; 
	bool isPaused;	 
	bool leaderBoardOpen;
	int row;
	int col;
	int numMines;
public:
	Board();
	void SetCols(int);
	void SetRows(int);
	void SetNumMines(int);
	void StartGame();
	void EndGame();
	void DrawBoard(sf::RenderWindow& window, Tile** (&tile), Mines* (&mine), std::vector<Numbers>&, std::vector<Flags>&, std::vector<SetNum>&, std::vector<Buttons>&, bool, bool);
	void DrawRevealedTiles(sf::RenderWindow& window, Tile** (&rt), bool);
	void LinkTileNeighbors(Tile** (&t));
	void SetTilePositions(Tile** (&t));
	void SetMinePositions(Tile** (&t), Mines* (&m));
	int CheckMinePosition(Tile(&t), Mines* (&m));
	bool CheckMineDuplicates(std::vector<int>& randWidth, std::vector<int>& randHeight); 
	void SetNumberMines(std::vector<Numbers>&, Tile** (&t));
	void AddFlag(std::vector<Flags>&, Tile(&t));
	void RemoveFlag(std::vector<Flags>&, Tile(&t));
	void MakeNumVect(std::vector<SetNum>&);
	void MakeButtonsVect(std::vector<Buttons>&);
	void ChangeToPause(std::vector<Buttons>& buttons);
	void ChangeToPlay(std::vector<Buttons>& buttons); 
	bool GetIsPaused(); 
	void ChangePauseBool();
	bool GetGameState();
	void ResetBoard(std::vector<Numbers>&, std::vector<Flags>&, Tile** (&t), Mines* (&m));
	void SetDebugMode(bool);
	bool GetDebugMode();
	bool CheckWin(Tile** (&t), Mines* (&m), std::vector<Flags>&);
	bool GetLeaderOpen();
	void ChangeLeaderOpen();
};

