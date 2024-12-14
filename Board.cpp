//HARLEY RICHARDSON, ALEXANDER SCHLUNT

#include <iostream>

#include "Board.h"
#include "player.h"
#include "battles.h"

#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m" /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0) */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define RESET "\033[0m"

Tile Board::getTile(int track, int _index){
    return _tiles[track][_index];
}

int Board::getPlayerTrack(int player_index){
    return _player_track[player_index];
}

void Board::initializeBoard()
{
    // Seed random number generator in your main function once
    for (int i = 0; i < 2; i++)
    {
        initializeTiles(i); // This ensures each lane has a unique tile distribution
    }
}

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iostream>

void Board::initializeTiles(int track_index)
{
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    // Keep track of green tile positions to ensure we place exactly 30 greens
    for (int i = 0; i < total_tiles; i++)
    {
        temp.wisdom_amt = 0;
        temp.military_power_amt = 0;
        temp.rations_amt = 0;

        if (i == total_tiles - 1)
        {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        }
        else if (i == 0)
        {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'Y';
        }
        else if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count))
        {
            temp.color = 'G';
            green_count++;
        }
        else
        {
            // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
            int color_choice = rand() % 5;
            switch (color_choice)
            {
            case 0:
                temp.color = 'B'; // Blue
                temp.description = "You have found yourself out of enemy lines,\nand can finally rest.";
                temp.rations_amt = 200;
                temp.military_power_amt = 200;
                temp.wisdom_amt = 200;

                break;
            case 1:
                temp.color = 'P'; // Pink
                temp.description = "Your speech has energized the masses,\nas well as talented advisors.";
                temp.rations_amt = 300;
                temp.military_power_amt = 300;
                temp.wisdom_amt = 300;
                break;
            case 2:
                temp.color = 'N'; // Brown
                temp.description = "You just recieved word that a supply line has been cut! You must back out!";
                temp.rations_amt = -300;
                break;
            case 3:
                temp.color = 'R'; // Red
                temp.description = "You've fallen into an ambush. Luckily, you escaped, but not\neveryone was so lucky.";
                temp.wisdom_amt = -100;
                temp.rations_amt = -100;
                temp.military_power_amt = -100;
                break;
            case 4:
                temp.color = 'U'; // Purple(Battle Square)
                break;
            }
        }

        // Assign the tile to the board for the specified lane
        _tiles[track_index][i] = temp;
    }
}

// Board::Board()
// {
//     _player_count = 1;

//     // Initialize player position
//     _player_position[0] = 0;

//     // Initialize tiles
//     initializeTiles();
// }

Board::Board(){
    return;
}

Board::Board(int player_count)
{
    if (player_count > _MAX_PLAYERS)
    {
        _player_count = _MAX_PLAYERS;
    }
    else
    {
        _player_count = player_count;
    }

    // Initialize player position
    for (int i = 0; i < _player_count; i++)
    {
        _player_position[i] = 0;
    }

    // Initialize tiles

    initializeBoard();

    //seed the spinner
    srand(time(0));
}

void Board::setPlayerPosition(int player_index, int pos){
    _player_position[player_index] = pos;
}

bool Board::isPlayerOnTile(int track_index, int pos, int player_index)
{
    if (_player_position[player_index] == pos && _player_track[player_index] == track_index)
    {
        return true;
    }
    return false;
}

void Board::displayTile(int track_index, int pos)
{
    // string space = "                                       ";
    std::string color = "";

    int player_1 = isPlayerOnTile(track_index, pos, 0);
    int player_2 = isPlayerOnTile(track_index, pos, 1);

    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <std::endl>

    // Determine color to display
    if (_tiles[track_index][pos].color == 'R')
    {
        color = RED;
    }
    else if (_tiles[track_index][pos].color == 'G')
    {
        color = GREEN;
    }
    else if (_tiles[track_index][pos].color == 'B')
    {
        color = BLUE;
    }
    else if (_tiles[track_index][pos].color == 'U')
    {
        color = PURPLE;
    }
    else if (_tiles[track_index][pos].color == 'N')
    {
        color = BROWN;
    }
    else if (_tiles[track_index][pos].color == 'P')
    {
        color = PINK;
    }
    else if (_tiles[track_index][pos].color == 'O')
    {
        color = ORANGE;
    }
    else if (_tiles[track_index][pos].color == 'Y')
    {
        color = GREY;
    }

    if (player_1 == true && player_2 == true)
    {
        std::cout << color << "|" << "1&2" << "|" << RESET;
    }
    else if (player_1 == true){
        std::cout << color << "|" << "1" << "|" << RESET;
    }
    else if (player_2 == true){
        std::cout << color << "|" << "2" << "|" << RESET;
    }
    else
    {
        std::cout << color << "| |" << RESET;
    }
}

void Board::displayTrack(int track_index)
{
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        displayTile(track_index, i);
    }
    std::cout << std::endl;
}

void Board::displayBoard()
{
    for (int i = 0; i < 2; i++)
    {
        displayTrack(i);
        if (i == 0)
        {
            std::cout << std::endl; // Add an extra line between the two lanes
        }
    }
}

bool Board::movePlayer(int track_index){
     // Increment player position
     _player_position[track_index]++;
     if (_player_position[track_index] == _BOARD_SIZE - 1)
     {
         // Player reached last tile
         return true;
     }
     return false;
}

int Board::getPlayerPosition(int track_index){
     if (track_index >= 0 && track_index <= _player_count){
         return _player_position[track_index];
     }
     return -1;
}

void Board::setPlayerTrack(int player_index, int track){
    _player_track[player_index] = track;
}

int Board::spinWheel(int player_index){
    int spin_spaces = (rand() % 6) + 1;
    std::cout << "spin spaces: " << spin_spaces << "\n";

    for (int i = 1; i <= spin_spaces; i++){
        movePlayer(player_index);
    }
    return spin_spaces;
}

#define __MAIN__
#ifdef __MAIN__

//GAME STATES

enum GameStates{
    GS_MENU_MAIN,
    GS_CHARACTER_SELECTION,
    GS_PATH_SELECTION,
    GS_ADVISOR_SELECTION,
    GS_BOARD,
    GS_BOARD_MOVE,
    GS_LEADERBOARD,

    //Battle
    GS_BATTLE,
    GS_UNIT_SELECTION,

    //End
    GS_TALLY_POINTS,
};

//Game Class
class Game{
    private:
        static const int NUM_PLAYERS = 2;
        static const int NUM_UNITS = 3;
        Player players[NUM_PLAYERS];

    public:
        Board board;
        std::vector<SpecialUnit> units[NUM_PLAYERS];

        void addUnit(int player_index, int unit_type);
        void printUnits(int player_index);
        SpecialUnit getUnit(int player_index, int unit_index);
        void addRandomUnit(int player_index);
        void battle();
        void init();
        void showLeaderboardSorted();
        void addtoLeaderboard(std::string name, int final_points);
        void gameLoop(int game_state, int player_index);
        void clearScreen();
        void waitForEnter();

        int getCharacterFromMenu(int player_index, int excluded_line);
        void getAdvisorFromMenu(int player_index);
        void doRandomEvent(int player_index);

        //Tiles
        void doTileEffects(int player_index, int player_prev_pos);

        //Assets

        std::string titleCard =     "///////////////////////////////////////////////////////////////////////////////////////////////////////////\n"
                                    "                                                                                                           \n"
                                    "                #     #                                #     #                  ### ### ###                \n"
                                    "                #  #  #  ####  #####  #      #####     #  #  #   ##   #####      #   #   #                 \n"
                                    "                #  #  # #    # #    # #      #    #    #  #  #  #  #  #    #     #   #   #                 \n"
                                    " ##### #####    #  #  # #    # #    # #      #    #    #  #  # #    # #    #     #   #   #     ##### ##### \n"
                                    "                #  #  # #    # #####  #      #    #    #  #  # ###### #####      #   #   #                 \n"
                                    "                #  #  # #    # #   #  #      #    #    #  #  # #    # #   #      #   #   #                 \n"
                                    "                 ## ##   ####  #    # ###### #####      ## ##  #    # #    #    ### ### ###                \n"
                                    "                                                                                                           \n"
                                    "///////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
};

void Game::init(){
    Board _board(NUM_PLAYERS);
    board = _board;
    board.initializeBoard();
}

void Game::addtoLeaderboard(std::string name, int final_score){
    std::ofstream file;
    file.open("leaderboard.txt",std::ios::app);
    file << "\n" << name << "|" << final_score << "\n";
    file.close();
}

//////////////
/////////////

//Battles 

void Game::printUnits(int player_index){
    std::cout << "-{ Units }-\n";
    for (int i = 0; i < units[player_index].size(); i++){
        std::cout << i+1;
        units[player_index][i].printStats();
        std::cout << "\n";
    }
}

void Game::addUnit(int player_index, int unit_type){
    SpecialUnit unit(unit_type);
    units[player_index].push_back(unit);
}

void Game::addRandomUnit(int player_index){
    int selection = rand() % 3;
    addUnit(player_index, selection);
}

void Game::battle(){
    std::cout << "Random Units from each side will be picked. Loser loses 250 military power.";

    if (units[0].size() == 0 || units[1].size() == 0){
        std::cout << "A player(s) does not have units.\n";

        if (units[0].size() == 0 && units[1].size() == 0){
            std::cout << "Both Players have no units. Nothing happens.\n";
            return;
        }
        if (units[0].size() == 0){
            std::cout << "Player 1 has no units. Player 1 loses automatically\n";
        }
        else if (units[1].size() == 0){
            std::cout << "Player 2 has no units. Player 1 loses automatically\n";
        }
    } 

    int player_1_choice = rand() % units[0].size();
    int player_2_choice = rand() % units[1].size();

    Battle fight(units[0][player_1_choice], units[1][player_2_choice]);
    fight.showUnits();
    
    while (fight.getUnit(0).getHealth() > 0 && fight.getUnit(1).getHealth() > 0){
        fight.fight();
        fight.showUnits();

        if (fight.getUnit(0).getHealth() <= 0){
            std::cout << "Player 1 has lost the battle.\n";
            players[0].addMilitaryPower(-250);
        }
        else if (fight.getUnit(1).getHealth() <= 0){
            std::cout << "Player 2 has lost the battle.\n";
            players[1].addMilitaryPower(-250);
        }

        std::cin.clear();
        std::cin.ignore(1000,'\n');
        waitForEnter();
    }
}

/////////////
/////////////



//SORTING ALGORITHM THING!!!
void Game::showLeaderboardSorted(){
    std::ifstream file("leaderboard.txt");
    std::string line;

    std::getline(file, line); // just to put it on the second line

    struct leaderboardEntry{
        int value;
        std::string name;
    };

    std::vector<leaderboardEntry> leaderboard;

    while (std::getline(file, line)){
        leaderboardEntry temp;
        
        temp.name = line.substr(0,line.find('|'));
        temp.value = stoi(line.substr(line.find('|')+1,line.length()));

        leaderboard.push_back(temp);
    }

    //BUBBLE SORT TIME!!!
    for (int i = 0; i < leaderboard.size()-1;i++){
        for (int j = 0; j < leaderboard.size()-1;j++){
            if (leaderboard[j].value < leaderboard[j+1].value){
                leaderboardEntry temp = leaderboard[j];
                leaderboard[j] = leaderboard[j+1];
                leaderboard[j+1] = temp;
            }
        }
    }

    //print out all contents.
    for (int i = 0; i < leaderboard.size(); i++){
        std::cout << i+1 << " | " << leaderboard[i].name << " | " << leaderboard[i].value << "\n";
    }
}

//////////////////////////////
/////////////////////////////

//RANDOM EVENTS

void Game::doRandomEvent(int player_index){

    //elements
    std::string description;
    int path_type;
    int advisor;
    int merit;


    std::ifstream event_file("random_events.txt");
    std::string line;
    int lines = -1;

    while (std::getline(event_file, line)){
        lines ++;
    }
    event_file.close();
    event_file.open("random_events.txt");

    int random_num = rand() % lines + 1;
    std::cout << random_num << "\n";

    int i= -1;
    while (std::getline(event_file, line)){
        i++;
        if (i == random_num){
            description = line.substr(0,line.find('|'));
            line = line.substr(line.find('|')+1,line.length());

            path_type = stoi(line.substr(0,line.find('|')));
            line = line.substr(line.find('|')+1,line.length());

            advisor = stoi(line.substr(0,line.find('|')));
            line = line.substr(line.find('|')+1,line.length());

            merit = stoi(line.substr(0,line.length()));
        }
    }

    event_file.close();

    //Applying everything

    if (path_type != board.getPlayerTrack(player_index) && path_type != 0){
        std::cout << "--------------------------------------------------------------\n";
        std::cout << "You continue your trek.\n";
        std::cout << "--------------------------------------------------------------\n";
        return;
    }

    std::cout << "--------------------------------------------------------------\n";
    std::cout << "Event: " << description << "\n";
    std::cout << "--------------------------------------------------------------\n";
    
    for (int i=0; i < players[player_index].advisors.size(); i++){
        if (players[player_index].advisors[i].getId() == advisor){
            std::cout << players[player_index].advisors[i].getName() << " Has protected you with ";
            std::cout << players[player_index].advisors[i].getDescription() << "\n";
            return;
        }
    }
    players[player_index].addMerit(merit);

    if (merit < 0){
        std::cout << "You've lost " << abs(merit) << " merit!\n";
    }
    else{
        std::cout << "You've gained " << merit << " merit!\n";
    }
}

/////////////////////////////
////////////////////////////

//LMAO THIS IS A "CLEAR SCREEN" ALRIGHT
void Game::clearScreen() {
    int i = 0;

    while (i < 200){ //OOOOO MAGIC NUMBER
        std::cout << std::endl;
        i++;
    }
}

void Game::waitForEnter(){
    std::cout << "Press enter to continue:\n";
    std::getchar();
}

//////      TILES       //////

void Game::doTileEffects(int player_index, int player_prev_pos){
    Tile tile;
    tile = board.getTile(board.getPlayerTrack(player_index), board.getPlayerPosition(player_index));
    
    players[player_index].addMilitaryPower(tile.wisdom_amt);
    players[player_index].addRations(tile.military_power_amt);
    players[player_index].addWisdom(tile.rations_amt);

    if (tile.color != 'G'){
            std::cout << "----------------------------------------------------------\n";
            std::cout << tile.description << "\n";
            std::cout << "----------------------------------------------------------\n";
    }

    switch (tile.color){
        case 'P':{
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            waitForEnter();

            int selection = rand() % 2;

            if (selection == 0){
                gameLoop(GS_ADVISOR_SELECTION, player_index);
            }
            else if(selection == 1){
                gameLoop(GS_UNIT_SELECTION, player_index);
            }
        }
        break;
        case 'B':{
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            waitForEnter();

            gameLoop(GS_MENU_MAIN, player_index);
        }
        break;
        case 'N':{
            board.setPlayerPosition(player_index, board.getPlayerPosition(player_index)-player_prev_pos);
        }
        break;
        case 'R':{
            board.setPlayerPosition(player_index,board.getPlayerPosition(player_index)-10);
            if (board.getPlayerPosition(player_index) < 0){
                board.setPlayerPosition(player_index, 0);
            }
        }
        break;
        case 'U':{
            battle();
            gameLoop(GS_MENU_MAIN, player_index);
        }
        break;
        case 'G':{
            doRandomEvent(player_index);
        }
        break;
    }
}

void Game::getAdvisorFromMenu(int player_index){
    std::ifstream advisor_file("advisors.txt");
    std::string line;
    int line_num = -1;
    int advisor_selection;

    while (std::getline(advisor_file, line)){
        line_num++;
        if (line_num > 0){
            std::cout << line_num << ". " << line << "\n";
        }
        else{
            std::cout << line << "\n";
        }
    }

    while (!(std::cin >> advisor_selection) || advisor_selection > line_num || advisor_selection < 1){
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        std::cout << "[Invalid Input]: Input one of the options above.\n";
    }

    players[player_index].addAdvisor("advisors.txt", advisor_selection);
    std::cin.clear();
    std::cin.ignore(1000,'\n');
    clearScreen();
}

int Game::getCharacterFromMenu(int player_index, int excluded_line){
    clearScreen();
    int player_selection;

    std::string line;
    int line_num = -1;

    std::ifstream character_file("characters.txt");

    while (std::getline(character_file, line)){
        line_num += 1;
        if (line_num != excluded_line){
            if (line_num > 0){
                std::cout << line_num << ": " << line << "\n";
            }
            else{
                std::cout << line << "\n";
            }
        }
    }

    //Input Sanitization
    while (!(std::cin >> player_selection) || player_selection == excluded_line || player_selection > line_num || player_selection < 1){
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        std::cout << "[Invalid Input]: Input one of the options above.\n";
    }

    players[player_index].getCharacterFromFile("characters.txt", player_selection);
    players[player_index].printStats();

    std::cin.clear();
    std::cin.ignore(1000,'\n');
    waitForEnter();

    return player_selection;
}


void Game::gameLoop(int game_state, int player_index = 0){
    clearScreen();
    switch (game_state){
        case GS_CHARACTER_SELECTION:{
            int excluded_character = -1; // -1 is no character
            for (int i = 0; i < 2; i++){
                std::cout << "-- Player " << i+1 << ": Select a character --\n";
                std::cout << "Characters: \n";
                excluded_character = getCharacterFromMenu(i, excluded_character);
                clearScreen();
            }
        
            gameLoop(GS_PATH_SELECTION);
        }
        break;
        case GS_PATH_SELECTION:{
            int selected_path; //1 is the academy, two is straight to leadership
            for (int i = 0; i < 2; i++){
                std::cout << "--" << players[i].getName() << ": Select a path --\n";
                std::cout << "Paths: \n";
                std::cout << "1. Go to academy.\n";
                std::cout << "\t Strong leaders are well prepared. spend some\n";
                std::cout << "\t resources to enter an academy, and get an advisor\n";
                std::cout << "\t to aid you.\n\n";
                std::cout << "2. Straight to leadership.\n";
                std::cout << "\t Strong leaders are quick and decisive. Venture\n";
                std::cout << "\t forth alone, spreading your name as a fearsome\n";
                std::cout << "\t leader\n";

                while (!(std::cin >> selected_path) || selected_path > 2 || selected_path < 1){
                    std::cin.clear();
                    std::cin.ignore(1000,'\n');
                    std::cout << "[Invalid Input]: Input one of the options above.\n";
                }

                clearScreen();

                if (selected_path == 1){
                    board.setPlayerTrack(i,0);
                    players[i].addMerit(-5000);
                    players[i].printStats();
                    gameLoop(GS_UNIT_SELECTION, i);
                    players[i].printAdvisors(false);
                }
                else if (selected_path == 2){
                    board.setPlayerTrack(i,1);
                    players[i].addMerit(2500);
                    players[i].addMilitaryPower(200);
                    players[i].printStats(); 

                    std::cin.clear();
                    std::cin.ignore(1000,'\n');
                    waitForEnter();
                }
                clearScreen();
            }
            gameLoop(GS_BOARD, 0);
        }
        break;
        case GS_ADVISOR_SELECTION:{
            getAdvisorFromMenu(player_index);
        }
        break;
        case GS_BOARD:{
            board.displayBoard();

            std::cin.clear();
            std::cin.ignore(1000,'\n');
            waitForEnter();

            clearScreen();
            gameLoop(GS_MENU_MAIN, player_index);
        }
        break;
        case GS_UNIT_SELECTION:{
            SpecialUnit tank(UT_TANK);
            SpecialUnit plane(UT_PLANE);
            SpecialUnit antiAir(UT_ANTIAIR);

            std::cin.clear();
            std::cin.ignore(1000,'\n');
            
            std::cout << "\nSelect a unit to add to your army!";
            std::cout << "1. \n";
            tank.printStats();
            std::cout << "2. \n";
            plane.printStats();
            std::cout << "3. \n";
            antiAir.printStats();

            int selection;

            while (!(std::cin >> selection) || selection > 3 || selection < 1){
                std::cin.clear();
                std::cin.ignore(1000,'\n');
                std::cout << "[Invalid Input]: Input one of the options above.\n";
            }

            SpecialUnit unit(selection-1);
            units[player_index].push_back(unit);
        }
        break;
        case GS_TALLY_POINTS:{
            /*Conversion rates:
                Military power = 4x
                Rations = 3x
                Wisdom = 2x
            */

            std::cin.clear();
            std::cin.ignore(1000,'\n');

            int total_merit_p1;
            int total_merit_p2;

            int first_bonus = 2000;

            //Player 1
            std::cout << "Player " << 1 << ": " << players[0].getName() << "\n";
            std::cout << "\t Military Power: " << players[0].getMilitaryPower() << " | 4x\n";
            std::cout << "\t Rations: " << players[0].getRations() << " | 3x\n";
            std::cout << "\t Wisdom: " << players[0].getWisdom() << " | 2x\n";
            std::cout << "\t Base Merit: " << players[0].getMerit()  << " | x\n";
            if (player_index == 0){
                std::cout << "\t First Bonus: " << first_bonus << "\n";
            }

            std::cin.clear();
            std::cin.ignore(1000,'\n');
            waitForEnter();

            std::cout << "Player " << 1 << ": " << players[0].getName() << "\n";
            std::cout << "\t __CONVERTED__: " << players[0].getMilitaryPower() * 4 << "\n";
            std::cout << "\t __CONVERTED__: " << players[0].getRations() * 3 << "\n";
            std::cout << "\t __CONVERTED__: " << players[0].getWisdom() * 2 << "\n";
            std::cout << "\t Base Merit: " << players[0].getMerit() << "\n";
            std::cout << "___________________________________________________________\n";

            total_merit_p1 = (
                (players[player_index].getMilitaryPower() * 4)+
                (players[player_index].getRations() * 3)+
                (players[player_index].getWisdom() * 2)+
                (players[player_index].getMerit())+
                ((int)(player_index==0)*first_bonus)
            );
            std::cout << "Total: " << total_merit_p1 << "\n";

            std::cin.clear();
            std::cin.ignore(1000,'\n');
            waitForEnter();
            clearScreen();

            //Player 2
            std::cout << "Player " << 2 << ": " << players[1].getName() << "\n";
            std::cout << "\t Military Power: " << players[1].getMilitaryPower() << " | 4x\n";
            std::cout << "\t Rations: " << players[1].getRations() << " | 3x\n";
            std::cout << "\t Wisdom: " << players[1].getWisdom() << " | 2x\n";
            std::cout << "\t Base Merit: " << players[1].getMerit()  << " | x\n";
            if (player_index == 0){
                std::cout << "\t First Bonus: " << first_bonus << "\n";
            }

            std::cin.clear();
            std::cin.ignore(1000,'\n');
            waitForEnter();

            std::cout << "Player " << 2 << ": " << players[1].getName() << "\n";
            std::cout << "\t __CONVERTED__: " << players[1].getMilitaryPower() * 4 << "\n";
            std::cout << "\t __CONVERTED__: " << players[1].getRations() * 3 << "\n";
            std::cout << "\t __CONVERTED__: " << players[1].getWisdom() * 2 << "\n";
            std::cout << "\t Base Merit: " << players[1].getMerit() << "\n";
            std::cout << "___________________________________________________________\n";

            total_merit_p2 = (
                (players[1].getMilitaryPower() * 4)+
                (players[1].getRations() * 3)+
                (players[1].getWisdom() * 2)+
                (players[1].getMerit())+
                ((int)(player_index==1)*first_bonus)
            );
            std::cout << "Total: " << total_merit_p2 << "\n";

            std::cin.clear();
            std::cin.ignore(1000,'\n');
            waitForEnter();
            clearScreen();

            std::cout << " P1    |    P2" << "\n";
            std::cout << total_merit_p1 << " | " << total_merit_p2 << "\n";

            if (total_merit_p1 > total_merit_p2){
                std::cout << "PLAYER 1 WINS!!!" << "\n"; 
            }
            else if (total_merit_p2 > total_merit_p1){
                std::cout << "PLAYER 2 WINS!!!" << "\n";
            }
            else{
                std::cout << "A DRAW?????" << "\n";
            }
            std::cout << "Enter Name for leaderboard!\n";
            std::string input;
            std::cin >> input;

            int score = (total_merit_p1 > total_merit_p1) ? total_merit_p1 : total_merit_p2;
            addtoLeaderboard(input, score);

            std::cin.clear();
            std::cin.ignore(1000,'\n');
            clearScreen();
            
            std::cout << "--{ LEADERBOARD }--\n";
            showLeaderboardSorted();
            waitForEnter();
            exit(0);
        }
        break;
        case GS_BOARD_MOVE:{
            int amt_forward;
            
            std::cout << "\n";
            amt_forward = board.spinWheel(player_index);
            std::cout << "\n";
            
            board.displayBoard();
            std::cout << "\n";
            doTileEffects(player_index, amt_forward);

            std::cin.clear();
            std::cin.ignore(1000,'\n');
            waitForEnter();
            if (board.getPlayerPosition(player_index) < 52){
                gameLoop(GS_MENU_MAIN, (int)(!player_index));
            }
            else{
                gameLoop(GS_TALLY_POINTS, player_index);
            }
        }
        break;
        case GS_MENU_MAIN:{
            int menu_input;

            std::cout << "--{ " << players[player_index].getName() << " }--\n";
            std::cout << "1. View Character\n";
            std::cout << "2. View Advisors\n";
            std::cout << "3. Check Position\n";
            std::cout << "4. Move Forward\n";
            std::cout << "5. View Units\n";

            while (!(std::cin >> menu_input) || menu_input < 1 || menu_input > 5){
                std::cin.clear();
                std::cin.ignore(1000,'\n');
                std::cout << "[Invalid Input]: Input one of the options above.\n";
            }

            switch(menu_input){
                case 1:
                    clearScreen();
                    players[player_index].printStats();

                    std::cin.clear();
                    std::cin.ignore(1000,'\n');
                    waitForEnter();

                    clearScreen();
                    gameLoop(GS_MENU_MAIN, player_index);
                break;
                case 2:
                    clearScreen();
                    players[player_index].printAdvisors();
                    
                    std::cin.clear();
                    std::cin.ignore(1000,'\n');
                    waitForEnter();

                    clearScreen();
                    gameLoop(GS_MENU_MAIN, player_index);
                break;
                case 3:
                    gameLoop(GS_BOARD, player_index);
                case 4:
                    gameLoop(GS_BOARD_MOVE, player_index);
                break;
                case 5:
                    clearScreen();
                    printUnits(player_index);

                    std::cin.clear();
                    std::cin.ignore(1000,'\n');
                    waitForEnter();

                    clearScreen();
                    gameLoop(GS_MENU_MAIN,player_index);
                break;
            }
        }
    }
}

/////////////////////////
/////     GAME      /////
/////////////////////////

    int main(){
        Game game;
        game.init();
        game.clearScreen();

        std::cout << game.titleCard << "\n";
        game.waitForEnter();

        game.gameLoop(GS_CHARACTER_SELECTION);
    }
#endif