#ifndef BTN_SPRITE_FONT_H
#define BTN_SPRITE_FONT_H

#include "btn_string_view.h"
#include "btn_sprite_item.h"
#include "btn_utf8_character.h"
#include "btn_config_sprite_text.h"

namespace btn
{

class sprite_font
{

public:
    static constexpr const int minimum_graphics = 94;

    constexpr sprite_font(const sprite_item& item, const span<const string_view>& utf8_characters) :
        _item(item),
        _utf8_characters(utf8_characters)
    {
        BTN_CONSTEXPR_ASSERT((item.shape() == sprite_shape::SQUARE || item.shape() == sprite_shape::TALL) &&
                             item.size() == sprite_size::SMALL, "Invalid shape or size");
        BTN_CONSTEXPR_ASSERT(item.tiles_item().graphics() >= minimum_graphics + int(utf8_characters.size()),
                             "Invalid graphics or utf8 characters count");
        BTN_CONSTEXPR_ASSERT(item.palette_item().palette().size() == 16, "Invalid colors count");
        BTN_CONSTEXPR_ASSERT(utf8_characters.size() <= BTN_CFG_SPRITE_TEXT_MAX_UTF8_CHARACTERS,
                             "Invalid utf8 characters count");
        BTN_CONSTEXPR_ASSERT(_validate_utf8_characters(utf8_characters), "Utf8 characters validation failed");
        BTN_CONSTEXPR_ASSERT(! _duplicated_utf8_characters(utf8_characters), "There's duplicated utf8 characters");
    }

    [[nodiscard]] constexpr const sprite_item& item() const
    {
        return _item;
    }

    [[nodiscard]] constexpr const span<const string_view>& utf8_characters() const
    {
        return _utf8_characters;
    }

    [[nodiscard]] constexpr bool operator==(const sprite_font& other) const
    {
        return _item == other._item && _utf8_characters == other._utf8_characters;
    }

    [[nodiscard]] constexpr bool operator!=(const sprite_font& other) const
    {
        return ! (*this == other);
    }

private:
    sprite_item _item;
    span<const string_view> _utf8_characters;

    [[nodiscard]] static constexpr bool _validate_utf8_characters(const span<const string_view>& utf8_characters)
    {
        for(const string_view& utf8_character_text : utf8_characters)
        {
            utf8_character utf8_char(utf8_character_text.data());

            if(utf8_char.value() <= '~')
            {
                return false;
            }

            if(utf8_char.size() != int(utf8_character_text.size()))
            {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] static constexpr bool _duplicated_utf8_characters(const span<const string_view>& utf8_characters)
    {
        for(size_t i = 0, size = utf8_characters.size(); i < size; ++i)
        {
            const string_view& a = utf8_characters[i];

            for(size_t j = i + 1; j < size; ++j)
            {
                const string_view& b = utf8_characters[j];

                if(a == b)
                {
                    return true;
                }
            }
        }

        return false;
    }
};

}

#endif