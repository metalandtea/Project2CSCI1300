
//HARLEY RICHARDSON, ALEXANDER SCHLUNT

#include <iostream>
#include <string>
#include <fstream>

#include "battles.h"

//LMAO THIS IS A "CLEAR SCREEN" ALRIGHT
void clear_screen() {
    int i = 0;

    while (i < 200){ //OOOOO MAGIC NUMBER
        std::cout << std::endl;
        i++;
    }
}

SpecialUnit::SpecialUnit(){
    name = "";
    type = -1;
    health = -1;
    baseDamage = -1;
    image = "";
}

SpecialUnit::SpecialUnit(int _unit){

    //NOTE: YES, I KNOW IT'S BETTER TO PUT THESE IMAGES IN FILES INSTEAD.
    //THIS IS JUST A PROOF OF CONCEPT.
    switch (_unit){
        case UT_TANK:
            name = "Tank";
            type = UT_TANK;
            health = 10;
            baseDamage = 2;
            image = "                \n"
                    "                \n"
                    "    ____        \n"
                    "  _/    }====== \n"
                    " |        /     \n"
                    "  OOOOOOOO      \n";
        break;
        case UT_PLANE:
            name = "Plane";
            type = UT_PLANE;
            health = 5;
            baseDamage = 3;
            image = "   _____ ===    \n"
                    "   \\    \\_____  \n"
                    "    | O O O ___\\  \n"
                    "   /_____/===    \n"
                    "                \n"
                    "                \n";

        break;
        case UT_ANTIAIR:
            name = "Anti-Aircraft";
            type = UT_ANTIAIR;
            health = 8;
            baseDamage = 4;
            image = "                \n"
                    "       _  _     \n"
                    "      // //     \n"
                    "    _//_//      \n"
                    "  /   |  |      \n"
                    " |    |  |      \n";
        break;
    }
}

int SpecialUnit::getType() {return type;}
int SpecialUnit::getbaseDamage() {return baseDamage;}
int SpecialUnit::getHealth() {return health;}
std::string SpecialUnit::getName() {return name;}
std::string SpecialUnit::getImage() {return image;}

void SpecialUnit::printStats(){
    std::cout << "\n";
    std::cout << "///---   " << name << "   ---///" << "\n";
    std::cout << "  -- Health: " << health << "\n";
    std::cout << "  -- Damage: " << baseDamage << "\n";
    std::cout << "________________________________" << "\n";
    std::cout << image << "\n";
    std::cout << "________________________________" << "\n";
}

void SpecialUnit::setHealth(int _health){
    health = _health;
}

Battle::Battle(SpecialUnit _unit1, SpecialUnit _unit2){
    Battle::units[0] = _unit1;
    Battle::units[1] = _unit2;
    turn = 0;
}

void Battle::fight(){
    if (turn == 0){
        turn = 1;

        units[1].setHealth(units[1].getHealth()-units[0].getbaseDamage());
    }
    else if (turn == 1){
        turn = 0;

        units[0].setHealth(units[0].getHealth()-units[1].getbaseDamage());
    }
}

SpecialUnit Battle::getUnit(int _unit){
    return units[_unit];
}

void Battle::showUnits(){
    units[0].printStats();
    units[1].printStats();
}
#ifdef __MAIN__
int main(){
    std::string buffer_button;
    SpecialUnit tank(0);
    SpecialUnit plane(1);
    Battle battle(tank, plane);
    battle.showUnits();
    std::cin >> buffer_button;
    clear_screen();
    battle.fight();
    battle.showUnits();

    return 0;
}
#endif