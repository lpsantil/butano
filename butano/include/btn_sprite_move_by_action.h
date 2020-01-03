#ifndef BTN_SPRITE_MOVE_BY_ACTION_H
#define BTN_SPRITE_MOVE_BY_ACTION_H

#include "btn_action.h"
#include "btn_utility.h"
#include "btn_sprite_ptr.h"
#include "btn_fixed_point.h"

namespace btn
{

class sprite_move_by_action : public action
{

public:
    sprite_move_by_action(sprite_ptr sprite, fixed x, fixed y) :
        sprite_move_by_action(move(sprite), fixed_point(x, y))
    {
    }

    sprite_move_by_action(sprite_ptr sprite, const fixed_point& delta_position) :
        _sprite(move(sprite)),
        _delta_position(delta_position),
        _initial_position(_sprite.position())
    {
    }

    void reset()
    {
        _sprite.set_position(_initial_position);
    }

    void update() override
    {
        _sprite.set_position(_sprite.position() + _delta_position);
    }

    bool done() const override
    {
        return false;
    }

    [[nodiscard]] const sprite_ptr& sprite() const
    {
        return _sprite;
    }

    [[nodiscard]] const fixed_point& delta_position() const
    {
        return _delta_position;
    }

    [[nodiscard]] const fixed_point& initial_position() const
    {
        return _initial_position;
    }

protected:
    sprite_ptr _sprite;
    fixed_point _delta_position;
    fixed_point _initial_position;
};

}

#endif