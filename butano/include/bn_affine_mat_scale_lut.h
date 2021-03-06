/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BN_AFFINE_MAT_SCALE_LUT_H
#define BN_AFFINE_MAT_SCALE_LUT_H

/**
 * @file
 * bn::affine_mat_scale_lut header file.
 *
 * @ingroup affine_mat
 */

#include "bn_array.h"
#include "bn_fixed.h"

namespace bn
{

/**
 * @brief Returns the LUT used to invert scale values in an affine transformation matrix.
 *
 * @ingroup affine_mat
 */
[[nodiscard]] constexpr array<uint16_t, 1025> create_affine_mat_scale_lut()
{
    array<uint16_t, 1025> result = {};
    int one = fixed_t<8>(1).data() * fixed_t<8>::scale();

    for(int index = 1; index < 1025; ++index)
    {
        result[index] = uint16_t(one / index);
    }

    return result;
}

/**
 * @brief LUT used to invert scale values in an affine transformation matrix.
 *
 * @ingroup affine_mat
 */
constexpr const array<uint16_t, 1025> affine_mat_scale_lut = create_affine_mat_scale_lut();

}

#endif
