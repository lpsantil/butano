/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "bn_blending_fade_alpha_hblank_effect_ptr.h"

#include "bn_span.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_display_manager.h"
#include "bn_blending_fade_alpha.h"
#include "bn_hblank_effects_manager.h"

namespace bn
{

blending_fade_alpha_hblank_effect_ptr blending_fade_alpha_hblank_effect_ptr::create(
        const span<const blending_fade_alpha>& alphas_ref)
{
    BN_ASSERT(display_manager::blending_transparency_alpha() == 1,
               "Transparency and fade blendings can't be enabled at the same time");
    BN_ASSERT(display_manager::blending_intensity_alpha() == 0,
               "Intensity and fade blendings can't be enabled at the same time");

    int id = hblank_effects_manager::create(alphas_ref.data(), alphas_ref.size(), 0,
                                            hblank_effects_manager::handler_type::BLENDING_FADE_ALPHA);
    return blending_fade_alpha_hblank_effect_ptr(id);
}

optional<blending_fade_alpha_hblank_effect_ptr> blending_fade_alpha_hblank_effect_ptr::create_optional(
        const span<const blending_fade_alpha>& alphas_ref)
{
    BN_ASSERT(display_manager::blending_transparency_alpha() == 1,
               "Transparency and fade blendings can't be enabled at the same time");
    BN_ASSERT(display_manager::blending_intensity_alpha() == 0,
               "Intensity and fade blendings can't be enabled at the same time");

    int id = hblank_effects_manager::create_optional(alphas_ref.data(), alphas_ref.size(), 0,
                                                     hblank_effects_manager::handler_type::BLENDING_FADE_ALPHA);
    optional<blending_fade_alpha_hblank_effect_ptr> result;

    if(id >= 0)
    {
        result = blending_fade_alpha_hblank_effect_ptr(id);
    }

    return result;
}

span<const blending_fade_alpha> blending_fade_alpha_hblank_effect_ptr::alphas_ref() const
{
    auto alphas_ptr = reinterpret_cast<const blending_fade_alpha*>(hblank_effects_manager::values_ref(id()));
    return span<const blending_fade_alpha>(alphas_ptr, display::height());
}

void blending_fade_alpha_hblank_effect_ptr::set_alphas_ref(const span<const blending_fade_alpha>& alphas_ref)
{
    hblank_effects_manager::set_values_ref(id(), alphas_ref.data(), alphas_ref.size());
}

void blending_fade_alpha_hblank_effect_ptr::reload_alphas_ref()
{
    hblank_effects_manager::reload_values_ref(id());
}

blending_fade_alpha_hblank_effect_ptr::blending_fade_alpha_hblank_effect_ptr(int id) :
    hblank_effect_ptr(id)
{
}

}
