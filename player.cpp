
#include "player.h"

//Get functions

std::string Player::getName()   {return name;}
int Player::getAge()            {return age;}
int Player::getMilitaryPower()  {return militaryPower;}
int Player::getRations()        {return rations;}
int Player::getWisdom()         {return wisdom;}
int Player::getSimbaPoints()    {return simbaPoints;}

//Set functions

void Player::setName(std::string _name)             {name = _name;}
void Player::setAge(int _age)                       {age = (_age >= 0) ? _age : 0;}
void Player::setMilitaryPower(int _militaryPower)   {militaryPower = (_militaryPower >= 100) ? _militaryPower : 100;}
void Player::setRations(int _rations)               {rations = (_rations >= 100) ? _rations : 100;}
void Player::setWisdom(int _wisdom)                 {wisdom = (_wisdom >= 100) ? _wisdom : 100;}
void Player::setSimbaPoints(int _simbaPoints)       {simbaPoints = (_simbaPoints >= 100) ? _simbaPoints : 100;}

//Add functions

void Player::addAge(int _age)                       {setAge(age + _age);}
void Player::addMilitaryPower(int _militaryPower)   {setMilitaryPower(militaryPower + _militaryPower);}
void Player::addRations(int _rations)               {setRations(rations + _rations);}
void Player::addWisdom(int _wisdom)                 {setWisdom(wisdom + _wisdom);}
void Player::addSimbaPoints(int _simbaPoints)       {setSimbaPoints(simbaPoints + _simbaPoints);}
