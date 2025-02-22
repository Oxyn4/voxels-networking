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

#include "response.hpp"

namespace voxels::protocols::game {
 template<class RootMessageT, LocalEndpointType EndpointT>
 class Stream;
}

namespace voxels::protocols::game::responses {
 template<LocalEndpointType EndpointT = Client>
 class StreamResponse : public Response<EndpointT> {};

 template<class ReplyT, LocalEndpointType EndpointType = Client>
 class Reply : public StreamResponse<EndpointType> {
 public:
  std::unique_ptr<ReplyT> Data;

  const ReplyT& operator*() const {
   return *Data;
  }

  const ReplyT* operator->() const {
   return Data.get();
  }

  const ReplyT& operator*() {
   return *Data;
  }

  const ReplyT* operator->() {
   return Data.get();
  }

  explicit Reply(std::unique_ptr<ReplyT>&& Data) : Data(std::move(Data)) {}
 };
}