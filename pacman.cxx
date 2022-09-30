#include "pacman.hxx"
#include "view.hxx"

#include "game_config.hxx"

Pacman::Pacman(Game_config const& config)
        : radius(config.pacman_radius),
          center{config.pacman_start_pos},
          velocity{config.pacman_start_velocity},
          lives{config.pacman_lives},
          score{config.score},
          can_move_right{true},
          can_move_left{true},
          can_move_down{true},
          can_move_up{true}
{}

ge211::Posn<int>
Pacman::center_pos() const
{
    return ge211::Posn<int>(int(center.x), int(center.y));
}

void
Pacman::set_center_pos(ge211::Posn<int> p)
{center = p;}


bool
Pacman::hits_left_tunnel_edge(Game_config const& config) const
{
    if (center.x < 2) {
        return true;
    }
    return false;
}


bool
Pacman::hits_right_tunnel_edge(Game_config const& config) const
{
    Block right_tunnel(config.scene_dims.width - 35, config.scene_dims.height
                                                     / 2 - 5, 1/2, 10);
    //hits tunnel on left side
    if (((center.y > right_tunnel.y) or (center.y < right_tunnel.y +
                                                    right_tunnel.height)) and (center.x - radius >
                                                                               right_tunnel.x - right_tunnel.width)) {
        return true;
    }
    return false;
}

Pacman
Pacman::next(double dt) const
{
    Pacman result(*this);
    float delta_x = velocity.width * dt;
    float delta_y = velocity.height * dt;
    if (can_move_right and can_move_left) {
        result.center.x = result.center.x + delta_x;
    }
    if(can_move_down and can_move_up) {
        result.center.y = result.center.y + delta_y;
    }

    return result;
}

bool
Pacman::hits_wall(Block const& block)
{

    Block
            circle_block
            (center.x - radius, center.y - radius, radius * 2, radius * 2);


    int x = block.x * 15;
    int y = block.y*15;
    int width = block.width*15;
    int height = block.height*15;

    Block brick(x,y,width,height);

    //right side of rect       //left side of rect
    if (((brick.x + brick.width*2)  < circle_block.x + circle_block.width +1) or
        ((circle_block.x + circle_block.width) < brick.x -brick.width +1) or
        ((brick.y + brick.height) < circle_block.y + circle_block.height/2 +1)or
        ((circle_block.y + circle_block.height) < brick.y-brick.height +1)) {
        return false;
    }
    return true;
}


bool
Pacman::hits_object(Block const& block)
{

    Block
            circle_block
            (center.x - radius, center.y - radius, radius * 2, radius * 2);


    int width = block.width*15;
    int height = block.height*15;
    int x = block.x * 15 - width/2;
    int y = block.y*15 - width/2;

    Block brick(x,y,width,height);


    //right side of rect       //left side of rect
    if (((brick.x + brick.width*2)  < circle_block.x + circle_block.width +1) or
        ((circle_block.x + circle_block.width) < brick.x -brick.width +1) or
        ((brick.y + brick.height) < circle_block.y + circle_block.height/2 +1)or
        ((circle_block.y + circle_block.height) < brick.y-brick.height +1)) {

        return false;
    }
    return true;
}


bool
Pacman::hits_wall_update(std::vector<Block>& walls)
{
    for (Block& wall: walls) {
        if (hits_wall(wall)) {

            //hits wall when going right
            if (velocity.width > 0) {
                can_move_right = false;
                can_move_left = true;
                can_move_down = true;
                can_move_up = true;
            }

            if (velocity.width < 0) {
                can_move_right = true;
                can_move_left = false;
                can_move_down = true;
                can_move_up = true;
            }

            if (velocity.height > 0) {
                can_move_right = true;
                can_move_left = true;
                can_move_down = false;
                can_move_up = true;
            }

            if (velocity.width > 0) {
                can_move_right = true;
                can_move_left = true;
                can_move_down = true;
                can_move_up = false;
            }
            return true;
        }
    }
    //works if I put return true;
    return false;
}

void
Pacman::stop_moving_x() {
    velocity.width = 0;
}

void
Pacman::stop_moving_y() {
    velocity.height = 0;
}


static double
sqr_distance(Position p, Position q)
{
    int dx = p.x - q.x;
    int dy = p.y - q.y;
    return dx * dx + dy * dy;
}

bool
Pacman::eats_object (int object_radius, std::vector<Block>& object_vector)
{
    for (Block& o: object_vector) {
        if (hits_object(o)) {
            o = object_vector.back();
            object_vector.pop_back();
            return true;
        }
    }
    return false;
}


bool
Pacman::pacman_ghost_collision (int ghost_radius, ge211::Posn<int>
ghost_center) const
{
    double radii = radius + ghost_radius;
    return sqr_distance(center, ghost_center) <= radii * radii;
}