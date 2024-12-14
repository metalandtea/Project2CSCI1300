
//HARLEY RICHARDSON, ALEXANDER SCHLUNT

#include "player.h"
#include <iostream>
#include <fstream>
#include <vector>

//////////////////////
//      ADVISOR     //
//////////////////////

//Contstructors
Advisor::Advisor(){
    id = -1; //-1 IS NOT AN ADVISOR
    name = "";
    description = "";
}

Advisor::Advisor(std::string _filename, int _id){
    id = _id;
    std::ifstream advisors(_filename);
    std::string line;
    bool found_line = false;
    int i = -1;

    while (std::getline(advisors, line)){
        i++;
        if (i > 0 && _id == std::stoi(line.substr(0,line.find('|')))){
            break;
        }
    }


    line = line.substr(line.find('|')+1, line.length());
    name = line.substr(0,line.find('|'));

    line = line.substr(line.find('|')+1, line.length());
    description = line.substr(0,line.length());
}

//getters
std::string Advisor::getName()          {return name;}
std::string Advisor::getDescription()   {return description;}
int Advisor::getId()                    {return id;}

void Advisor::printStats(){
    std::cout << "Advisor: " << name << "\n";
    std::cout << "Id: " << id << "\n";
    std::cout << "Description: " << description << "\n";
}

//////////////////////
//      PLAYER      //
//////////////////////

//Get functions

std::string Player::getName()   {return name;}
int Player::getAge()            {return age;}
int Player::getMilitaryPower()  {return militaryPower;}
int Player::getRations()        {return rations;}
int Player::getWisdom()         {return wisdom;}
int Player::getMerit()    {return merit;}

//Set functions

void Player::setName(std::string _name)             {name = _name;}
void Player::setAge(int _age)                       {age = (_age >= 0) ? _age : 0;}
void Player::setMilitaryPower(int _militaryPower)   {militaryPower = (_militaryPower >= 100) ? _militaryPower : 100;}
void Player::setRations(int _rations)               {rations = (_rations >= 100) ? _rations : 100;}
void Player::setWisdom(int _wisdom)                 {wisdom = (_wisdom >= 100) ? _wisdom : 100;}
void Player::setMerit(int _merit)                   {merit = (_merit >= 100) ? _merit : 100;}

//Add functions

void Player::addAge(int _age)                       {setAge(age + _age);}
void Player::addMilitaryPower(int _militaryPower)   {setMilitaryPower(militaryPower + _militaryPower);}
void Player::addRations(int _rations)               {setRations(rations + _rations);}
void Player::addWisdom(int _wisdom)                 {setWisdom(wisdom + _wisdom);}
void Player::addMerit(int _merit)                   {setMerit(merit + _merit);}

//Player advisor functions

void Player::addAdvisor(std::string _advisors_filename, int _id){
    Advisor advisor(_advisors_filename, _id);
    if (advisors.size() < MAX_ADVISORS){
        advisors.push_back(advisor);
    }
}
void Player::removeAdvisor(int _id){
    for (int i = 0; i < advisors.size(); i++){
        if (advisors[i].getId() == _id){
            advisors.erase(advisors.begin()+i);
        }
    }
}

void Player::printAdvisors(bool _brief){
    std::cout << "-<{[  Advisors  ]}>-\n";
    if (_brief == true){
        for (int i = 0; i < advisors.size(); i++){
            std::cout << advisors[i].getName() << "\n";
        }
        return;
    }

    for (int i = 0; i < advisors.size(); i++){
        std::cout << "\t --" << advisors[i].getName() << "--\n";
        std::cout << "\t> Description: " << advisors[i].getDescription() << "\n";
        std::cout << "\t> Id: " << advisors[i].getId() << "\n";
    }
}


void Player::printStats(){
    std::cout << "-- " << name << "--" << "\n";
    std::cout << "Age: " << age << "\n";
    std::cout << "Military Power: " << militaryPower << "\n";
    std::cout << "Rations: " << rations << "\n";
    std::cout << "Wisdom: " << wisdom << "\n";
    std::cout << "Simba Points: " << merit << "\n";
}

void Player::getCharacterFromFile(std::string _filename, int _line){
    std::ifstream Characters(_filename);
    std::string character_stats;
    int i = -1;
    while (std::getline(Characters, character_stats)){
        i++;
        if (i == _line){
            break;
        }
    }

    //Set each value of the player.(Yes this isn't the best way to do it. Sorry.)
    name = character_stats.substr(0,character_stats.find('|'));
    character_stats = character_stats.substr(character_stats.find('|')+1, character_stats.length());

    age = std::stoi(character_stats.substr(0,character_stats.find('|')));
    character_stats = character_stats.substr(character_stats.find('|')+1, character_stats.length());

    militaryPower = std::stoi(character_stats.substr(0,character_stats.find('|')));
    character_stats = character_stats.substr(character_stats.find('|')+1, character_stats.length());

    rations = std::stoi(character_stats.substr(0,character_stats.find('|')));
    character_stats = character_stats.substr(character_stats.find('|')+1, character_stats.length());

    wisdom = std::stoi(character_stats.substr(0,character_stats.find('|')));
    character_stats = character_stats.substr(character_stats.find('|')+1, character_stats.length());

    merit = std::stoi(character_stats.substr(0,character_stats.find('|')));
    character_stats = character_stats.substr(0, character_stats.length());
}


#ifdef __MAIN__

int main(){
    std::string characters_filename = "characters.txt";
    std::string advisors_filename = "advisors.txt";

    Player player;
    player.getCharacterFromFile(characters_filename, 5);
    clear_screen();
    player.printStats();

    player.addAdvisor(advisors_filename, 1);

    player.printAdvisors(0);
}
#endif