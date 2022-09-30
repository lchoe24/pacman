#pragma once
#include "../.cs211/lib/ge211/include/ge211_geometry.hxx"

using Position = ge211::Posn<int>;

struct Game_config
{
    Game_config();

    ge211::Dims<int> scene_dims;
    int pacman_radius;

    Position pacman_start_pos;

    ge211::Dims<int> pacman_start_velocity;

    int pacman_lives;

    int score;

    int ghost_radius;
    Position ghost_start_pos;
    ge211::Dims<int> ghost_start_velocity;


};