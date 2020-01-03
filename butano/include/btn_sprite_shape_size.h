#ifndef BTN_SPRITE_SHAPE_SIZE_H
#define BTN_SPRITE_SHAPE_SIZE_H

#include "btn_assert.h"

namespace btn
{

enum class sprite_shape
{
    SQUARE,
    WIDE,
    TALL
};

enum class sprite_size
{
    SMALL,
    NORMAL,
    BIG,
    HUGE
};


/**
 * @brief Calculates sprite dimensions from its shape and size.
 *
 * shape\size 	00 	01 	10 	11
 * 00	8x8 	16x16 	32x32 	64x64
 * 01	16x8 	32x8 	32x16 	64x32
 * 10	8x16 	8x32 	16x32 	32x64
 */
class sprite_shape_size
{

public:
    constexpr sprite_shape_size(sprite_shape shape, sprite_size size) :
        _shape(shape),
        _size(size)
    {
    }

    [[nodiscard]] constexpr sprite_shape shape() const
    {
        return _shape;
    }

    [[nodiscard]] constexpr sprite_size size() const
    {
        return _size;
    }

    [[nodiscard]] constexpr int width() const
    {
        switch(_shape)
        {

        case sprite_shape::SQUARE:
            switch(_size)
            {

            case sprite_size::SMALL:
                return 8;

            case sprite_size::NORMAL:
                return 16;

            case sprite_size::BIG:
                return 32;

            case sprite_size::HUGE:
                return 64;
            }
            break;

        case sprite_shape::WIDE:
            switch(_size)
            {

            case sprite_size::SMALL:
                return 16;

            case sprite_size::NORMAL:
                return 32;

            case sprite_size::BIG:
                return 32;

            case sprite_size::HUGE:
                return 64;
            }
            break;

        case sprite_shape::TALL:
            switch(_size)
            {

            case sprite_size::SMALL:
                return 8;

            case sprite_size::NORMAL:
                return 8;

            case sprite_size::BIG:
                return 16;

            case sprite_size::HUGE:
                return 32;
            }
            break;
        }

        BTN_CONSTEXPR_ASSERT(false, "Invalid shape or size");
        return 0;
    }

    [[nodiscard]] constexpr int height() const
    {
        switch(_shape)
        {

        case sprite_shape::SQUARE:
            switch(_size)
            {

            case sprite_size::SMALL:
                return 8;

            case sprite_size::NORMAL:
                return 16;

            case sprite_size::BIG:
                return 32;

            case sprite_size::HUGE:
                return 64;
            }
            break;

        case sprite_shape::WIDE:
            switch(_size)
            {

            case sprite_size::SMALL:
                return 8;

            case sprite_size::NORMAL:
                return 8;

            case sprite_size::BIG:
                return 16;

            case sprite_size::HUGE:
                return 32;
            }
            break;

        case sprite_shape::TALL:
            switch(_size)
            {

            case sprite_size::SMALL:
                return 16;

            case sprite_size::NORMAL:
                return 32;

            case sprite_size::BIG:
                return 32;

            case sprite_size::HUGE:
                return 64;
            }
            break;
        }

        BTN_CONSTEXPR_ASSERT(false, "Invalid shape or size");
        return 0;
    }

    [[nodiscard]] constexpr int pixels() const
    {
        return width() * height();
    }

    [[nodiscard]] constexpr int tiles(bool eight_bits_per_pixel) const
    {
        return eight_bits_per_pixel ? pixels() / 32 : pixels() / 64;
    }

private:
    sprite_shape _shape;
    sprite_size _size;
};

}

#endif