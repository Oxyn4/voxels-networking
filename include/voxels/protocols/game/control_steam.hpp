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


#include "control_stream_events.hpp"
#include "control_stream_responses.hpp"

#include <boost/signals2.hpp>

#include "stream.hpp"

#include <voxels/protocols/game/schema/protocol_raw_types.hpp>

namespace voxels::protocols::game {
    template<LocalEndpointType EndpointType>
    class ControlStream;

    // specialisation for server

    template<>
    class ControlStream<Server> : public Stream<Server> {
        // specialization of response and event types
        using IdentityResponseT = responses::Identity<Server>;
        using IdentityReceivedEventT = events::IdentityReceived<Client>;
        using IdentitySentT = events::IdentitySent<Server>;
    private:

    public:
        boost::signals2::signal<
            IdentityResponseT(const IdentityReceivedEventT&)
        > IdentityReceivedSignal;

        boost::signals2::signal<
            void(const IdentitySentT&)
        > IdentitySentSignal;
    };

    // specialisation for client


    template<>
    class ControlStream<Client> : public Stream<Client> {
        // specialization of response and event types
        using IdentityResponseT = responses::Identity<Client>;
        using IdentityReceivedEventT = events::IdentityReceived<Server>;
        using IdentitySentT = events::IdentitySent<Client>;
    private:

    public:
        boost::signals2::signal<
            IdentityResponseT(const IdentityReceivedEventT&)
        > IdentityReceivedSignal;

        boost::signals2::signal<
            void(const IdentitySentT&)
        > IdentitySentSignal;
    };
}