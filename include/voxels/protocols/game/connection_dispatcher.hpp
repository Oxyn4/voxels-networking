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

#include "event_dispatcher.hpp"

#include "connection_events.hpp"
#include "connection_responses.hpp"

namespace voxels::protocols::game
{
    template<LocalEndpointType EndpointT = Client>
    class ConnectionEventDispatcher;

    template<>
    class ConnectionEventDispatcher<Server> : public EventDispatcher {
        using ControlStreamInitiatedEventT = events::ControlStreamInitiated<Server>;

    public:
        ConnectionEventDispatcher() = default;
        virtual ~ConnectionEventDispatcher() = default;

        virtual responses::ControlStreamInitiated operator()(const ControlStreamInitiatedEventT& Event) = 0;
    };

    template<>
    class ConnectionEventDispatcher<Client> : public EventDispatcher {
        using ControlStreamInitiatedEventT = events::ControlStreamInitiated<Client>;

    public:
        ConnectionEventDispatcher() = default;
        virtual ~ConnectionEventDispatcher() = default;

        virtual responses::ControlStreamInitiated operator()(const ControlStreamInitiatedEventT& Event) = 0;
    };

    template<LocalEndpointType EndpointT = Client>
    class DefaultConnectionEventDispatcher;

    template<>
    class DefaultConnectionEventDispatcher<Server> : public ConnectionEventDispatcher<Server> {
        using ControlStreamInitiatedEventT = events::ControlStreamInitiated<Server>;

    public:
        // the signals for events associated with a connection
        boost::signals2::signal<
          responses::ControlStreamInitiated(const ControlStreamInitiatedEventT&)
        > ControlStreamInitiated;

        responses::ControlStreamInitiated operator () (const ControlStreamInitiatedEventT& Event) override {
            return ControlStreamInitiated(Event).get();
        }
    };

    template<>
    class DefaultConnectionEventDispatcher<Client> : public ConnectionEventDispatcher<Client> {
        using ControlStreamInitiatedEventT = events::ControlStreamInitiated<Client>;

    public:
        // the signals for events associated with a connection
        boost::signals2::signal<
          responses::ControlStreamInitiated(const ControlStreamInitiatedEventT&)
        > ControlStreamInitiated;

        responses::ControlStreamInitiated operator () (const ControlStreamInitiatedEventT& Event) override {
            return ControlStreamInitiated(Event).get();
        }
    };

}