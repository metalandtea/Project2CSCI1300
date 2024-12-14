//HARLEY RICHARDSON, ALEXANDER SCHLUNT

#include <string>

#ifndef TILE_H
#define TILE_H

struct Tile{
        std::string description;
        char color;
        int wisdom_amt;
        int rations_amt;
        int military_power_amt;
        int spaces_amt;
        int advisor_id;
        bool select_advisor;
};
#endif
