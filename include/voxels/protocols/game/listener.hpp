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

#include "connection.hpp"
#include "event_dispatcher.hpp"

#include <boost/signals2.hpp>

#include <boost/asio.hpp>


#include <memory>

namespace voxels::protocols::game {
    class Listener;
}

namespace voxels::protocols::game::responses {
    class ListenerResponse {};

    class NewConnection final : private ListenerResponse {};
}

namespace voxels::protocols::game::events {
    class ListenerEvent {
        using ConnectionT = Connection<Server> ;

    public:
        const std::weak_ptr<Listener> Listener_;

        explicit ListenerEvent(const std::weak_ptr<Listener> &Listener_) : Listener_(Listener_) {}
    };

    class NewConnectionEvent final : private ListenerEvent {
        using ConnectionT = Connection<Server> ;

    public:
        const std::weak_ptr<ConnectionT> Connection_;

        NewConnectionEvent(const std::weak_ptr<Listener>& Listener_, const std::weak_ptr<ConnectionT>& Connection) : ListenerEvent(Listener_), Connection_(Connection) {}
    };

}

namespace voxels::protocols::game {

    // The listener works as an event dispatcher for events related to managing connections
    class Listener final : public EventDispatcher {
        using ConnectionT = Connection<Server>;

    private:
        // local endpoint of our Listener object, usually our machines ip address and a UDP port
        boost::asio::ip::udp::endpoint LocalEndpoint;

        // the connection objects managed by this Listener
        std::vector<
            std::shared_ptr<ConnectionT>
        > Connections;
    public:
        explicit Listener(const boost::asio::ip::address& Address, const uint16_t Port) : LocalEndpoint(Address, Port) {};
        ~Listener() = default;

        // each different event gets a signal which manages multiple Callback functions for that event
        boost::signals2::signal<
            responses::NewConnection(const events::NewConnectionEvent&)
        > NewConnectionSignal;


    };
}