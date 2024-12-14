//HARLEY RICHARDSON, ALEXANDER SCHLUNT

enum unitTyoes{
            UT_TANK,
            UT_PLANE,
            UT_ANTIAIR,
};

class SpecialUnit{
    private:
        int health;
        int baseDamage;
        int type;
        std::string name;
        std::string image;
        
    public:
        SpecialUnit(int _unit);
        SpecialUnit();

        //Getters
        int getType();
        int getbaseDamage();
        int getHealth();
        std::string getName();
        std::string getImage();

        //Setters
        void setHealth(int _health);

        //Stats
        void printStats();
};

class Battle{
    private:
        int turn;
        SpecialUnit units[2];
    public:
        Battle(SpecialUnit _unit1, SpecialUnit _unit2);
        void showUnits();
        void fight();
        SpecialUnit getUnit(int _index);
};
