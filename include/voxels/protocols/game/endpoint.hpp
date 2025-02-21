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
 * @file endpoint.hpp
 * @brief Contains the definition of the LocalEndpointType concept
 */

#pragma once

namespace voxels::protocols::game {
    /**
     * @class Server endpoint.hpp
     * @brief A tag type used as a template parameter to many of the library types to indicate usage of a specialised overload meant for voxels server endpoints.
     */
    struct Server;

    /**
     * @class Client endpoint.hpp
     * @brief A tag type used as a template parameter to many of the library types to indicate usage of a specialised overload meant for voxels client endpoints.
     */
    struct Client;

    /**
     * @concept LocalEndpointType
     * @brief A concept used to check a type is either Server or Client, allowing for specialised overloaded based on a template parameter constrained by this concept.
     */
    template<typename EndpointType>
    concept LocalEndpointType = std::is_same_v<EndpointType, Client> || std::is_same_v<EndpointType, Server>;
}