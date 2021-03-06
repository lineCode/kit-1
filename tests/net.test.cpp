#include <catch.hpp>
#include "../kit/net/net.h"
#include <string>
using namespace std;

TEST_CASE("Socket","[socket]") {
    SECTION("tcp server"){
        // TODO: initiate mock client with netcat
        // warn and stop if netcat does not exist
        
        //TCPSocket server;
        
        //REQUIRE(not server);
        //REQUIRE_NOTHROW(server.open());
        
        //REQUIRE_NOTHROW(server.bind(1337));
        //REQUIRE_NOTHROW(server.listen(10));
        
        //TCPSocket client;
        ////for(;;)
        ////{
        ////    try{
        //        client = server.accept();
        ////    }catch(...){
        ////        continue;
        ////    }
        ////    boost::this_thread::yield();
        ////}
        //REQUIRE(client);
        
        //client.send("hello world!");
        //const int SZ = 128;
        //uint8_t buf[SZ];
        //int sz = SZ;
        //while(not client.select()) {
        //    boost::this_thread::yield();
        //}
        //REQUIRE(client.select());
        //std::string msg;
        //REQUIRE_NOTHROW(msg = client.recv());
        //REQUIRE(msg == "hello world!");
        
        //REQUIRE_NOTHROW(client.close());
        //REQUIRE(not client);
        //REQUIRE_NOTHROW(server.close());
        //REQUIRE(not server);
        
        // TODO: kill mock client
    }
    SECTION("tcp client"){
        // TODO: initiate mock server process
        //TCPSocket s;
    }
    SECTION("udp server"){
        //UDPSocket s;
        //REQUIRE(not s);
        //REQUIRE_NOTHROW(s.open());
        //REQUIRE(s);
        ////REQUIRE(not s.select());
        //REQUIRE_NOTHROW(s.close());
        //REQUIRE(not s);
    }
    SECTION("udp client"){
    }
    SECTION("addresses"){
        Address addr;
        
        addr = Address("1.2.3.4:5");
        REQUIRE(addr.ip() == "1.2.3.4");
        REQUIRE(addr.port() == 5);
        REQUIRE(string(addr) == "1.2.3.4:5");
    }
}

