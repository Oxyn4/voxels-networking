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

#include "msquic.h"

#include <memory>

// singleton class that manages a unique ptr to msquic API table
class msquic {
private:
  std::unique_ptr<const QUIC_API_TABLE> API;

  msquic() {
    const QUIC_API_TABLE* RawAPI = nullptr;

    uint Status = MsQuicOpen2(&RawAPI);

    API = std::make_unique<const QUIC_API_TABLE>(*RawAPI);
  };
  msquic(const msquic&);
  msquic& operator=(const msquic&);
  ~msquic() = default;

public:

  msquic(msquic&) = delete;
  void operator=(msquic&) = delete;

  static msquic& Get() {
    static msquic Instance;

    return Instance;
  };

  // pointer semantics
  const QUIC_API_TABLE& operator*() const {
      return *API;
  }

  const QUIC_API_TABLE* operator->() const {
    return API.get();
  }

  const QUIC_API_TABLE& operator*() {
    return *API;
  }

  const QUIC_API_TABLE* operator->() {
      return API.get();
  }
};