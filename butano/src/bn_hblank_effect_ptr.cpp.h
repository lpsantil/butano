/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "bn_hblank_effect_ptr.h"

#include "bn_span.h"
#include "bn_hblank_effects_manager.h"

namespace bn
{

bool hblank_effect_ptr::visible() const
{
    return hblank_effects_manager::visible(_id);
}

void hblank_effect_ptr::set_visible(bool visible)
{
    hblank_effects_manager::set_visible(_id, visible);
}

hblank_effect_ptr::hblank_effect_ptr(const hblank_effect_ptr& other) :
    hblank_effect_ptr(other._id)
{
    hblank_effects_manager::increase_usages(_id);
}

hblank_effect_ptr& hblank_effect_ptr::operator=(const hblank_effect_ptr& other)
{
    if(_id != other._id)
    {
        if(_id >= 0)
        {
            hblank_effects_manager::decrease_usages(_id);
        }

        _id = other._id;
        hblank_effects_manager::increase_usages(_id);
    }

    return *this;
}

void hblank_effect_ptr::_destroy()
{
    hblank_effects_manager::decrease_usages(_id);
}

}
