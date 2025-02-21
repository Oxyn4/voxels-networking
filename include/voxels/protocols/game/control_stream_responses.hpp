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

#include "stream_responses.hpp"

namespace voxels::protocols::game::responses {
 struct ControlStreamResponse {};

 template<LocalEndpointType EndpointT = Client>
 struct Identity {};

 using IdentityDataT = int;

 template<>
 struct Identity<Client> : ControlStreamResponse, Reply<IdentityDataT> {
  using Reply::operator*;
  using Reply::operator->;

  explicit Identity(std::unique_ptr<IdentityDataT>& Data) : Reply(std::move(Data)) {}
 };

 using ClientIdentity = Identity<Client>;

 template<>
 struct Identity<Server> : ControlStreamResponse, Reply<IdentityDataT, Server> {
  using Reply::operator*;
  using Reply::operator->;

  explicit Identity(std::unique_ptr<IdentityDataT>& Data) : Reply(std::move(Data)) {}
 };

 using ServerIdentity = Identity<Server>;
}