#include <iostream>
#include <random>
#include <array>
#include <thread>
#include <chrono>
#include <string>
#include <string_view>

inline double get_random(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double>distr(0.0, 1.0);

    return distr(gen);
}

inline double get_random_damage_multi(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double>distr(1.0, 2.0);

    return distr(gen);
}

class Player {
    private:
        std::string name{"player"};
        double health {100.0};
        double damage {10.0};
        int stamina {50};
    public:
        explicit Player(std::string name)
            :name(std::move (name))
            {
                std::cout << "Welcome player\n";
            }
        std::string_view get_name() const {return name;}
        double get_health() const{return health;}
        double get_damage() const{return damage;}
        int get_stamina() const{return stamina;}

        void display_stats() const{
            std::cout << "\n";
            std::cout << "Health: " << get_health() << "\n";
            std::cout << "Damage: " << get_damage() << "\n";
            std::cout << "Stamina: " << get_stamina() << "\n";
        }

        void set_health(double health_set){
            this -> health = health_set;
            std::cout << "player health is now: " << health << "\n";
        }
        
        void set_name(std::string_view name_set){
            this -> name = name_set;
            std::cout << "player name is now: " << name << "\n";
        }

        void set_stamina(){
            stamina = 50;
        }

        void take_damage(double damage_points){
        std::cout << name << " takes: " << damage_points << " damage \n";
        health -= damage_points;
    }
    void deplete_stamina(){
        stamina -= 5;
        std::cout << "Player stamina is: " << stamina << "\n";
    }
        
};

class Monster{
    private:
        std::string name;
        double health;
        double damage;
        int stamina;
    public: 
        enum MonsterType {
        orc,
        goblin,
        bandit,
    };
        explicit Monster(MonsterType type){
            switch (type){
                case orc: {
                    name = "ORC";
                    health = 250.0;
                    damage = 20.0;
                    stamina = 50;
                    type = orc;
                    break;
                }
                case goblin: {
                    name = "Goblin";
                    health = 50.0;
                    damage = 10.0;
                    stamina = 70;
                    type = goblin;
                    break;
                }
                case bandit: {
                    name = "Bandit";
                    health = 100.0;
                    damage = 15.0;
                    stamina = 60;
                    type = bandit;
                    break;  
                }
            }   
        }
    private :
        MonsterType type;
    public :
        std::string_view get_name(){return name;}
        double get_health() const {return health;}
        double get_damage() const {return damage;}
        double get_stamina() const {return stamina;}
        void display_stats() const{
                std::cout << "\n";
                std::cout << name << "\n";
                std::cout << "Health: " << get_health() << "\n";
                std::cout << "Damage: " << get_damage() << "\n";
                std::cout << "Stamina: " << get_stamina() << "\n";
            }
        void set_stamina(){
            switch(type){
                case orc:{
                    stamina = 50;
                    break;
                }
                case goblin:{
                    stamina = 70;
                    break;
                }
                case bandit: {
                    stamina = 60;
                    break;
                }
            }
        }
        void take_damage(double damage_points){
            std::cout << name << " takes: " << damage_points << " damage \n";
            health -= damage_points;
            
            }
        void deplete_stamina(){
            stamina -= 5;
            std::cout << "Monster stamina is: " << stamina << " \n";
        }
};

int handle_room_type(double random_num);
Monster generate_monster(double random_num);

template <typename T>
double handle_damage_amount(T object, double random_num){
    double damage {object.get_damage()};
    return (damage * random_num);
    
}

int main(){
    bool playing {true};

    std::cout << "enter your name here: ";
    std::string name{};
    std::cin >> name;

    while (playing){
        Player player{name};
        int player_stamina_tracker{player.get_stamina()};
        while(player.get_health() > 0){
            int room_type {handle_room_type(get_random())};
            switch (room_type){
                case 1:{
                    std::cout << "you proceed forward \n";
                    break;
                }
                case 2:{
                    std::cout << "The treasure is: \n";
                    break;
                }
                case 3:{
                    Monster monster{generate_monster(get_random())};
                    std::cout << "a "  << monster.get_name() << " is here prepare yourself \n";
                    std::cout << "\n";
                    while((player.get_health() > 0) && (monster.get_health()>0)){
                        if (player.get_stamina() <= 0){
                            std::cout << "player stamina depleted \n";
                            player.set_stamina();
                            continue;
                        }else{
                            monster.take_damage(handle_damage_amount(player, get_random_damage_multi()));
                            std::cout << "Monster health: " << monster.get_health() << "\n";
                            std::cout << "\n";
                            player.deplete_stamina();
                        }

                        if (monster.get_stamina() <= 0){
                            std::cout << "Monster stamina depleted \n";
                            monster.set_stamina();
                            continue;
                        }else{
                            player.take_damage(handle_damage_amount(monster, get_random_damage_multi()));
                            std::cout << "Player health: " << player.get_health() << "\n";
                            std::cout << "\n";
                            monster.deplete_stamina();
                        }
                    }
                    
                    break;
                }
            }
            
            
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << "Play game again?: y/n";
        char player_choice{};
        std::cin >> player_choice;
        if (player_choice == 'y'){
            playing = true;
        } else{ 
            playing = false;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    



return 0;
}

int handle_room_type(double random_num){
    int room_type{};
    if (random_num < 0.33){
        std::cout << "You have stumbled into an empty room\n";
        room_type = 1;
        return room_type;
    }else if((random_num>= 0.33) &&(random_num < 0.66)){
        std::cout << "You have found treasure \n";
        room_type = 2;
        return room_type;
    }else{
        std::cout << "A foe approaches\n";
        room_type = 3;
        return room_type;
    }
}

Monster generate_monster(double random_num){

    if (random_num < 0.4){
        Monster monster_id{Monster::bandit};
        return monster_id;
    }else if ((random_num>= 0.4) &&(random_num < 0.8)){
        Monster monster_id{Monster::goblin};
        return monster_id;
    }else{
        Monster monster_id{Monster::orc};
        return monster_id;
    }
}

