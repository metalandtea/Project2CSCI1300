
//HARLEY RICHARDSON, ALEXANDER SCHLUNT

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifndef ADVISOR_H
#define ADVISOR_H

class Advisor{
    private:
        int id;
        std::string name;
        std::string description;
    public:
        //Constructors
        Advisor(); //Set empty advisor
        Advisor(std::string _filename, int _id); //Get advisor by advisor id

        //getters
        int getId();
        std::string getName();
        std::string getDescription();

        //Other
        void printStats();
};

#endif

#ifndef PLAYER_H
#define PLAYER_H

class Player{
    private:
        const int MAX_ADVISORS = 2;

        std::string name;
        int age;
        int militaryPower; // strength(reskinned)
        int rations; // stamina(reskinned)
        int wisdom;
        int merit;// pridePoints(reskinned)
    
    public:
        std::vector<Advisor> advisors;

        //getters
        std::string getName();
        int getAge();
        int getMilitaryPower();
        int getRations();
        int getWisdom();
        int getMerit();

        //setters
        void setName(std::string _name);
        void setAge(int _age);
        void setMilitaryPower(int _militaryPower);
        void setRations(int _rations);
        void setWisdom(int _wisdom);
        void setMerit(int _merit);

        //Advisors 
        void addAdvisor(std::string _advisors_filename, int _id);
        void removeAdvisor(int _id);
        void printAdvisors(bool _brief=false);

        //other functions
        void addAge(int _age);
        void addMilitaryPower(int _militaryPower);
        void addRations(int _rations);
        void addWisdom(int _wisdom);
        void addMerit(int _merit);

        void printStats();
        void getCharacterFromFile(std::string _filename, int _line);
};

#endif