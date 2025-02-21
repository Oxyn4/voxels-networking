/*
This file is part of the Voxels networking library.

the voxels networking library is free software: you can redistribute it and/or modify it under the terms of the
GNU General Public License as published by the Free Software Foundation, either version 3 of the License,
or (at your option) any later version. the Voxels networking library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details. You should have received a copy of the GNU General Public
License along with the voxels networking library. If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file quic.hpp
 * @brief Contains interface definitions for writing custom QUIC layers compatible with the voxels protocol layer.
 */

#pragma once

#include "endpoint.hpp"

#include "stream_dispatcher.hpp"
#include "listener_dispatcher.hpp"

#include "event_dispatcher.hpp"

/**
 * @namespace voxels::protocols::game::quic
 * @brief Contains interfaces that allows for implementing custom QUIC compatible layers
 * @details The voxels layer of the protocol relies on a common interface provided by the lower level quic layer. This namespace contains classes that make writing a quic layer compatible with the voxels layer simpler.
 */
namespace voxels::protocols::game::quic {
    /**
     * @class Stream quic.hpp Quic stream interface
     * @brief Interface representing a QUIC stream
     * @tparam EndpointType The Endpoint type either server and client
     */
    template<class RootMessageT, LocalEndpointType EndpointType = Client>
    class Stream;

    template<class RootMessageT>
    class Stream<RootMessageT, Client> {
        using StreamEventDispatcherT = EventDispatcher;
    protected:
        StreamEventDispatcherT* Dispatcher;

    public:
        explicit Stream(StreamEventDispatcherT* dispatcher) : Dispatcher(dispatcher) {}

        virtual ~Stream() = default;
    };

    template<class RootMessageT>
    class Stream<RootMessageT, Server> {
        using StreamEventDispatcherT = StreamEventDispatcher<RootMessageT>;
    protected:
        StreamEventDispatcherT* Dispatcher;

    public:
        explicit Stream(StreamEventDispatcherT* dispatcher) : Dispatcher(dispatcher) {}

        virtual ~Stream() = default;
    };

    template<LocalEndpointType EndpointType = Client>
    class Connection;

    template<>
    class Connection<Server> {
    protected:
        ConnectionEventDispatcher<Server>* Dispatcher;

    public:
        explicit Connection(ConnectionEventDispatcher<Server>* dispatcher) : Dispatcher(dispatcher) {}

        virtual ~Connection() = default;
    };

    template<>
    class Connection<Client> {
    protected:
        ConnectionEventDispatcher<Client>* Dispatcher;

    public:
        explicit Connection(ConnectionEventDispatcher<Client>* dispatcher) : Dispatcher(dispatcher) {}

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