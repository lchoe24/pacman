#include "controller.hxx"

Controller::Controller(Model& model)
        : model(model),
          view(model)

{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view.draw(set);
}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::left()) {
        model.move_pacman_left();

    } else if (key == ge211::Key::right()) {
        model.move_pacman_right();

    } else if (key == ge211::Key::up()) {
        model.move_pacman_up();

    } else if (key == ge211::Key::down()) {
        model.move_pacman_down();

    } else if (key == ge211::Key::code('q')) {
        quit();
    }
}

void
Controller::on_frame(double dt)
{
    model.on_frame(dt);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view.initial_window_title();
}