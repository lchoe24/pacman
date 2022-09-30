#ifndef GAME_PACMAN_HXX
#define GAME_PACMAN_HXX

#pragma once

#include "../.cs211/lib/ge211/include/ge211_geometry.hxx"

#include "game_config.hxx"



#include <iostream>

#include <vector>

using Position = ge211::Posn<int>;

using Block = ge211::Rect<int>;

using Velocity = ge211::Dims<float>;

struct Pacman
{
    //constructor
    Pacman(Game_config const&);

    ge211::Posn<int> center_pos() const;

    void set_center_pos(ge211::Posn<int> p);

    bool hits_left_tunnel_edge(Game_config const&) const;
    bool hits_right_tunnel_edge(Game_config const&) const;

    Pacman next(double dt) const;
    bool hits_wall(Block const& brick);
    bool hits_object(Block const& brick);
    bool hits_wall_update(std::vector<Block>& walls);

    void stop_moving_x();
    void stop_moving_y();

    int radius;

    Position center;
    Velocity velocity;

    int lives;
    int score;

    bool can_move_right;
    bool can_move_left;
    bool can_move_down;
    bool can_move_up;


    bool eats_object (int object_radius, std::vector<Block>& object_vector);

    bool pacman_ghost_collision (int ghost_radius, ge211::Posn<int>
    ghost_center) const;


};


#endif //GAME_PACMAN_HXX