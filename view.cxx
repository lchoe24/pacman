#include "view.hxx"
#include "model.hxx"


using Color = ge211::Color;

ge211::Dims<int> const scene_dims {510, 405};

static int const conversion_factor = 15;

static Color const pacman_color = Color::medium_yellow();
static Color const black_color = Color::black();
static Color const dead_lives_color = Color::black().blend(.5,
                                                           Color::white());
static Color const dots_color = Color::white();
static Color const fruit_color = Color::medium_magenta();
static Color const wall_color = Color::medium_blue();
static Color const blinky_color = Color::medium_red();
static Color const pinky_color = Color::medium_red().blend(.5, Color::white());
static Color const inky_color = Color::medium_cyan();
static Color const clyde_color = Color::medium_red().blend(.5, Color::medium_yellow());
static Color const powerupmode_color = Color::medium_blue().blend(.4,
                                                                  Color::black
                                                                          ());

View::View(Model const& model)
        : pacman_sprite(conversion_factor, pacman_color),
          lives_sprite(conversion_factor/2, pacman_color),
          dead_lives_sprite(conversion_factor/2, dead_lives_color),
          dots_sprite(conversion_factor/3, dots_color),
          fruit_sprite(conversion_factor/3, fruit_color),
          pellet_sprite(conversion_factor/2, dots_color),
          blinky_sprite(conversion_factor, blinky_color),
          pinky_sprite(conversion_factor, pinky_color),
          inky_sprite(conversion_factor, inky_color),
          clyde_sprite(conversion_factor, clyde_color),
          powerupmode_sprite(conversion_factor, powerupmode_color),
          wall_sprite({conversion_factor, conversion_factor}, wall_color),
          black_tunnel_sprite({conversion_factor, conversion_factor}, black_color),
          win_sprite("YOU WIN", {"sans.ttf", 50}),
          lose_sprite("GAME OVER", {"sans.ttf", 50}),
          model_(model),
          score_sprite()
{ }


ge211::Posn<int>
View::board_to_screen(ge211::Posn<int> logical) //logical is board position
{
    ge211::Posn<int> p(0,0);
    p.x = logical.x * conversion_factor;
    p.y = logical.y * conversion_factor;
    return p;
}

ge211::Posn<int>
View::dots_top_left(ge211::Posn<int> logical, int radius)
{
    ge211::Posn<int> p(0,0);

    p.x = logical.x * conversion_factor - radius;
    p.y = logical.y * conversion_factor - radius;
    return p;
}

void
View::draw(ge211::Sprite_set& set)
{
    //pacman
    set.add_sprite(pacman_sprite, model_.pacman.center_pos());

    //pellets
    int p_radius = conversion_factor / 2;
    for (Block pellet: model_.pellets) {
        set.add_sprite(pellet_sprite, dots_top_left({pellet.x, pellet.y},
                                                    p_radius), -1);
    }

    // fruits
    int f_radius = conversion_factor / 3;
    for (Block fruit: model_.fruits) {
        set.add_sprite(fruit_sprite, dots_top_left({fruit.x, fruit.y},
                                                   f_radius), -1);
    }

    //ghosts
    if (!model_.power_up_mode) {
        set.add_sprite(blinky_sprite, model_.ghost1.center_pos());
        set.add_sprite(pinky_sprite, model_.ghost2.center_pos());
        set.add_sprite(inky_sprite, model_.ghost3.center_pos());
        set.add_sprite(clyde_sprite, model_.ghost4.center_pos());
    }
    else if (model_.power_up_mode) {
        set.add_sprite(powerupmode_sprite, model_.ghost1.center_pos());
        set.add_sprite(powerupmode_sprite, model_.ghost2.center_pos());
        set.add_sprite(powerupmode_sprite, model_.ghost3.center_pos());
        set.add_sprite(powerupmode_sprite, model_.ghost4.center_pos());
    }

    //lives
    int z = 2;
    for (int r = 1; r < 4; r++) {
        set.add_sprite(lives_sprite, board_to_screen({r, 26}), z);
        if (model_.get_lives() == 2) {
            set.add_sprite(dead_lives_sprite,board_to_screen({3, 26}),z + 1);
        }if (model_.get_lives() == 1) {
            set.add_sprite(dead_lives_sprite,board_to_screen({3, 26}),z + 1);
            set.add_sprite(dead_lives_sprite,board_to_screen({2, 26}),z + 1);
        }if (model_.get_lives() == 0) {
            set.add_sprite(dead_lives_sprite,board_to_screen({1, 26}),z + 1);
            set.add_sprite(dead_lives_sprite,board_to_screen({3, 26}),z + 1);
            set.add_sprite(dead_lives_sprite,board_to_screen({2, 26}),z + 1);
            set.add_sprite(lose_sprite, board_to_screen({7, 12}), 3);
        }
    }

    //black tunnel
    //left
    for (int r = 0; r < 2; r++) {
        for (int c = 13; c < 15; c++) {
            set.add_sprite(black_tunnel_sprite, board_to_screen({r, c}), 1);
        }
    }//right
    for (int r = 32; r < 35; r++) {
        for (int c = 13; c < 15; c++) {
            set.add_sprite(black_tunnel_sprite, board_to_screen({r, c}), 1);
        }
    }

    //walls
    for (Block wall: model_.walls) {
        set.add_sprite(wall_sprite, board_to_screen(wall.top_left()), 2);
    }


    for (Block dot : model_.white_dots){
        set.add_sprite(dots_sprite, dots_top_left({dot.x, dot.y},
                                                  conversion_factor /
                                                  3), -1);
    }

    if (model_.white_dots.size() == 0) {
        set.add_sprite(win_sprite, board_to_screen({10, 12}), 3);
    }

    // Build the text sprite
    ge211::Text_sprite::Builder builder(sans15_);
    builder.color(Color::white());
    builder << "Score: " << model_.get_score();
    score_sprite.reconfigure(builder);
    set.add_sprite(score_sprite, board_to_screen({27, 25}));

}

View::Dimensions
View::initial_window_dimensions() const
{
    return scene_dims;
}

std::string
View::initial_window_title() const
{
    return "PACMAN";
}