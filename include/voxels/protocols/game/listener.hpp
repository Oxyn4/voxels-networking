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

#include <boost/asio.hpp>

#include <memory>

#include "msquic.hpp"

#include "listener_dispatcher.hpp"

namespace voxels::protocols::game {

    struct ListenerSettings final {
        std::chrono::milliseconds Timeout;

        ListenerSettings() : Timeout(std::chrono::milliseconds(5000)) {}

        operator msquic::ListenerSettings () const {
            msquic::ListenerSettings New;

            New.Timeout = Timeout;

            return New;
        }
    };

    // The listener works as an event dispatcher for events related to managing connections
    class Listener final {
        using ConnectionT = Connection<Server>;

    private:
        // the underlying quic listener object
        msquic::Listener QuicListener;

        // local endpoint of our Listener object, usually our machines ip address and a UDP port
        boost::asio::ip::udp::endpoint LocalEndpoint;

        // the connection objects managed by this Listener
        std::vector<std::shared_ptr<ConnectionT>> Connections;
    public:
        DefaultListenerEventDispatcher Callbacks;

        explicit Listener(
            const ListenerSettings& Settings,
            const boost::asio::ip::address& Address,
            const uint16_t Port = 13392
        ) : QuicListener(&Callbacks, Settings), LocalEndpoint(Address, Port) {};

        ~Listener() = default;


    };
}