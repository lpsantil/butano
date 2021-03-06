/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "bn_core.h"
#include "bn_display.h"
#include "bn_bgs_mosaic.h"
#include "bn_regular_bg_items_stage_1.h"
#include "bn_regular_bg_position_hblank_effect_ptr.h"
#include "wave_generator.h"

namespace
{
    [[nodiscard]] constexpr bn::array<bn::fixed, bn::display::height()> _create_hblank_effect_deltas()
    {
        bn::array<bn::fixed, bn::display::height()> result;
        wave_generator().generate(result);
        return result;
    }

    constexpr const bn::array<bn::fixed, bn::display::height()> hblank_effect_deltas = _create_hblank_effect_deltas();
}

int main()
{
    bn::core::init();

    bn::regular_bg_ptr bg = bn::regular_bg_items::stage_1.create_bg(0, 0);
    bg.set_mosaic_enabled(true);
    bn::bgs_mosaic::set_stretch(0.2);

    bn::regular_bg_position_hblank_effect_ptr hblank_effect =
            bn::regular_bg_position_hblank_effect_ptr::create_horizontal(move(bg), hblank_effect_deltas);

    while(true)
    {
        bn::core::update();
    }
}
