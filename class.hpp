/*
    classes of doodle jump
    by ali ranjbari
*/
#ifndef _CLASS_HPP_
#define _CLASS_HPP_

#include <iostream>
#include <string>
#include "src/rsdl.hpp"
#include <vector>

using namespace std;

const string PIC_DOODLE_LEFT = "pics/left.png";
const string PIC_DOODLE_RIGHT = "pics/right.png";
const string PIC_DOODLE_LEFT_J = "pics/left_jumping.png";
const string PIC_DOODLE_RIGHT_J = "pics/right_jumping.png";
const string PIC_BACKGROUND = "pics/background.png";
const string PIC_NPLATFORM = "pics/Nplatform.png";
const string PIC_MPLATFORM = "pics/Mplatform.png";
const string PIC_BPLATFORM1 = "pics/Bplatform.png";
const string PIC_BPLATFORM2 = "pics/Bplatform2.png";
const string PIC_BPLATFORM3 = "pics/Bplatform3.png";
const string PIC_BPLATFORM4 = "pics/Bplatform4.png";
const string PIC_ENEMY = "pics/enemy.png";
const string PIC_SPRING = "pics/spring.png";
const string PIC_SPRING2 = "pics/spring2.png";


struct Speed{
    double x;
    double y;
};

struct Acceleration{
    double x;
    double y;
};
struct Position{
    int x;
    int y;
};
struct Size{
    int width;
    int height;
};

struct Moving{
    bool still_moving = false;
    char direction = 'd';
};

const Size WINDOW_SIZE = {650,1024};
const Size CHAR_SIZE = {92,90};
const Size PLAT_SIZE = {120,30};
const Size ENEMY_SIZE = {118,172};
const Size SPRING_SIZE = {35, 23};
const Position CHAR_INI_POS = {325,900};
const Acceleration GRAVITY_FORC = {0,0.25};
const Speed JUMP_SP = {0,-10};
const Speed SPR_JUM_SP = {0,-20};
const Speed MOVE_SP = {8,0};
const Speed PLAT_SP = {6,0};
const int LOST_SPEED = 10;


class Character{
private:
    Size size = CHAR_SIZE;
    Position position = CHAR_INI_POS;
    int  previous_y_pos = CHAR_INI_POS.y;
    Speed total_speed = {0,0};
    Speed jump_speed = JUMP_SP;
    Speed spring_jm_speed = SPR_JUM_SP;
    Acceleration gravity_force = GRAVITY_FORC;
    Speed move_speed = MOVE_SP;
    int jumped = false;
    Moving moving;
 

public:
    void jump();
    void spring_jump();
    void falling();
    bool is_within_screen();
    void move_right();
    void move_left();
    void stop();
    bool is_moving();
    void continue_moving();
    void draw(Window* window);
    Position get_position();
    int get_previous_y_pos(){return previous_y_pos;}
    bool is_falling();
    void lost_fall();
    void stay_in_middle(){position.y = WINDOW_SIZE.height/2;}
    bool has_reach_bottom();
};

class Enemy{
private:
    Position position;
public:
    Enemy(Position _position);
    void move_down(int y){position.y += y;}
    void draw(Window* window);
    bool has_collided(Position char_pos);
};

class Platform{
protected:
    Position position;
public:
    Platform(Position _position);
    void move_down(int y){position.y += y;}
    virtual bool has_collided(Position char_pos, int previous_y_pos);
    virtual void draw(Window* window) = 0;
    virtual void move() = 0;
};

class Nplatform : public Platform{
private:

public:
    Nplatform(Position _position):Platform(_position){};
    void draw(Window* window);
    void move(){};
};

class Bplatform : public Platform{
private:
    bool is_breaked = false;
    int break_level = 0;
    int delay_time = 2;
public:
    Bplatform(Position _position):Platform(_position){};
    void draw_breaked_pl(Window* window);
    void draw(Window* window);
    bool has_collided(Position char_pos, int previous_y_pos);
    void move(){};
};

class Mplatform : public Platform{
private:
    Speed speed = PLAT_SP;
    char move_direction = 'd';
public:
    Mplatform(Position _position):Platform(_position){};
    void touch_the_sides();
    void move();
    void draw(Window* window);
};

class Spring{
private:
    Position position;
    bool opened = false;
public:
    Spring(Position pos): position(pos){}
    void draw(Window* window);
    bool has_collided(Position char_pos, int previous_y_pos);
    void move_down(int y);
    
};

class Map{
private:
    vector<Enemy*> enemies;
    vector<Platform*> platforms;
    vector<Spring*> springs;
public:
    Map(vector<Enemy*> _enemies, vector<Platform*> _platforms, vector<Spring*> _springs);
    int should_char_jump(Position char_pos, int previous_y_pos);
    void update(bool &lost,Position char_pos);
    void draw(Window* window);
    void move_camera(int y);
};

class Score{
private:
    int current_score = 0;
    bool camera_moved = false;
public:
    int get_score(){return current_score;}
    void add_score(int y){current_score += y;camera_moved = true;}
    void add_score(Position char_pos);
    void show_score(Window* window);
};

class Doodlejump{
private:
    Window* window;
    Map* map;
    Character* character = new Character();
    bool lost = false;
    Score* score = new Score();
public:
    Doodlejump(Map* _map);
    void draw_background();
    void move_character(char pressed_key);
    void press_anykey_quit();
    void get_input();
    void move_camera(int y);
    void update();
    void lost_message();
    void one_frame();
    void game_loop(int delay_time);
    void start_game();
    
};


#endif
