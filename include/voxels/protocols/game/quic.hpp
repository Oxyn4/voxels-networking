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

#include "endpoint.hpp"

#include "listener_dispatcher.hpp"

#include "event_dispatcher.hpp"

namespace voxels::protocols::game::quic {
    template<LocalEndpointType EndpointType = Client>
    class Stream;

    template<>
    class Stream<Client> {
    protected:
        StreamEventDispatcher* Dispatcher;

    public:
        explicit Stream(StreamEventDispatcher* dispatcher) : Dispatcher(dispatcher) {}

        virtual ~Stream() = default;
    };

    template<>
    class Stream<Server> {
    protected:
        StreamEventDispatcher* Dispatcher;

    public:
        explicit Stream(StreamEventDispatcher* dispatcher) : Dispatcher(dispatcher) {}

        virtual ~Stream() = default;
    };

    template<LocalEndpointType EndpointType = Client>
    class Connection;

    template<>
    class Connection<Server> {
    protected:
        ConnectionEventDispatcher* Dispatcher;

    public:
        explicit Connection(ConnectionEventDispatcher* dispatcher) : Dispatcher(dispatcher) {}

        virtual ~Connection() = default;
    };

    template<>
    class Connection<Client> {
    protected:
        ConnectionEventDispatcher* Dispatcher;

    public:
        explicit Connection(ConnectionEventDispatcher* dispatcher) : Dispatcher(dispatcher) {}

        virtual ~Connection() = default;
    };

    class Listener {
    protected:
        ListenerEventDispatcher* Dispatcher;

    public:
        explicit Listener(ListenerEventDispatcher* dispatcher) : Dispatcher(dispatcher) {}

        virtual ~Listener() = default;
    };

}