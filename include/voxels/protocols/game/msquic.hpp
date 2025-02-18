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

#include "quic.hpp"

// singleton class that manages a unique ptr to msquic API table
class Msquic {
private:
  std::unique_ptr<const QUIC_API_TABLE> API;

  Msquic() {
    const QUIC_API_TABLE* RawAPI = nullptr;

    uint Status = MsQuicOpen2(&RawAPI);

    API = std::make_unique<const QUIC_API_TABLE>(*RawAPI);
  };
  Msquic(const Msquic&);
  Msquic& operator=(const Msquic&);
  ~Msquic() = default;

public:

  Msquic(Msquic&) = delete;
  void operator=(Msquic&) = delete;

  static Msquic& Get() {
    static Msquic Instance;

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

namespace voxels::protocols::game::msquic {
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

    template<class EventDispatcherT>
    class Listener final : quic::Listener<EventDispatcherT> {
    private:
        HQUIC Handle;
        HQUIC Configuration;
        HQUIC Registration;

        QUIC_SETTINGS QuicSettings = {0};
    public:
        // constructors
        explicit Listener(EventDispatcherT* ContextPointer_, const ListenerSettings& Settings) : quic::Listener<EventDispatcherT>(ContextPointer_), QuicSettings(Settings) {}

        void Setup() const {
            QUIC_BUFFER Alpn = {
                sizeof("voxels") - 1,
                reinterpret_cast<uint8_t*>("voxels")
            };

            uint Status = Msquic::Get()->ConfigurationOpen(
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