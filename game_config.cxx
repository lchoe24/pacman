#include "game_config.hxx"

// This is the default (and only) constructor for `Game_config`. It
// determines all the default values of all the member variables.
Game_config::Game_config()
        : scene_dims {510, 405},
          pacman_radius {15},
          pacman_start_pos{248,270},
          pacman_start_velocity{ge211::Dims<int>{0,0}},
          pacman_lives{3},
          score{-20},
          ghost_radius{15},
          ghost_start_pos{200,120},
          ghost_start_velocity {ge211::Dims<int>{100,0}}

{ }