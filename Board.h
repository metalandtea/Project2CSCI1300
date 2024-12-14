//HARLEY RICHARDSON, ALEXANDER SCHLUNT

#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"

class Board
{
private:
    static const int _BOARD_SIZE = 52;
    Tile _tiles[2][_BOARD_SIZE];
    static const int _MAX_PLAYERS = 2;
    int _player_count;
    int _player_position[_MAX_PLAYERS];
    int _player_track[_MAX_PLAYERS];

    void displayTile(int track_ind, int pos);
    void initializeTiles(int track_ind);
    bool isPlayerOnTile(int track_ind, int pos, int player_index);

public:
    Board();
    Board(int player_count);
    void displayTrack(int player_index);
    void initializeBoard();
    void displayBoard();
    bool movePlayer(int player_index);
    int getPlayerPosition(int player_index);
    int getPlayerTrack(int player_index);
    void setPlayerTrack(int player_index, int track);
    int spinWheel(int player_index);
    void setPlayerPosition(int player_index, int pos);

    Tile getTile(int track, int _index);
};

#endif