/*
    Doodle Jump by Ali Ranjbari
    may 16, 2021

*/

#include "class.hpp"
#include <fstream>
using namespace std;

const string FILE_NAME = "map.txt";

struct Elements{
    vector<Platform*> platforms;
    vector<Enemy*> enemies;
    vector<Spring*> springs;
};

Platform* add_nplatform(Position position){
    return new Nplatform({position.x-60 , 1024-(position.y+36)});
}
Platform* add_mplatform(Position position){
    return new Mplatform({position.x-60 , 1024-(position.y+36)});
}
Platform* add_bplatform(Position position){
    return new Bplatform({position.x-60 , 1024-(position.y+36)});
}
Enemy* add_enemy(Position position){
    return new Enemy({position.x-68 , 1024-(position.y+184)});
}
Spring* add_spring(Position position){
    return new Spring({position.x-56 , 1024-(position.y+46)});
}

void add_element(Elements& elements, Position position, string type){
    if(type == "platform")
        elements.platforms.push_back(add_nplatform(position));
    else if(type ==  "mplatform")
        elements.platforms.push_back(add_mplatform(position));
    else if(type ==  "bplatform")
        elements.platforms.push_back(add_bplatform(position));
    else if(type ==  "enemy")
        elements.enemies.push_back(add_enemy(position));
    else if(type ==  "spring")
        elements.springs.push_back(add_spring(position));
}

Map* creat_map(){
    Elements elements;
    ifstream map_file(FILE_NAME);
    int number_of_element;
    map_file >> number_of_element;
    string type;
    Position position;
    for(int i = 0; i<number_of_element; i++){
        map_file >> position.x >> position.y >> type;
        add_element(elements, position , type);
    }
    return new Map(elements.enemies,elements.platforms,elements.springs);
} 


int main(){
   
    Doodlejump doodle(creat_map());
    doodle.start_game();

    return 0;
}
