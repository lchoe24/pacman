#include "view.hxx"

#include "game_config.hxx"
#include "ghost.hxx"


Ghost::Ghost(Game_config const& config, Position position, Velocity velocity)
        : radius(config.ghost_radius),
          center{position},
          velocity{velocity},
          can_move_right{true},
          can_move_left{true},
          can_move_down{true},
          can_move_up{true}
{}

ge211::Posn<int>
Ghost::center_pos() const
{
    return ge211::Posn<int>(int(center.x), int(center.y));
}

void
Ghost::set_center_pos(ge211::Posn<int> p)
{
    center = p;
}

bool
Ghost::hits_left_tunnel_edge(Game_config const& config) const
{
    if (center.x < 2) {
        return true;
    }
    return false;
}


bool
Ghost::hits_right_tunnel_edge(Game_config const& config) const
{
    Block right_tunnel(config.scene_dims.width - 35, config.scene_dims.height
                                                     / 2 - 5, 1/2, 10);
    //hits tunnel on left side
    if (((center.y > right_tunnel.y) or (center.y < right_tunnel.y +
                                                    right_tunnel
                                                            .height)) and (center.x - radius > right_tunnel.x - right_tunnel
            .width
        )) {
        return true;
    }
    return false;
}

Ghost
Ghost::next(double dt) const
{
    Ghost result(*this);
    float delta_x = velocity.width * dt;
    float delta_y = velocity.height * dt;
    if(can_move_right or can_move_left) {
        result.center.x = result.center.x + delta_x;
    }
    if(can_move_down or can_move_up) {
        result.center.y = result.center.y + delta_y;
    }

    return result;
}

bool
Ghost::hits_wall(Block const& block)
{

    Block
            circle_block
            (center.x - radius, center.y - radius, radius * 2, radius * 2);


    /*
    int x = (center.x - radius) /15;
    int y = (center.y - radius) /15;
    int width = (radius*2) /15;

    Block circle_block(x,y,width,width);
*/

    int x = block.x * 15;
    int y = block.y*15;
    int width = block.width*15;
    int height = block.height*15;

    Block brick(x,y,width,height);


    //std::cout << circle_block.x;

    //right side of rect       //left side of rect
    if (((brick.x + brick.width*2)  < circle_block.x + circle_block.width +1) or
        ((circle_block.x + circle_block.width) < brick.x -brick.width +1) or
        ((brick.y + brick.height) < circle_block.y + circle_block.height/2 +1) or
        ((circle_block.y + circle_block.height) < brick.y-brick.height +1)) {

        return false;
    }
    return true;
}


bool
Ghost::hits_wall_update(std::vector<Block>& walls)
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
    //works if i put return true;
    return false;
}

void
Ghost::stop_moving_x() {
    velocity.width = 0;
}

void
Ghost::stop_moving_y() {
    velocity.height = 0;
}

