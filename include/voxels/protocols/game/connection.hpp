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

#include <boost/asio.hpp>

#include "connection_dispatcher.hpp"

namespace voxels::protocols::game {
    template<LocalEndpointType EndpointType = Client>
    class ConnectionSettings;

    template<>
    class ConnectionSettings<Client> {

    };

    template<>
    class ConnectionSettings<Server> {

    };

    template<LocalEndpointType EndpointT>
    class Connection;

    template<>
    class Connection<Server> final : public EventDispatcher {
        using ControlStreamInitiatedEventT = events::ControlStreamInitiated<Server>;

    public:
        boost::asio::ip::udp::endpoint RemoteEndpoint;

        DefaultConnectionEventDispatcher<Server> Callbacks;

    };

    template<>
    class Connection<Client> final : public EventDispatcher {
    public:
        boost::asio::ip::udp::endpoint RemoteEndpoint;

        DefaultConnectionEventDispatcher<Client> Callbacks;

    };
}
