#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

struct Controller :  ge211::Abstract_game
{

    explicit Controller(Model& );


    void draw(ge211::Sprite_set& set) override;
    View::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

    void on_key(ge211::Key) override;

    void on_frame(double dt) override;

    Model& model;
    View view;
};