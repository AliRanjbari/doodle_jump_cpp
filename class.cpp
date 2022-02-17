/*
    classes of doodle jump
    by ali ranjbari
*/

#include "class.hpp"


void Character::jump(){
    jumped = 15;
    total_speed.y = jump_speed.y;
    total_speed.x = jump_speed.x;
}

void Character::spring_jump(){
    jumped = 9;
    total_speed.y = spring_jm_speed.y;
    total_speed.x = spring_jm_speed.x;
}

void Character::falling(){
    previous_y_pos = position.y;
    position.y += total_speed.y;
    position.x += total_speed.x;
    total_speed.x += gravity_force.x;
    total_speed.y += gravity_force.y;
}

bool Character::is_within_screen(){
    int screen_margin = CHAR_SIZE.width/-2;
    if(position.x < screen_margin || position.x > (WINDOW_SIZE.width+screen_margin))
        return false;
    return true;
}

void Character::move_right(){
    position.x += move_speed.x;
    position.y += move_speed.y;
    if(!is_within_screen())
        position.x = CHAR_SIZE.width/-2;
    moving.still_moving = true;
    moving.direction = 'd';
}

void Character::move_left(){
    position.x -= move_speed.x;
    position.y += move_speed.y;
    if(!is_within_screen())
        position.x = WINDOW_SIZE.width+CHAR_SIZE.width/-2;
    moving.still_moving = true;
    moving.direction = 'a';
}

void Character::stop(){
    moving.still_moving = false;
}

void Character::continue_moving(){
    if(moving.direction == 'd')
        move_right();
    else if(moving.direction == 'a')
        move_left();
}

bool Character::is_moving(){
    return moving.still_moving;
}

void Character::draw(Window* window){
    if(jumped == 0){
        if(moving.direction == 'a')
            window->draw_img(PIC_DOODLE_LEFT, Rectangle(position.x, position.y, size.width, size.height));
        else if(moving.direction == 'd')
            window->draw_img(PIC_DOODLE_RIGHT, Rectangle(position.x, position.y, size.width, size.height));
    }
    else{
         if(moving.direction == 'a')
            window->draw_img(PIC_DOODLE_LEFT_J, Rectangle(position.x, position.y, size.width, size.height-8));
        else if(moving.direction == 'd')
            window->draw_img(PIC_DOODLE_RIGHT_J, Rectangle(position.x, position.y, size.width, size.height-8));
        jumped--;
    }
}

Position Character::get_position(){
    return position;
}

bool Character::is_falling(){
    return total_speed.y > 0 ? true : false;
}

bool Character::has_reach_bottom(){
    if(position.y > WINDOW_SIZE.height)
        return true;
    return false;
}


void Character::lost_fall(){
    gravity_force.y = 0;
    total_speed.y = 0;
    total_speed.x = 0;
}

Enemy::Enemy(Position _position){
    position = _position;
}

void Enemy::draw(Window* window){
    window->draw_img(PIC_ENEMY, Rectangle(position.x, position.y, ENEMY_SIZE.width, ENEMY_SIZE.height));
}

bool Enemy::has_collided(Position char_pos){
    if(char_pos.x < position.x+ENEMY_SIZE.width-7 && char_pos.x > position.x-CHAR_SIZE.width+7)
        if(char_pos.y < position.y+ENEMY_SIZE.height && char_pos.y > position.y-CHAR_SIZE.height)
            return true;
    return false;
}

Platform::Platform(Position _position){
    position = _position;
}

bool Platform::has_collided(Position char_pos, int previous_y_pos){
    if(char_pos.x < position.x+PLAT_SIZE.width-7 && char_pos.x > position.x-CHAR_SIZE.width+7)
        if(previous_y_pos+CHAR_SIZE.height <= position.y && char_pos.y+CHAR_SIZE.height >= position.y )
            return true;
    return false;
}


void Nplatform::draw(Window* window){
    window->draw_img(PIC_NPLATFORM,Rectangle(position.x,position.y,PLAT_SIZE.width,PLAT_SIZE.height));
}

void Bplatform::draw_breaked_pl(Window* window){
    if(break_level >= 0 && break_level < delay_time){
        window->draw_img(PIC_BPLATFORM2, Rectangle(position.x, position.y, PLAT_SIZE.width, PLAT_SIZE.height));
        break_level++; 
    }
    else if(break_level >= delay_time && break_level < delay_time*2){
        window->draw_img(PIC_BPLATFORM3, Rectangle(position.x, position.y, PLAT_SIZE.width, PLAT_SIZE.height));
        break_level++; 
    }
    else if(break_level >= 2*delay_time && break_level < 3*delay_time*2){
        window->draw_img(PIC_BPLATFORM4, Rectangle(position.x, position.y, PLAT_SIZE.width, PLAT_SIZE.height));
        break_level++; 
    }
}

void Bplatform::draw(Window* window){
    if(is_breaked == false){
        window->draw_img(PIC_BPLATFORM1, Rectangle(position.x, position.y, PLAT_SIZE.width, PLAT_SIZE.height));
    }
    else{
      draw_breaked_pl(window);
    }
}

bool Bplatform::has_collided(Position char_pos, int previous_y_pos){
    if(char_pos.x < position.x+PLAT_SIZE.width-7 && char_pos.x > position.x-CHAR_SIZE.width+7)
        if(previous_y_pos+CHAR_SIZE.height <= position.y && char_pos.y+CHAR_SIZE.height >= position.y )
            is_breaked = true;
    return false;
}

void Mplatform::touch_the_sides(){
    if(position.x <= 0 || position.x >= WINDOW_SIZE.width-PLAT_SIZE.width)
        move_direction = move_direction == 'd' ? 'r' : 'd';
}

void Mplatform::move(){
    if(move_direction == 'd')
        position.x += PLAT_SP.x;
    else
        position.x -= PLAT_SP.x;
    touch_the_sides();
}

void Mplatform::draw(Window* window){
    window->draw_img(PIC_MPLATFORM, Rectangle(position.x, position.y,PLAT_SIZE.width,PLAT_SIZE.height));
}

void Spring::draw(Window* window){
    if(opened == false)
        window->draw_img(PIC_SPRING, Rectangle(position.x, position.y,SPRING_SIZE.width,SPRING_SIZE.height));
    else
        window->draw_img(PIC_SPRING2, Rectangle(position.x, position.y-10,SPRING_SIZE.width,55));
}

bool Spring::has_collided(Position char_pos, int previous_y_pos){
    if(char_pos.x < position.x+SPRING_SIZE.width-7 && char_pos.x > position.x-CHAR_SIZE.width+7)
        if(previous_y_pos+CHAR_SIZE.height <= position.y && char_pos.y+CHAR_SIZE.height >= position.y ){
            opened = true;
            return true;
        }
    return false;

}

void Spring::move_down(int y){
    position.y += y;
}

Map::Map(vector<Enemy*> _enemies, vector<Platform*> _platforms, vector<Spring*> _springs){
   enemies = _enemies;
   platforms = _platforms;
   springs = _springs;
}


int Map::should_char_jump(Position char_pos, int previous_y_pos){
    for(auto pl : platforms)
        if(pl->has_collided(char_pos, previous_y_pos))
            return 1;
    for(auto sp: springs)
        if(sp->has_collided(char_pos, previous_y_pos))
            return 2;
    return 0;
}

void Map::update(bool &lost,Position char_pos){
    for(auto& pl: platforms){
        pl->move();
    }
    for(auto& en: enemies)
        if(en->has_collided(char_pos))
            lost = true;
    
}

void Map::draw(Window* window){
    for(auto pl: platforms)
        pl->draw(window);
    for(auto en: enemies)
        en->draw(window);
    for(auto sp: springs)
        sp->draw(window);
}

void Map::move_camera(int y){
    for(auto& pl: platforms)
        pl->move_down(y);
    for(auto& en: enemies)
        en->move_down(y);
    for(auto& sp: springs)
        sp->move_down(y);
}

void Score::add_score(Position char_pos){
    if(!camera_moved)
        if(current_score < WINDOW_SIZE.height-char_pos.y)
            current_score = WINDOW_SIZE.height-char_pos.y;
}

void Score::show_score(Window* window){
    window->show_text(to_string(current_score), Point(10,10), RED, "pics/FreeSansBold-Rdmo.otf", 40);

}

Doodlejump::Doodlejump(Map* _map){
    map = _map;
}

void Doodlejump::draw_background(){
    window->draw_img(PIC_BACKGROUND);
}

void Doodlejump::move_character(char pressed_key){
    if(!lost){
        if(pressed_key == 'a'){
            character->move_left();
        }
        else if(pressed_key == 'd'){
            character->move_right();
        }
    }
    if(pressed_key == 'q')
        exit(0);
}

void Doodlejump::press_anykey_quit(){
    if(window->has_pending_event()){
        Event event = window->poll_for_event();
        if(event.get_type() == Event::Event::KEY_PRESS)
            exit(0);
    }
}

void Doodlejump::get_input(){
    if(lost)
        press_anykey_quit();
    if(window->has_pending_event()){
        Event event = window->poll_for_event();
        switch(event.get_type()){
        case Event::Event::QUIT:
            exit(0);
            break;
        case Event::Event::KEY_PRESS:
            move_character(event.get_pressed_key());
            break;
        case Event::Event::KEY_RELEASE:
            character->stop();
            break;
        }
    }
    if(!lost)
        if(character->is_moving())
            character->continue_moving();
}

void Doodlejump::move_camera(int y){
    map->move_camera(y);
    if(y > 0)
        character->stay_in_middle();
}


void Doodlejump::update(){
    score->add_score(character->get_position());
    map->update(lost, character->get_position());
    int jump_level = map->should_char_jump(character->get_position(), character->get_previous_y_pos());
    if(!lost && jump_level){
        if(jump_level == 1)
            character->jump();
        else
            character->spring_jump();
    }
    if(character->get_position().y < WINDOW_SIZE.height/2){
        score->add_score(WINDOW_SIZE.height/2-character->get_position().y);
        move_camera(WINDOW_SIZE.height/2-character->get_position().y);
    }
    if(character->has_reach_bottom())
        lost = true;
    if(lost){
        character->lost_fall();
        move_camera(-LOST_SPEED);
    }
    character->falling();
}

void Doodlejump::lost_message(){
    window->show_text("You Lost!", Point(150,40), RED, "pics/FreeSansBold-Rdmo.otf", 80);
    window->show_text("score", Point(20,400), BLACK, "pics/FreeSansBold-Rdmo.otf", 40);
    window->show_text(to_string(score->get_score()), Point(100,400),BLACK,"pics/FreeSansBold-Rdmo.otf", 200);
    window->show_text("press any key to QUIT", Point(150,950),BLUE,"pics/FreeSansBold-Rdmo.otf", 40);
}

void Doodlejump::one_frame(){
    window->clear();
    draw_background();
    get_input();
    update();
    map->draw(window);
    character->draw(window);
    if(lost)
        lost_message();
    else
        score->show_score(window);
    window->update_screen();
}

void Doodlejump::game_loop(int delay_time){
    character->jump();
    while(true){
        one_frame();
        delay(delay_time);
    }
}

void Doodlejump::start_game(){
    window = new Window(WINDOW_SIZE.width,WINDOW_SIZE.height,"DOODLEJUMP");
    game_loop(15);
}

