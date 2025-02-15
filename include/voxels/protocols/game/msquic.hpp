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

#include "listener.hpp"
#include "listener.hpp"
#include "listener.hpp"
#include "listener.hpp"

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

namespace voxels::protocols::game::quic {
    struct CredentialSettings final {};

    struct Credentials final {
        CredentialSettings Settings;
    };

    struct ListenerSettings final {
        std::chrono::milliseconds Timeout;

        ListenerSettings()
            : Timeout(std::chrono::milliseconds(5000)) {};

        // ReSharper disable once CppNonExplicitConversionOperator
        operator QUIC_SETTINGS () const {
            QUIC_SETTINGS New = {0};

            New.IdleTimeoutMs = Timeout.count();
            New.IsSet.IdleTimeoutMs = true;

            return New;
        }
    };

    template<class ContextT>
    class Listener {
    private:
        HQUIC Handle;
        HQUIC Configuration;
        HQUIC Registration;

        QUIC_SETTINGS QuicSettings = {0};

        ContextT* ContextPointer;
    public:
        // constructors
        explicit Listener(ContextT* ContextPointer_, const ListenerSettings& Settings) : QuicSettings(Settings), ContextPointer(ContextPointer_) {}

        void Setup() const {
            QUIC_BUFFER Alpn = {
                sizeof("voxels") - 1,
                reinterpret_cast<uint8_t*>("voxels")
            };

            uint Status = msquic::Get()->ConfigurationOpen(
                Registration,
                // used in application layer protocol negotiation
                &Alpn,
                // the amount of application layer protocol negotiation buffers
                1,
                &QuicSettings,
                sizeof(QuicSettings),
                nullptr,
                &Configuration
            );
        }

        void Open() const {}

        void Start() const {}

        // A C compatible callback function to be passed to msquic
        static QUIC_STATUS EventForwarder(HQUIC Handle, Listener* Context, QUIC_LISTENER_EVENT* Event) {

            return QUIC_STATUS_SUCCESS;
        }
    };
}