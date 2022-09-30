#include "pacman.hxx"
#include "ghost.hxx"
#include "model.hxx"
#include <catch.hxx>

Game_config const config;

TEST_CASE( "ghost eats pacman")
{
    Model m(config);

    //pacman does not lose life when not touching ghost
    m.ghost1.center = Position(100, 100);
    m.ghost2.center = Position(100, 200);
    m.ghost3.center = Position(100, 300);
    m.ghost4.center = Position(100, 400);
    m.ghost1.velocity.width = 0;
    m.ghost2.velocity.width = 0;
    m.ghost3.velocity.height = 0;
    m.ghost4.velocity.height = 0;

    m.pacman.center = Position(100, 150);
    CHECK(m.pacman.lives == 3);

    //pacman loses a life when touching ghost if not in power up mode
    m.power_up_mode = false;
    m.pacman.center = Position(100, 200);
    m.ghost1.center = Position(100, 205);
    CHECK(m.pacman.lives == 2);

    //pacman does not lose a life if in power_up_mode
    m.power_up_mode = true;
    m.pacman.center = Position(100, 200);
    m.ghost1.center = Position(100, 205);
    CHECK(m.pacman.lives == 2);
}


TEST_CASE( "pacman eats ghost: power up")
{
    Model m(config);
    m.power_up_mode = false;
    m.pacman.center = Position(100,100);
    int num_pellets = m.pellets.size();

    for (Block& d: m.pellets) {
        m.pacman.center = Position(d.x, d.y);
        CHECK (m.power_up_mode == true);

        m.ghost1.center = Position(400,400);
        CHECK(m.pacman.lives == 3);

        m.ghost1.center = Position(100,100);
        CHECK(m.pacman.lives == 3);
    }

    CHECK(m.get_score() == num_pellets*20 + num_pellets*100);

}

TEST_CASE( "pacman eat dots")
{
    Model m(config);
    int num_dots = m.white_dots.size();

    for (Block& d: m.white_dots) {
        m.pacman.center = Position(d.x,d.y);
    }

    CHECK(m.white_dots.size() == 0);
    CHECK(m.get_score() == num_dots*10);
    CHECK(m.win_game());
}

TEST_CASE( "pacman eat fruits")
{
    Model m(config);
    int num_fruits = m.fruits.size();

    for (Block& d: m.fruits) {
        m.pacman.center = Position(d.x,d.y);
    }

    CHECK(m.fruits.size() == 0);
    CHECK(m.get_score() == num_fruits*50);

}

TEST_CASE( "lose game")
{
    Model m1(config);
    m1.pacman.lives--;
    m1.pacman.lives--;
    m1.pacman.lives--;
    CHECK(m1.lose_game());

    Model m2(config);
    m2.pacman.center = m2.ghost1.center;
    CHECK(m2.pacman.lives == 3);
    m2.pacman.center = m2.ghost2.center;
    CHECK(m2.pacman.lives == 1);
    m2.pacman.center = m2.ghost3.center;
    CHECK(m2.pacman.lives == 0);
    CHECK(m2.lose_game());

    Model m3(config);
    m3.pacman.lives = 0;
    CHECK(m3.lose_game());
    CHECK(m3.ghost1.velocity == Velocity{0,0});
    CHECK(m3.ghost2.velocity == Velocity{0,0});
    CHECK(m3.ghost3.velocity == Velocity{0,0});
    CHECK(m3.ghost4.velocity == Velocity{0,0});
    CHECK(m3.pacman.velocity == Velocity{0,0});

}
