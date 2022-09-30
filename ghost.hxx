//
// Created by Lena Choe on 2021/11/29.
//

#ifndef GAME_GHOST_HXX
#define GAME_GHOST_HXX


#pragma once

#include "../.cs211/lib/ge211/include/ge211_geometry.hxx"

#include "game_config.hxx"

#include <iostream>


using Position = ge211::Posn<int>;

using Block = ge211::Rect<int>;

using Velocity = ge211::Dims<float>;

struct Ghost
{
    //constructor
    Ghost(Game_config const&, Position position, Velocity velocity);

    //Ghost(Game_config const&, Velocity velocity);

    ge211::Posn<int> center_pos() const;

    void set_center_pos(ge211::Posn<int> p);


    bool hits_left_tunnel_edge(Game_config const&) const;
    bool hits_right_tunnel_edge(Game_config const&) const;

    Ghost next(double dt) const;
    bool hits_wall(Block const& brick);
    bool hits_wall_update(std::vector<Block>& walls);

    void stop_moving_x();
    void stop_moving_y();


    int radius;

    Position center;

    Velocity velocity;



    bool can_move_right;
    bool can_move_left;
    bool can_move_down;
    bool can_move_up;
};


#endif //GAME_GHOST_HXX