#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include "TextureManager.h"
#include "SmallClasses.h"
#include "Board.h"
using namespace std;

void setText(sf::Text& text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void OpenLeaderBoard(int rowLB, int colLB, Board& gameBoard, vector<Buttons>& buttons, sf::Vector2f mousePos, vector<string>& names, vector<string>& times, bool added, bool addedIndex) {

    unsigned int width = colLB * 16;
    unsigned int height = (rowLB * 16) + 50;

    sf::RenderWindow leader_window(sf::VideoMode(width, height), "LeaderBoard Window", sf::Style::Close);

    //leaderboard text 
    sf::Font font;
    sf::Text text;
    font.loadFromFile("files/font.ttf");
    text.setFont(font);
    text.setString("LEADERBOARD");
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setFillColor(sf::Color::White);
    setText(text, (float)width / 2.0f, (float)height / 2.0f - 120);

    //making 5 texts for the 5 leaders 
    sf::Text first;
    sf::Text second;
    sf::Text third;
    sf::Text fourth;
    sf::Text fifth;

    first.setFont(font);
    first.setCharacterSize(18);
    first.setStyle(sf::Text::Bold);
    first.setFillColor(sf::Color::White);
    first.setString("1.\t" + times[0] + "\t" + names[0]);
    setText(first, (float)width / 2.0f, ((float)height / 2.0f) - 60);

    second.setFont(font);
    second.setCharacterSize(18);
    second.setStyle(sf::Text::Bold);
    second.setFillColor(sf::Color::White);
    second.setString("2.\t" + times[1] + "\t" + names[1]);
    setText(second, (float)width / 2.0f, ((float)height / 2.0f) - 30);


    third.setFont(font);
    third.setCharacterSize(18);
    third.setStyle(sf::Text::Bold);
    third.setFillColor(sf::Color::White);
    third.setString("3.\t" + times[2] + "\t" + names[2]);
    setText(third, (float)width / 2.0f, ((float)height / 2.0f) - 0);


    fourth.setFont(font);
    fourth.setCharacterSize(18);
    fourth.setStyle(sf::Text::Bold);
    fourth.setFillColor(sf::Color::White);
    fourth.setString("4.\t" + times[3] + "\t" + names[3]);
    setText(fourth, (float)width / 2.0f, ((float)height / 2.0f) + 30);


    fifth.setFont(font);
    fifth.setCharacterSize(18);
    fifth.setStyle(sf::Text::Bold);
    fifth.setFillColor(sf::Color::White);
    fifth.setString("5.\t" + times[4] + "\t" + names[4]);
    setText(fifth, (float)width / 2.0f, ((float)height / 2.0f) + 60);


    //leaderboard window while
    while (leader_window.isOpen()) {
        //while the leaderboard is open, the timer pauses 
        //gameBoard.changePauseBool(); 
        //gameBoard.changeToPause(buttons); 
        sf::Event event;
        while (leader_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameBoard.ChangeLeaderOpen();    //leaderboard closes
                leader_window.close();

                //gameBoard.changePauseBool(); 
                //gameBoard.changeToPlay(buttons);
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //if leaderboard already is open 
                if (gameBoard.GetLeaderOpen()) {
                    gameBoard.ChangeLeaderOpen();    //leaderboard closes
                    if (buttons[5].GetSprite().getGlobalBounds().contains(mousePos)) {
                        leader_window.close();
                    }
                }
            }
        }

        if (added) {
            if (addedIndex == 0) {
                first.setString("1.\t" + times[0] + "\t" + names[0] + "*");
            }
            else if (addedIndex == 1) {
                second.setString("2.\t" + times[1] + "\t" + names[1] + "*");
            }
            else if (addedIndex == 2) {
                third.setString("3.\t" + times[2] + "\t" + names[2] + "*");
            }
            else if (addedIndex == 3) {
                fourth.setString("4.\t" + times[3] + "\t" + names[3] + "*");
            }
            else if (addedIndex == 4) {
                fifth.setString("5.\t" + times[4] + "\t" + names[4] + "*");
            }
        }

        //draw all the places 
        leader_window.clear(sf::Color::Blue);
        leader_window.draw(text);
        leader_window.draw(first);
        leader_window.draw(second);
        leader_window.draw(third);
        leader_window.draw(fourth);
        leader_window.draw(fifth);
        leader_window.display();
    }
}

void AddLeader(int num0, int num1, int num2, int num3, string username, vector<string>& namesLB, vector<string>& timesLB, bool& added, int& addedIndex) {

    string fullTime = to_string(num0) + to_string(num1) + ":" + to_string(num2) + to_string(num3);
    
    username.pop_back();

    int vectAdded;

    int min1;
    int min2;                         
    int sec1;
    int sec2;

    bool stop_while = true;

    int i = 0;

    //while (stop_while == true) {
    //    if (i == 5) {
    //        stop_while = false;
    //    }
    // 
    //    string str1(1, timesLB[i].at(0));
    //    string str2(1, timesLB[i].at(1));
    //    string str3(1, timesLB[i].at(3));
    //    string str4(1, timesLB[i].at(4));
    //    min1 = stoi(str1);
    //    min2 = stoi(str2);
    //    sec1 = stoi(str3);
    //    sec2 = stoi(str4);
    //    if (num0 < min1) {
    //        namesLB.insert(namesLB.begin() + i, username);          //if i = 0, add to beginning of vect; if i = 4, add to the fifth place of the vector 
    //        timesLB.insert(timesLB.begin() + i, fullTime);
    //        added = true; 
    //        stop_while = false;
    //    }
    //    else if (num0 == min1) {
    //        if (num1 < min2) {
    //            namesLB.insert(namesLB.begin() + i, username);
    //            timesLB.insert(timesLB.begin() + i, fullTime);
    //            added = true;
    //            stop_while = false;
    //        }
    //        else if (num1 == min2) {
    //            if (num2 < sec1) {
    //                namesLB.insert(namesLB.begin() + i, username);
    //                timesLB.insert(timesLB.begin() + i, fullTime);
    //                added == true;
    //                stop_while = false;
    //            }
    //            else if (num2 == sec1) {
    //                if (num3 < sec2) {
    //                    namesLB.insert(namesLB.begin() + i, username);
    //                    timesLB.insert(timesLB.begin() + i, fullTime);
    //                    added = true;
    //                    stop_while = false;
    //                }
    //            }
    //        }
    //    }
    //    i++;
    //    addedIndex = i;
    //}


    //for (int i = 0; i < 5; i++) {
    //    addedIndex = i;
    //    char char1 = timesLB[i].at(0);
    //    char char2 = timesLB[i].at(1);                         //.at(2) = ":"
    //    char char3 = timesLB[i].at(3);
    //    char char4 = timesLB[i].at(4);
    //    string str1(1, char1);
    //    string str2(1, char2);
    //    string str3(1, char3); 
    //    string str4(1, char4);
    //    min1 = stoi(str1); 
    //    min2 = stoi(str2);
    //    sec1 = stoi(str3); 
    //    sec2 = stoi(str4);
    //   /* cout << "time at " << i << ": " << timesLB[i] << endl;
    //    cout << "min1: " << min1 << endl;
    //    cout << "min2: " << min2 << endl;
    //    cout << "sec1: " << sec1 << endl;
    //    cout << "sec2: " << sec2 << endl;*/
    //    if (num0 < min1) {
    //        namesLB.insert(namesLB.begin() + i, username);          //if i = 0, add to beginning of vect; if i = 4, add to the fifth place of the vector 
    //        timesLB.insert(timesLB.begin() + i, fullTime);
    //        added = true;
    //        exit;
    //    }
    //    else if (num0 == min1) {
    //        if (num1 < min2) {
    //            namesLB.insert(namesLB.begin() + i, username);          
    //            timesLB.insert(timesLB.begin() + i, fullTime);
    //            added = true;
    //            exit;
    //        }
    //        else if (num1 == min2) {
    //            if (num2 < sec1) {
    //                namesLB.insert(namesLB.begin() + i, username);          
    //                timesLB.insert(timesLB.begin() + i, fullTime);
    //                added == true;
    //                exit;
    //            }
    //            else if (num2 == sec1) {
    //                if (num3 < sec2) {
    //                    namesLB.insert(namesLB.begin() + i, username);        
    //                    timesLB.insert(timesLB.begin() + i, fullTime);
    //                    added = true;
    //                    exit;
    //                }
    //            }
    //        }
    //    }
    //}

    ofstream WriteFile("files/leaderboard.txt");

    //if the time was good enough to be added to the list 
    if (added == true) {

        if (timesLB.size() > 5) {
            timesLB.erase(timesLB.end() - 1);
        }

        WriteFile << timesLB[0] << "," << namesLB[0] << endl;
        WriteFile << timesLB[1] << "," << namesLB[1] << endl;
        WriteFile << timesLB[2] << "," << namesLB[2] << endl;
        WriteFile << timesLB[3] << "," << namesLB[3] << endl;
        WriteFile << timesLB[4] << "," << namesLB[4] << endl;
    }

}


int main() {

    //cout << "hi" << endl; 

    //get row, col, and num of mines from Config file 
    fstream conFile("files/board_config.cfg");
    if (!conFile.is_open()) {
        cout << "file is not open" << endl;
    }
    int col;
    int row;
    int numMines;
    string line;

    std::getline(conFile, line);
    col = stoi(line);
    std::getline(conFile, line);
    row = stoi(line);
    std::getline(conFile, line);
    numMines = stoi(line);
    //numMines = 3;

    //set up board with properties
    Board gameBoard;
    gameBoard.SetCols(col);
    gameBoard.SetRows(row);
    gameBoard.SetNumMines(numMines);


    unsigned int width = 800;
    unsigned int height = 600;

    //total time (running the whole time)
    auto clock1 = chrono::high_resolution_clock::now();

    //run when game is paused 
    auto clock2 = chrono::high_resolution_clock::now();
    auto clock2Duration = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - clock2).count();

    //create map for the timer digits (TAs demo)
    map<int, sf::Sprite> clockDigits;

    sf::Texture digitsT;
    digitsT.loadFromFile("files/images/digits.png");
    sf::Sprite digits;
    digits.setTexture(digitsT);

    sf::IntRect zeroRect(0, 0, 21, 32);
    digits.setTextureRect(zeroRect);
    sf::Sprite zero = digits;
    clockDigits.emplace(0, zero);

    sf::IntRect oneRect(21, 0, 21, 32);
    digits.setTextureRect(oneRect);
    sf::Sprite one = digits;
    clockDigits.emplace(1, one);

    sf::IntRect twoRect(42, 0, 21, 32);
    digits.setTextureRect(twoRect);
    sf::Sprite two = digits;
    clockDigits.emplace(2, two);

    sf::IntRect threeRect(63, 0, 21, 32);
    digits.setTextureRect(threeRect);
    sf::Sprite three = digits;
    clockDigits.emplace(3, three);

    sf::IntRect fourRect(84, 0, 21, 32);
    digits.setTextureRect(fourRect);
    sf::Sprite four = digits;
    clockDigits.emplace(4, four);

    sf::IntRect fiveRect(105, 0, 21, 32);
    digits.setTextureRect(fiveRect);
    sf::Sprite five = digits;
    clockDigits.emplace(5, five);

    sf::IntRect sixRect(126, 0, 21, 32);
    digits.setTextureRect(sixRect);
    sf::Sprite six = digits;
    clockDigits.emplace(6, six);

    sf::IntRect sevenRect(147, 0, 21, 32);
    digits.setTextureRect(sevenRect);
    sf::Sprite seven = digits;
    clockDigits.emplace(7, seven);

    sf::IntRect eightRect(168, 0, 21, 32);
    digits.setTextureRect(eightRect);
    sf::Sprite eight = digits;
    clockDigits.emplace(8, eight);

    sf::IntRect nineRect(189, 0, 21, 32);
    digits.setTextureRect(nineRect);
    sf::Sprite nine = digits;
    clockDigits.emplace(9, nine);

    bool clockPaused = false;

    auto clock1Duration = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - clock1);
    int trueTime = clock1Duration.count();

    int clockMins = 0;
    int clockSecs = 0;

    if (!clockPaused) {
        trueTime = trueTime - clock2Duration;
        clockMins = trueTime / 60;
        clockSecs = trueTime % 60;
    }

    int num0 = clockMins / 10 % 10;
    int num1 = clockMins % 10;
    int num2 = clockSecs / 10 % 10;
    int num3 = clockSecs % 10;

    string username;

    while (true) {
        sf::RenderWindow window(sf::VideoMode(width, height), "Welcome Window", sf::Style::Close);

        //welcome text 
        sf::Font font;
        sf::Text text;
        font.loadFromFile("files/font.ttf");
        text.setFont(font);
        text.setString("WELCOME TO MINESWEEPER!");
        text.setCharacterSize(24);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        text.setFillColor(sf::Color::White);
        setText(text, (float)width / 2.0f, (float)height / 2.0f - 150);

        //enter name here text
        sf::Text text1;
        text1.setFont(font);
        text1.setString("Enter your name:");
        text1.setCharacterSize(20);
        text1.setStyle(sf::Text::Bold);
        text1.setFillColor(sf::Color::White);
        setText(text1, (float)width / 2.0f, (float)height / 2.0f - 75);

        //inputed text 
        sf::Text text2;
        text2.setFont(font);
        text2.setCharacterSize(18);
        text2.setFillColor(sf::Color::Yellow);
        text2.setString("|");
        setText(text2, (float)width / 2.0f, (float)height / 2.0f - 45);



        string inputed_text;

        //welcome window while
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return 0;
                }
                if (event.type == sf::Event::TextEntered) {
                    if (isalpha(event.text.unicode)) {
                        if (inputed_text.length() == 0) {
                            inputed_text += toupper(event.text.unicode);
                        }
                        else if (inputed_text.length() <= 9) {
                            inputed_text += tolower(event.text.unicode);
                        }
                    }
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::BackSpace) {
                        if (inputed_text.length() == 0) {
                            continue;
                        }
                        inputed_text.erase(inputed_text.length() - 1, 1);
                    }
                    if (event.key.code == sf::Keyboard::Enter) {
                        if (!inputed_text.length() == 0) {
                            window.close();
                            //open game window
                            break;
                        }
                    }
                }
            }
            username = text2.getString(); 
            text2.setString(inputed_text + "|");
            setText(text2, width / 2.0f, height / 2.0f - 45);
            window.clear(sf::Color::Blue);
            window.draw(text);
            window.draw(text1);
            window.draw(text2);
            window.display();
        }


        sf::RenderWindow game_window(sf::VideoMode(col * 32, (row * 32) + 100), "Minesweeper", sf::Style::Close);

        //make 2D array for tiles 
        Tile** tiles = new Tile * [row];
        for (int i = 0; i < row; i++)
            tiles[i] = new Tile[col];

        //make a sperate 2d array for the pause mode (cover the screen with revealed tiles)
        Tile** revealedTiles = new Tile * [row];
        for (int i = 0; i < row; i++) {
            revealedTiles[i] = new Tile[col];
            for (int j = 0; j < col; j++) {
                revealedTiles[i][j].SetSprite("tile_revealed");
            }
        }

        //make 1D array for mines
        Mines* mines = new Mines[numMines];

        //make 2D array for temp storage 
        char** store = new char* [row];
        for (int i = 0; i < row; i++)
            store[i] = new char[col];

        //make all vectors for all properties 
        sf::Event event;
        vector<Numbers> nums;
        vector<Flags> flags;
        vector<SetNum> counts;
        vector<Buttons> buttons;


        //read the leaderboard config file 
        ifstream ConFig;
        ConFig.open("files/board_config.cfg");
        string line;
        std::getline(ConFig, line, '\n');
        int colLB = stoi(line);
        std::getline(ConFig, line, '\n');
        int rowLB = stoi(line);

        //make vectors to store the leaderboard leaders and their times 
        vector<string> namesLB;
        vector<string> timesLB;

        fstream configFile("files/leaderboard.txt");

        for (int i = 0; i < 5; i++) { 
            std::getline(configFile, line, ','); 
            timesLB.push_back(line); 
            std::getline(configFile, line, '\n'); 
            namesLB.push_back(line); 
        }

        for (int i = 0; i < 5; i++) {
            cout << timesLB[i] << endl;
            cout << namesLB[i] << endl;
        }

        //bool and index for adding to the leaderboard 
        bool added = false;
        int addedIndex = 0;

        //setup board 
        gameBoard.MakeButtonsVect(buttons);
        gameBoard.MakeNumVect(counts);
        gameBoard.SetTilePositions(tiles);
        gameBoard.LinkTileNeighbors(tiles);
        gameBoard.SetMinePositions(tiles, mines);
        gameBoard.SetNumberMines(nums, tiles);

        //gameboard window while 
        while (game_window.isOpen()) {
            while (game_window.pollEvent(event)) {
                //if game window is closed; close the game window 
                if (event.type == sf::Event::Closed) {
                    game_window.close();
                    return 0;
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    //if left click on tile on board, reveal the tile 
                    //if it is a mine, end the game; if not, open the neighbor tiles 
                    //if game is paused, no buttons or the game can be clicked besides restart, leaderboard, and pause 
                    if (!gameBoard.GetIsPaused()) {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            sf::Vector2f mousePos = game_window.mapPixelToCoords(sf::Mouse::getPosition(game_window));
                            for (int i = 0; i < row; i++) {
                                for (int j = 0; j < col; j++) {
                                    if (tiles[i][j].spriteT.getGlobalBounds().contains(mousePos) && !tiles[i][j].IsFlag() && gameBoard.GetGameState()) {
                                        tiles[i][j].RevealTile();
                                        if (tiles[i][j].IsMine()) {
                                            gameBoard.EndGame();
                                        }
                                        else {
                                            tiles[i][j].OpenNeighborTiles();
                                        }
                                    }
                                }
                            }
                            //reset the board if smily face us clicked
                            if (buttons[1].GetSprite().getGlobalBounds().contains(mousePos)) {
                                gameBoard.ResetBoard(nums, flags, tiles, mines);
                                //total time (running the whole time)
                                clock1 = chrono::high_resolution_clock::now();

                                //run when game is paused 
                                clock2 = chrono::high_resolution_clock::now();
                                clock2Duration = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - clock2).count();
                            }
                            //turn debug mode on when button pressed
                            else if (buttons[3].GetSprite().getGlobalBounds().contains(mousePos) && !gameBoard.GetDebugMode() && !gameBoard.GetIsPaused() && !gameBoard.CheckWin(tiles, mines, flags)) {
                                gameBoard.SetDebugMode(true);
                            }
                            //turn debug mode off if it was already on and clicked
                            else if (buttons[3].GetSprite().getGlobalBounds().contains(mousePos) && gameBoard.GetDebugMode() && !gameBoard.GetIsPaused() && !gameBoard.CheckWin(tiles, mines, flags)) {
                                gameBoard.SetDebugMode(false);
                            }
                            //change play button to pause if cliceked
                            //pause game
                            else if (buttons[4].GetSprite().getGlobalBounds().contains(mousePos) && !gameBoard.GetIsPaused() && gameBoard.GetGameState() && !gameBoard.CheckWin(tiles, mines, flags)) {
                                clockPaused = !clockPaused;

                                if (clockPaused) {
                                    clock2 = chrono::high_resolution_clock::now();
                                }
                                else {
                                    auto clock3 = chrono::steady_clock::now();
                                    clock2Duration += chrono::duration_cast<chrono::seconds>(clock3 - clock2).count();
                                }

                                gameBoard.ChangePauseBool();
                                //cout << "here: " << gameBoard.GetIsPaused() << endl;
                                gameBoard.ChangeToPause(buttons);

                                if (gameBoard.GetIsPaused()) {
                                    for (int i = 0; i < row; i++) {
                                        for (int j = 0; j < col; j++) {
                                            revealedTiles[i][j].SetPosition((float)j * 32, (float)i * 32);
                                            revealedTiles[i][j].ChangeFakeReveal();
                                        }
                                    }
                                }
                            }
                            //change puase button to play if clicked
                            //unpause game
                            else if (buttons[4].GetSprite().getGlobalBounds().contains(mousePos) && gameBoard.GetIsPaused() && gameBoard.GetGameState() && !gameBoard.CheckWin(tiles, mines, flags)) {
                                gameBoard.ChangePauseBool();
                                //cout << "here1: " << gameBoard.GetIsPaused() << endl;

                                gameBoard.ChangeToPlay(buttons);

                                for (int i = 0; i < row; i++) {
                                    for (int j = 0; j < col; j++) {
                                        revealedTiles[i][j].SetPosition((float)j * 32, (float)i * 32);
                                        revealedTiles[i][j].ChangeFakeReveal();
                                    }
                                }
                            }
                            //if leaderboard window not already open
                            else if (!gameBoard.GetLeaderOpen()) {
                                if (buttons[5].GetSprite().getGlobalBounds().contains(mousePos)) {

                                    gameBoard.ChangeLeaderOpen();    //leaderbaord is now open 

                                    if (gameBoard.GetLeaderOpen()) {
                                        clockPaused = !clockPaused;

                                        if (clockPaused) {
                                            clock2 = chrono::high_resolution_clock::now();
                                        }
                                        else {
                                            auto clock3 = chrono::steady_clock::now();
                                            clock2Duration += chrono::duration_cast<chrono::seconds>(clock3 - clock2).count();
                                        }

                                    }

                                    OpenLeaderBoard(rowLB, colLB, gameBoard, buttons, mousePos, namesLB, timesLB, added, addedIndex);

                                    clockPaused = !clockPaused;

                                    if (clockPaused) {
                                        clock2 = chrono::high_resolution_clock::now();
                                    }
                                    else {
                                        auto clock3 = chrono::steady_clock::now();
                                        clock2Duration += chrono::duration_cast<chrono::seconds>(clock3 - clock2).count();
                                    }

                                    
                                }
                            }
                        }
                        //add flag to board if mouse is right clicked over tile 
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                            sf::Vector2f mousePos = game_window.mapPixelToCoords(sf::Mouse::getPosition(game_window));
                            for (int i = 0; i < row; i++) {
                                for (int j = 0; j < col; j++) {
                                    if (tiles[i][j].spriteT.getGlobalBounds().contains(mousePos) && !tiles[i][j].IsFlag() && !tiles[i][j].IsOpen() && gameBoard.GetGameState())
                                        gameBoard.AddFlag(flags, tiles[i][j]);
                                    else if (tiles[i][j].spriteT.getGlobalBounds().contains(mousePos) && !tiles[i][j].IsOpen() && tiles[i][j].IsFlag() && gameBoard.GetGameState())
                                        gameBoard.RemoveFlag(flags, tiles[i][j]);
                                }
                            }
                        }
                        break;
                    }
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        sf::Vector2f mousePos = game_window.mapPixelToCoords(sf::Mouse::getPosition(game_window));
                        if (buttons[1].GetSprite().getGlobalBounds().contains(mousePos)) {
                            gameBoard.ResetBoard(nums, flags, tiles, mines);
                            //total time (running the whole time)
                            clock1 = chrono::high_resolution_clock::now();

                            //run when game is paused 
                            clock2 = chrono::high_resolution_clock::now();
                            clock2Duration = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - clock2).count();
                        }
                        else if (buttons[4].GetSprite().getGlobalBounds().contains(mousePos) && !gameBoard.GetIsPaused() && !gameBoard.CheckWin(tiles, mines, flags)) {
                            gameBoard.ChangePauseBool();

                            gameBoard.ChangeToPause(buttons);
                        }
                        //change puase button to play if clicked
                        else if (buttons[4].GetSprite().getGlobalBounds().contains(mousePos) && gameBoard.GetIsPaused() && !gameBoard.CheckWin(tiles, mines, flags)) {
                            clockPaused = !clockPaused;

                            if (clockPaused) {
                                clock2 = chrono::high_resolution_clock::now();
                            }
                            else {
                                auto clock3 = chrono::steady_clock::now();
                                clock2Duration += chrono::duration_cast<chrono::seconds>(clock3 - clock2).count();
                            }

                            gameBoard.ChangePauseBool();

                            gameBoard.ChangeToPlay(buttons);

                            for (int i = 0; i < row; i++) {
                                for (int j = 0; j < col; j++) {
                                    revealedTiles[i][j].ChangeFakeReveal();
                                }
                            }
                            if (gameBoard.GetIsPaused()) {
                                for (int i = 0; i < row; i++) {
                                    for (int j = 0; j < col; j++) {
                                        revealedTiles[i][j].SetPosition((float)j * 32, (float)i * 32);
                                        revealedTiles[i][j].ChangeFakeReveal();
                                    }
                                }
                            }
                        }
                        //open leaderboard window, pause timer
                        //if leader isn't already open
                        else if (!gameBoard.GetLeaderOpen()) {

                            if (buttons[5].GetSprite().getGlobalBounds().contains(mousePos)) {
                                gameBoard.ChangeLeaderOpen();    //leaderbaord is now open 

                                if (gameBoard.GetLeaderOpen()) {
                                    clockPaused = !clockPaused;

                                    if (clockPaused) {
                                        clock2 = chrono::high_resolution_clock::now();
                                    }
                                    else {
                                        auto clock3 = chrono::steady_clock::now();
                                        clock2Duration += chrono::duration_cast<chrono::seconds>(clock3 - clock2).count();
                                    }

                                }

                                OpenLeaderBoard(rowLB, colLB, gameBoard, buttons, mousePos, namesLB, timesLB, added, addedIndex); 

                                clockPaused = !clockPaused;

                                if (clockPaused) {
                                    clock2 = chrono::high_resolution_clock::now();
                                }
                                else {
                                    auto clock3 = chrono::steady_clock::now();
                                    clock2Duration += chrono::duration_cast<chrono::seconds>(clock3 - clock2).count();
                                }

                               
                            }
                        }
                    }
                }
            }
            //window drawn from what the user clicked on 
            game_window.clear(sf::Color::White);
            gameBoard.DrawBoard(game_window, tiles, mines, nums, flags, counts, buttons, gameBoard.GetGameState(), gameBoard.GetDebugMode());
            //draw 2D array of revealed tiles over board when paused 
            gameBoard.DrawRevealedTiles(game_window, revealedTiles, gameBoard.GetGameState());

            auto clock1Duration = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - clock1);
            int trueTime = clock1Duration.count();

            int clockMins = 0;
            int clockSecs = 0;

            if (!clockPaused) {
                trueTime = trueTime - clock2Duration;
                clockMins = trueTime / 60;
                clockSecs = trueTime % 60;
            }

            int num0 = clockMins / 10 % 10;
            int num1 = clockMins % 10;
            int num2 = clockSecs / 10 % 10;
            int num3 = clockSecs % 10;

            if (gameBoard.CheckWin(tiles, mines, flags)) {
                AddLeader(num0, num1, num2, num3, username, namesLB, timesLB, added, addedIndex);
            }

            if (!gameBoard.GetGameState() || gameBoard.CheckWin(tiles, mines, flags)) {
                num0 = num1 = num2 = num3 = 0;
            }

            clockDigits[num0].setPosition(((float)col * 32) - 97, 32 * ((float)row + 0.5f) + 16);
            game_window.draw(clockDigits[num0]);

            clockDigits[num1].setPosition(((float)col * 32) - 76, 32 * ((float)row + 0.5f) + 16);
            game_window.draw(clockDigits[num1]);

            clockDigits[num2].setPosition(((float)col * 32) - 54, 32 * ((float)row + 0.5f) + 16);
            game_window.draw(clockDigits[num2]);

            clockDigits[num3].setPosition(((float)col * 32) - 33, 32 * ((float)row + 0.5f) + 16);
            game_window.draw(clockDigits[num3]);



            game_window.display();

        } //while game window is open loop 
    } //while(true) loop

    TextureManager::Clear();
    return 0;
}
