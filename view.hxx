#pragma once

#include "model.hxx"
#include <string>

class View
{
public:
    using Dimensions = ge211::Dims<int>;

    explicit View(Model const& model);
    ge211::Circle_sprite const pacman_sprite;
    ge211::Circle_sprite const lives_sprite;
    ge211::Circle_sprite const dead_lives_sprite;
    ge211::Circle_sprite const dots_sprite;
    ge211::Circle_sprite const fruit_sprite;
    ge211::Circle_sprite const pellet_sprite;
    ge211::Circle_sprite const blinky_sprite;
    ge211::Circle_sprite const pinky_sprite;
    ge211::Circle_sprite const inky_sprite;
    ge211::Circle_sprite const clyde_sprite;
    ge211::Circle_sprite const powerupmode_sprite;
    ge211::Rectangle_sprite const wall_sprite;
    ge211::Rectangle_sprite const black_tunnel_sprite;
    ge211::Text_sprite const win_sprite;
    ge211::Text_sprite const lose_sprite;


    void draw(ge211::Sprite_set& set);

    Dimensions initial_window_dimensions() const;
    std::string initial_window_title() const;

private:
    Model const& model_;
    ge211::Text_sprite score_sprite;
    ge211::Font sans15_{"sans.ttf", 15};

    ge211::Posn<int> board_to_screen(ge211::Posn<int> position);
    ge211::Posn<int> dots_top_left(ge211::Posn<int> position, int radius);
};
