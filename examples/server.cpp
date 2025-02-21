
#include <voxels/protocols/game/protocol.hpp>

using namespace voxels::protocols::game;


responses::ServerIdentity IdentityReceivedHandler(const events::ClientIdentityReceived& Event) {
    std::unique_ptr<int> Data(new int(42));

    responses::ServerIdentity Response(Data);

    return Response;
}

responses::ControlStreamInitiated ControlStreamInitiatedHandler(const events::ControlStreamInitiated<Server>& Event) {
    const std::shared_ptr<ControlStream<Server>> ControlStream = Event.ControlStream_.lock();

    ControlStream->Callbacks.IdentityReceivedSignal.connect(IdentityReceivedHandler);

    return {};
}

responses::NewConnection NewConnectionHandler(const events::NewConnectionEvent& Event) {
    const std::shared_ptr<Connection<Server>> Connection_ = Event.Connection_.lock();

    Connection_->Callbacks.ControlStreamInitiated.connect(ControlStreamInitiatedHandler);

    return {};
}

int main() {
    const ListenerSettings Settings;

    Listener Listener_(Settings, boost::asio::ip::make_address("127.0.0.1"));

    Listener_.Callbacks.NewConnection.connect(NewConnectionHandler);

    return 0;
}