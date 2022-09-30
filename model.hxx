#pragma once

#include <ge211.hxx>
#include "game_config.hxx"
#include "pacman.hxx"
#include "ghost.hxx"
#include <vector>



struct Model
{

    explicit Model(Game_config const& config = Game_config());
    using Block = ge211::Rect<int>;

    int get_lives() const;
    bool win_game();
    bool lose_game();
    bool game_over();
    int get_score() const;
    void move_pacman_left();
    void move_pacman_right();
    void move_pacman_up();
    void move_pacman_down();
    void lose_a_life();

    //ge211::Dims<int> const scene_dims {510, 405};

    std::vector<Block> walls;
    std::vector<Block> pellets;

    std::vector<Block> all_dots;
    std::vector<Block> white_dots;
    std::vector<Block> fruits;
    std::vector<Block> taken_positions;


    bool dots_wall_overlap(ge211::Posn<int> center, int radius,
                           ge211::Posn<int> wall) const;

    void object_collision();

    void on_frame(double dt);

    Game_config const config;
    Pacman pacman;
    Velocity ghost1_vel{100,0};
    Velocity ghost2_vel{-100,0};
    Velocity ghost3_vel{0,-100};
    Velocity ghost4_vel{0,100};
    Position ghost1_start_pos{200,120};
    Position ghost2_start_pos{300,30};
    Position ghost3_start_pos{165,315};
    Position ghost4_start_pos{450,300};
    Ghost ghost1;
    Ghost ghost2;
    Ghost ghost3;
    Ghost ghost4;

    //ge211::Posn<int> large_center {scene_dims.width / 2, scene_dims.height /
    //2};

    bool power_up_mode = false;

};
