#include "headers.hpp"
#include <memory>


class Acceptor: std::enable_shared_from_this<Acceptor>{
private:
    net::io_context& context_;
    ip::tcp::acceptor acceptor_;

    void on_accept(beast::error_code ec, net::ip::tcp::socket socket){
        if(ec)
            return fail(ec, "accept");
        // else
        //     std::make_shared<HTTPSession>(std::move(socket))->run();

        acceptor_.async_accept(
            net::make_strand(context_),
            beast::bind_front_handler(
                &Acceptor::on_accept,
                shared_from_this())
            );
    }
    void fail(beast::error_code ec, char const* what){
        if(ec == net::error::operation_aborted){
            return;
        }
        std::cerr << what <<  ec.message() << std::endl;
    }
public:
    Acceptor(net::io_context& context, net::ip::tcp::endpoint endpoint) : context_(context), acceptor_(context){
        beast::error_code ec;

        acceptor_.open(endpoint.protocol(), ec);
        if(ec){
            fail(ec, "open");
            return;
        }

        acceptor_.set_option(net::socket_base::reuse_address(true), ec);
        if(ec){
            fail(ec, "set_option");
            return;
        }

        acceptor_.listen(net::socket_base::max_listen_connections, ec);
        if(ec){
            fail(ec, "listen");
            return;
        }
    }

    // will start excepting new connections
    void start(){
        acceptor_.async_accept(
            net::make_strand(context_),
            beast::bind_front_handler(
                &Acceptor::on_accept,
                shared_from_this())

            );
    }
};