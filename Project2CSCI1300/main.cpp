
//HARLEY RICHARDSON, ALEXANDER SCHLUNT

//////////////////////////////////
//                              //
//          HEADER FILE         //
//                              //
//////////////////////////////////

#include <string>
#include <iostream>

class Player{
    private:
        std::string name;
        int age;
        int militaryPower;
        int rations;
        int wisdom;
        int simbaPoints;
    
    public:
        //getters
        std::string getName();
        int getAge();
        int getMilitaryPower();
        int getRations();
        int getWisdom();
        int getSimbaPoints();

        //setters
        void setName(std::string _name);
        void setAge(int _age);
        void setMilitaryPower(int _militaryPower);
        void setRations(int _rations);
        void setWisdom(int _wisdom);
        void setSimbaPoints(int _simbaPoints);

        //other functions
        void addAge(int _age);
        void addMilitaryPower(int _militaryPower);
        void addRations(int _rations);
        void addWisdom(int _wisdom);
        void addSimbaPoints(int _simbaPoints);
};

///////////////////////////////////

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

int main(){
    std::string title = "///////////////////////////////////////////////////////////////////////////////////////////////////////////\n"
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

    std::cout << title;
    return 0;
}