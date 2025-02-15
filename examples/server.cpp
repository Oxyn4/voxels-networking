
#include <voxels/protocols/game/protocol.hpp>

using namespace voxels::protocols::game;


responses::Identity<Server> IdentityReceivedHandler(const events::IdentityReceived<Client>& Event) {
    std::unique_ptr<int> Data(new int(42));

    responses::Identity<Server> Response(Data);

    return Response;
}

responses::ControlStreamInitiated ControlStreamInitiatedHandler(const events::ControlStreamInitiated<Server>& Event) {
    const std::shared_ptr<ControlStream<Server>> ControlStream = Event.ControlStream_.lock();

    ControlStream->IdentityReceivedSignal.connect(IdentityReceivedHandler);

    return {};
}

responses::NewConnection NewConnectionHandler(const events::NewConnectionEvent& Event) {
    const std::shared_ptr<Connection<Server>> Connection_ = Event.Connection_.lock();

    Connection_->ControlStreamInitiatedSignal.connect(ControlStreamInitiatedHandler);

    return {};
}

int main() {
    Listener Listener_(boost::asio::ip::make_address("127.0.0.1"));

    Listener_.NewConnectionSignal.connect(NewConnectionHandler);

    return 0;
}