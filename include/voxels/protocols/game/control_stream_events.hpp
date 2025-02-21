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

#include "stream_events.hpp"

namespace voxels::protocols::game {
    template<LocalEndpointType EndpointType = Client>
    class ControlStream;
}


namespace voxels::protocols::game::events {
 template<LocalEndpointType EndpointT = Client>
 struct ControlStreamEvent {
  using ControlStreamT = ControlStream<EndpointT>;

  std::weak_ptr<ControlStreamT> ControlStream_;
 };

 template<LocalEndpointType EndpointT = Client>
 struct IdentityReceived;

 template<>
 struct IdentityReceived<Client> : ControlStreamEvent<Client>, Received<int, Client> {
  using Received::operator*;
  using Received::operator->;
 };

 template<>
 struct IdentityReceived<Server> : ControlStreamEvent<Server>, Received<std::string, Server> {
  using Received::operator*;
  using Received::operator->;
 };


 template<LocalEndpointType EndpointT = Client>
 struct IdentitySent;

 template<>
 struct IdentitySent<Client> : ControlStreamEvent<Client>, Sent<int, Client> {
  using Sent::operator*;
  using Sent::operator->;
 };

 template<>
 struct IdentitySent<Server> : ControlStreamEvent<Server>, Sent<std::string, Server> {
  using Sent::operator*;
  using Sent::operator->;
 };

 using ServerIdentitySent = IdentitySent<Server>;
 using ServerIdentityReceived = IdentitySent<Server>;

 using ClientIdentitySent = IdentitySent<Client>;
 using ClientIdentityReceived = IdentityReceived<Client>;


}
