
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
#include <string>

class Player{
    private:
        std::string name;
        int age;
        int militaryPower; // strength(reskinned)
        int rations; // stamina(reskinned)
        int wisdom;
        int simbaPoints;// pridePoints(reskinned)

        void getCharacterFromFile(std::fstream _file, int _line);
        /*SUDO CODE:
            loop through file till line(excluding the first line that tells what variables they are)
            (have a token that means ignore the line and add one to the line to avoid duplicates)
            get line
            split by |
            assign to necessary variables.
            (add exit token to the character sheet)

            ++ THE EXIT TOKEN IS SO WE CAN'T CHOOSE DUPLICATES ++
        */
    
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

#endif