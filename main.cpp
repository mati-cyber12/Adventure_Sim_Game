#include <iostream>
#include <random>
#include <array>
#include <thread>
#include <chrono>

enum Room_type{
    enemy,
    loot,
};

inline int get_random_room(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>distr(1,2);

    return distr(gen);
}

inline double get_random_event(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double>distr(0.0, 1.0);

    return distr(gen);
}

Room_type get_room_type(int random_num);

void handle_room_type(Room_type room, double& player_health, double& player_damage);

void handle_loot_room(double random,double& player_health, double& player_damage);

int main(){

    
    
    bool play_game {true};

    while(play_game){
        double player_health{10.0}; // CHANGE LATER
        double player_damage{10.0}; //change later

        while(player_health > 0){
            Room_type room_player_encounters{get_room_type(get_random_room())};
            handle_room_type(room_player_encounters, player_health, player_damage);
            




            player_health -= 2;


            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << "Play again y/n:";
        char play_again_user_choice {};
        std::cin >> play_again_user_choice; 

        if(play_again_user_choice == 'y'){
            play_game = true;
        } else {
            play_game = false;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));


    }



    return 0;
}

Room_type get_room_type(int random_num){
    switch (random_num){
        case 1:
            return enemy;
        case 2:
            return loot;
    }
}

void handle_room_type(Room_type room , double& player_health, double& player_damage){
    switch (room){
        case loot:{
            std::cout << "you have found loot \n";
            handle_loot_room(get_random_event(), player_health, player_damage);
        }
        case enemy:{
            std::cout << "you have encountered an enemy stand and fight \n";
        }
    }
}

void handle_loot_room(double random, double& player_health, double& player_damage){
    if (random > 0.5){
        std::cout << "\n";
        std::cout << "You have found a health kit \n";
        player_health += 2;
        std::cout << "Your health is now " << player_health << "\n";
        std::cout << "\n";
    } else{
        std::cout << "\n";
        std::cout << "You have found a damage upgrade \n";
        player_damage += 2;
        std::cout << "Damaged increases to " << player_damage << "\n";
        std::cout << "\n";
    }
}
