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

#include "control_steam.hpp"

namespace voxels::protocols::game {
    template<LocalEndpointType EndpointType = Client>
    class Connection;
}

namespace voxels::protocols::game::responses {
    struct ControlStreamResponse;

    class ControlStreamInitiated final : public ControlStreamResponse {

    };
}

namespace voxels::protocols::game::events {
    template<LocalEndpointType EndpointT = Client>
    class ConnectionEvent {
        using ConnectionT = Connection<EndpointT>;

    public:
        std::weak_ptr<ConnectionT> Connection_;

        explicit ConnectionEvent(const std::weak_ptr<ConnectionT>& Connection_) : Connection_(Connection_) {};
    };

    template<LocalEndpointType EndpointT = Client>
    class ControlStreamInitiated final : public ConnectionEvent<EndpointT> {
        using ControlStreamT = ControlStream<EndpointT> ;
        using ConnectionT = Connection<EndpointT>;

    public:
        std::weak_ptr<ControlStreamT> ControlStream_;

        ControlStreamInitiated(const std::weak_ptr<ConnectionT> &Connection_, const std::weak_ptr<ControlStreamT> &ControlStream_)
            : ConnectionEvent<EndpointT>(Connection_), ControlStream_{ControlStream_} {};
    };
}

namespace voxels::protocols::game {
    template<LocalEndpointType EndpointT>
    class Connection;

    template<>
    class Connection<Server> final : public EventDispatcher {
        using ControlStreamInitiatedEventT = events::ControlStreamInitiated<Server>;

    public:
        boost::asio::ip::udp::endpoint RemoteEndpoint;

        // the signals for events associated with a connection
        boost::signals2::signal<
          responses::ControlStreamInitiated(const ControlStreamInitiatedEventT&)
        > ControlStreamInitiatedSignal;
    };

    template<>
    class Connection<Client> final : public EventDispatcher {
        using ControlStreamInitiatedEventT = events::ControlStreamInitiated<Client>;

    public:
        boost::asio::ip::udp::endpoint RemoteEndpoint;

        // the signals for events associated with a connection
        boost::signals2::signal<
          responses::ControlStreamInitiated(const ControlStreamInitiatedEventT&)
        > ControlStreamInitiatedSignal;
    };
}
