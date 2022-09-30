#include "model.hxx"
//#include "view.hxx"


Model::Model(Game_config const& config)
        : config(config),
          pacman(config),
          ghost1(config, ghost1_start_pos, ghost1_vel),
          ghost2(config, ghost2_start_pos, ghost2_vel),
          ghost3(config, ghost3_start_pos, ghost3_vel),
          ghost4(config, ghost4_start_pos, ghost4_vel)
{


    for (int i =0; i < 32; i++) {
        if (i < 2) {
            walls.push_back({8 + i, 12, 1, 1});
            walls.push_back({8 + i, 15, 1, 1});
            walls.push_back({24 + i, 21, 1, 1});
            walls.push_back({28 + i, 21, 1, 1});
            walls.push_back({4, 19 + i, 1, 1});
            walls.push_back({7, 5 + i, 1, 1});
            walls.push_back({10, 7 + i, 1, 1});
            walls.push_back({13, 5 + i, 1, 1});
            walls.push_back({17, 21 + i, 1, 1});
            walls.push_back({20, 5 + i, 1, 1});
        }
        if (i < 3) {
            //walls.push_back({20, 4 + i, 1, 1});
            walls.push_back({13, 14 + i, 1, 1,});
            walls.push_back({19 + i, 13, 1, 1});
            walls.push_back({21, 14 + i, 1, 1});
            walls.push_back({24 + i, 15, 1, 1});
            walls.push_back({27 + i, 18, 1, 1});
            walls.push_back({26 + i, 4, 1, 1});
            walls.push_back({26 + i, 7, 1, 1});
            walls.push_back({26, 10 + i, 1, 1});

        }
        if (i < 4) {
            walls.push_back({13 + i, 13, 1, 1});
            walls.push_back({29 + i, 12, 1, 1}); //tunnel
            walls.push_back({29 + i, 15, 1, 1}); //tunnel
            walls.push_back({1 + i, 12, 1, 1});  //tunnel
            walls.push_back({1 + i, 15, 1, 1});  //tunnel
        }
        if (i < 5) {
            walls.push_back({4 + i, 4, 1, 1});
            walls.push_back({4, 5 + i, 1, 1});
            walls.push_back({24, 16 + i, 1, 1});
        }
        if (i < 6) {
            walls.push_back({5 + i, 9, 1, 1});
            walls.push_back({12 + i, 4, 1, 1});
            walls.push_back({10, 12 + i, 1, 1});
            walls.push_back({29, 4 + i, 1, 1});
        }
        if (i < 7) {
            walls.push_back({4 + i, 18, 1, 1});
            walls.push_back({4 + i, 21, 1, 1});
            walls.push_back({13 + i, 10, 1, 1});
        }
        if (i < 8) {
            walls.push_back({13 + i, 7, 1, 1});
            //walls.push_back({13 + i, 10, 1, 1});
            walls.push_back({1, 16 + i, 1, 1}); //v wall
            walls.push_back({32, 16 + i, 1, 1}); //v wall
        }
        if (i < 9) {
            walls.push_back({13 + i, 17, 1, 1});
            walls.push_back({13 + i, 20, 1, 1});
            walls.push_back({13 + i, 23, 1, 1});
            walls.push_back({23, 4 + i, 1, 1});
        }
        if (i < 10) {
            walls.push_back({1, 2 + i, 1, 1}); //v wall
            walls.push_back({32, 2 + i, 1, 1}); //v wall
        }
        if (i < 32) {
            walls.push_back({1 + i, 1, 1, 1}); //h wall
            walls.push_back({1 + i, 24, 1, 1}); //h wall
        }
    }

    //taken_positions vector
    for (Block wall : walls){
        taken_positions.push_back(wall);
    }

    //pacman initial posn
    //ge211::Posn<int> initial_posn = config.pacman_start_pos;
    //taken_positions.push_back({initial_posn.x, initial_posn.y, 1, 1,});

    //ghost box
    taken_positions.push_back({18, 14,1,1});
    taken_positions.push_back({18, 13,1,1});
    for (int r = 15; r < 21; r++) {
        for (int c = 15; c < 17; c++) {
            taken_positions.push_back({r, c, 1, 1});
        }
    }

    //pellets
    taken_positions.push_back({12,6, 1, 1});
    taken_positions.push_back({28,6, 1,1});
    taken_positions.push_back({3,23,1,1});
    taken_positions.push_back({31,23, 1,1});

    pellets.push_back({12,6, 1, 1});
    pellets.push_back({28,6, 1,1});
    pellets.push_back({3,23,1,1});
    pellets.push_back({31,23, 1,1});



    //dots vector
    ge211::Posn<int> position = {0,0};
    for (int r = 3; r < 32; r++) {
        for (int c = 3; c < 24; c++) {
            position.x = r;
            position.y = c;
            all_dots.push_back({position.x, position.y, 1, 1});
        }
    }

    //fruit
    for (int i =6; i < 11; i++) {
        fruits.push_back({i, 20, 1, 1});
        taken_positions.push_back({i, 20, 1, 1});
    }
    for (int i =14; i < 17; i++) {
        fruits.push_back({i, 22, 1, 1});
        taken_positions.push_back({i, 22, 1, 1});
    }
    for (int i =19; i < 22; i++) {
        fruits.push_back({i, 22, 1, 1});
        taken_positions.push_back({i, 22, 1, 1});
    }

    fruits.push_back({27, 6, 1, 1});
    taken_positions.push_back({27, 6, 1, 1});

    for (Block dot: all_dots) {
        bool intersect = false;
        for (Block wall: taken_positions) {
            if (dots_wall_overlap({dot.x*15, dot.y*15},
                                  5,
                                  {wall.x*15, wall.y*15})) {
                intersect = true;
            }
        }
        if (!intersect) {
            white_dots.push_back({dot.x, dot.y, 1, 1});
        }
    }
    white_dots.push_back({12,7, 1, 1});
    white_dots.push_back({4,23, 1,1});

}

int
Model::get_lives() const{
    return pacman.lives;
}

int
Model::get_score() const{
    return pacman.score;
}

bool
Model::win_game()
{
    if (white_dots.size() == 0) {
        return true;
    } else {
        return false;
    }
}

bool
Model::lose_game() {
    if (pacman.lives ==0) {
        return true;
    }
    else {
        return false;
    }
}

bool
Model::game_over()
{
    if (lose_game() or win_game()) {
        return true;
    }
    else {
        return false;
    }
}

void
Model::move_pacman_left()
{

    pacman.velocity.width = -50;
    pacman.velocity.height = 0;
}

void
Model::move_pacman_right()
{
    if (pacman.can_move_right) {
        pacman.velocity.width = 100;
        pacman.velocity.height = 0;
    }
    else {
        pacman.velocity.width = 0;
    }
}

void
Model::move_pacman_up()
//must specify which struct the function is a part of
{
    if (pacman.can_move_up) {
        pacman.velocity.height = -50;
        pacman.velocity.width = 0;
    }
    else {
        pacman.velocity.height = 0;
    }
}

void
Model::move_pacman_down()
{
    if (pacman.can_move_down) {
        pacman.velocity.height = 100;
        pacman.velocity.width = 0;
    }
    else {
        pacman.velocity.height = 0;
    }
}


void
Model::lose_a_life()
{
    pacman.stop_moving_x();
    pacman.stop_moving_y();
    pacman.set_center_pos(config.pacman_start_pos);
    pacman.lives --;
}



bool
Model::dots_wall_overlap(ge211::Posn<int> center, int radius,
                         ge211::Posn<int> wall) const
{

    if ((center.x + radius) < wall.x){
        return false;
    }
    else if ((center.x - radius) > (wall.x + 15)){
        return false;
    }else if ((center.y + radius) < wall.y){
        return false;
    }else if ((center.y - radius) > (wall.y + 15)){
        return false;
    }
    return true;

}


void
Model:: object_collision()
{
    int conversion_factor = 15;

    //eats pellet
    if (pacman.eats_object(conversion_factor/2, pellets)){
        pacman.score += 20;
        power_up_mode = true;

    }//eats dot
    if (pacman.eats_object(conversion_factor/3, white_dots)){
        pacman.score += 10;
    }//eats fruit
    if (pacman.eats_object(conversion_factor/3, fruits)){
        pacman.score += 50;
    }

}

void
Model::on_frame(double dt1)
{
    double dt = 1. / 60.;
    Pacman pacman_temp = pacman.next(dt);
    if (pacman_temp.hits_left_tunnel_edge(config)) {
        pacman.center.x += config.scene_dims.width - 25;
    }

    if (pacman_temp.hits_right_tunnel_edge(config)) {
        pacman.center.x -= config.scene_dims.width - 25;

    }
    //only works if u update the velocity on on_frame !!
    if (pacman_temp.hits_wall_update(walls)) {
        if (pacman.velocity.width != 0) {
            pacman.stop_moving_x();
        }
        if (pacman.velocity.height != 0) {
            pacman.stop_moving_y();
        }
    }


    if (pacman_temp.pacman_ghost_collision(ghost1.radius,ghost1.center_pos())) {
        if(power_up_mode) {
            pacman.score += 100;
            ghost1.stop_moving_x();
            ghost1.radius = 0;
            ghost1.set_center_pos(Position {255, 195});
            power_up_mode = false;
        }
        else if(!power_up_mode) {
            lose_a_life();
        }
    }

    if (pacman_temp.pacman_ghost_collision(ghost2.radius,ghost2.center_pos())) {
        if (power_up_mode) {
            pacman.score += 100;
            ghost2.stop_moving_x();
            ghost2.radius = 0;
            ghost2.set_center_pos(Position {225, 210});
            power_up_mode = false;

        }
        else if(!power_up_mode) {
            lose_a_life();
        }
    }

    if (pacman_temp.pacman_ghost_collision(ghost3.radius,ghost3.center_pos())) {
        if (power_up_mode) {
            pacman.score += 100;
            ghost3.stop_moving_y();
            ghost3.radius = 0;
            ghost3.set_center_pos(Position {255, 225});
            power_up_mode = false;

        }
        else if(!power_up_mode) {
            lose_a_life();
        }
    }

    if (pacman_temp.pacman_ghost_collision(ghost4.radius,ghost4.center_pos())) {
        if (power_up_mode) {
            pacman.score += 100;
            ghost4.stop_moving_y();
            ghost4.radius = 0;
            ghost4.set_center_pos(Position{285,210});
            power_up_mode = false;

        }
        else if(!power_up_mode) {
            lose_a_life();
        }
    }

    if (game_over()) {
        pacman.stop_moving_x();
        pacman.stop_moving_y();
        ghost1.stop_moving_x();
        ghost2.stop_moving_x();
        ghost3.stop_moving_y();
        ghost4.stop_moving_y();
    }


    Ghost ghost1_temp = ghost1.next(dt);

    if (ghost1_temp.hits_wall_update(walls)) {

        ghost1.velocity = ghost1.velocity * -1;
    }


    Ghost ghost2_temp = ghost2.next(dt);

    if (ghost2_temp.hits_wall_update(walls)) {

        ghost2.velocity = ghost2.velocity * -1;
    }


    Ghost ghost3_temp = ghost3.next(dt);

    if (ghost3_temp.hits_wall_update(walls)) {

        ghost3.velocity = ghost3.velocity * -1;
    }


    Ghost ghost4_temp = ghost4.next(dt);

    if (ghost4_temp.hits_wall_update(walls)) {

        ghost4.velocity = ghost4.velocity * -1;
    }

    pacman = pacman.next(dt);
    ghost1 = ghost1.next(dt);
    ghost2 = ghost2.next(dt);
    ghost3 = ghost3.next(dt);
    ghost4 = ghost4.next(dt);

    object_collision();

}



