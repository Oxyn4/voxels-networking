/*
This file is part of the Voxels networking library.

the voxels networking library is free software: you can redistribute it and/or modify it under the terms of the
GNU General Public License as published by the Free Software Foundation, either version 3 of the License,
or (at your option) any later version. the Voxels networking library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details. You should have received a copy of the GNU General Public
License along with the voxels networking library. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "control_steam.hpp"

namespace voxels::protocols::game {
    class Connection;
}

namespace voxels::protocols::game::responses {
    class ControlStreamResponse {};

    class ControlStreamInitiated final : public ControlStreamResponse {};
}

namespace voxels::protocols::game::events {
    class ConnectionEvent {
    public:
        std::weak_ptr<Connection> Connection_;

        explicit ConnectionEvent(const std::weak_ptr<Connection>& Connection_)
            : Connection_(Connection_) {};
    };

    class ControlStreamInitiated final : public ConnectionEvent {
    public:
        std::weak_ptr<ControlSteam> ControlStream_;

        ControlStreamInitiated(const std::weak_ptr<Connection> &Connection_, const std::weak_ptr<ControlSteam> &ControlStream_)
            : ConnectionEvent(Connection_), ControlStream_{ControlStream_} {};
    };
}

namespace voxels::protocols::game {
    class Connection final {
    private:

    public:
        boost::signals2::signal<
          responses::ControlStreamInitiated(const events::ControlStreamInitiated&)
        > ControlStreamInitiatedSignal;

    };
}
