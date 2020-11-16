/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BN_HW_LINK_H
#define BN_HW_LINK_H

#include "bn_hw_irq.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvolatile"
#pragma GCC diagnostic ignored "-Wpedantic"

#include "../3rd_party/gba-link-connection/include/LinkConnection.h"

#pragma GCC diagnostic pop

namespace bn::hw::link
{
    using connection = LinkConnection;
    using state = LinkState;

    BN_CODE_IWRAM void _intr();

    inline void init(int baud_rate, connection& connection_ref)
    {
        linkConnection = &connection_ref;
        irq::replace_or_push_back(irq::id::SERIAL, _intr);
        connection_ref.init(connection::BaudRate(baud_rate));
    }

    inline void enable()
    {
        irq::enable(irq::id::SERIAL);
    }

    inline void disable()
    {
        irq::disable(irq::id::SERIAL);
    }
}

#endif