#include <catch.hpp>
#include "../include/kit/args/args.h"
#include "../include/kit/log/log.h"
using namespace std;

TEST_CASE("Args","[args]") {

    SECTION("empty") {
        Args args;
        REQUIRE(args.empty());
        REQUIRE(args.size() == 0);
    }
    
    SECTION("has") {
        // empty
        Args args;
        REQUIRE(not args.has("foobar"));
        
        // single arg
        args = Args(vector<string>{"foobar"});
        REQUIRE(args.has("foobar"));
        REQUIRE(not args.has("foo"));
        
        // multiple args
        args = Args(vector<string>{"foo", "bar"});
        REQUIRE(args.has("foo"));
        REQUIRE(args.has("bar"));
        REQUIRE(not args.has("baz"));

        // switches
        args = Args();
        REQUIRE(not args.has('v', "verbose"));
        args = Args(vector<string>{"--verbose"});
        REQUIRE(args.has('v', "verbose"));
        REQUIRE(not args.has('n', "nope"));
        args = Args(vector<string>{"-v"});

        // multiple char switches
        args = Args(vector<string>{"-abc"}, "-a -b -c");
        REQUIRE(args.has('a', "achar"));
        REQUIRE(args.has('b', "bchar"));
        REQUIRE(args.has('c', "cchar"));
        args = Args(vector<string>{"-ac"}, "-a -b -c");
        REQUIRE(args.has('a', "achar"));
        REQUIRE(not args.has('b', "bchar"));
        REQUIRE(args.has('c', "cchar"));
    }
    
    SECTION("schemas") {
        Args args;
        
        REQUIRE_NOTHROW(args = Args(vector<string>{"--foo"}, "-f --foo"));
        REQUIRE(args.has('f',"foo"));
        REQUIRE(args.has("--foo"));
        REQUIRE(not args.has("-f"));
        
        REQUIRE_NOTHROW(args = Args(vector<string>{"-f"}, "-f --foo"));
        REQUIRE(args.has('f',"foo"));
        REQUIRE(not args.has("--foo"));
        REQUIRE(args.has("-f"));
        
        {
            Log::Silencer ls;
            REQUIRE_THROWS(args = Args(vector<string>{"--invalid"}, "-f --foo"));
        }
        
        REQUIRE_NOTHROW(Args(vector<string>{"-ab"}, "-a -b"));
        {
            Log::Silencer ls;
            // -c invalid
            REQUIRE_THROWS(Args(vector<string>{"-abc"}, "-a -b"));
        }

    }
}

