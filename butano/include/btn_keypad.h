#ifndef BTN_KEYPAD_H
#define BTN_KEYPAD_H

#include "btn_common.h"

namespace btn::keypad
{
    enum class button_type
    {
        A =         0x0001,
        B =         0x0002,
        SELECT =    0x0004,
        START =     0x0008,
        RIGHT =     0x0010,
        LEFT =      0x0020,
        UP =        0x0040,
        DOWN =      0x0080,
        R =         0x0100,
        L =         0x0200
    };

    [[nodiscard]] bool down(button_type button);

    [[nodiscard]] bool up(button_type button);

    [[nodiscard]] bool held(button_type button);

    [[nodiscard]] bool pressed(button_type button);

    [[nodiscard]] bool released(button_type button);
}

#endif