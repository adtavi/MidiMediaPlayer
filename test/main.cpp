//
//  main.cpp
//  TestMidiMediaPlayer
//
//  Created by Adriel Taboada on 01/08/2020.
//
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "ofxUnitTests.h"

TEST_CASE( "Testing", "[main]" ) {
    REQUIRE( true );
}

class TestApp: public ofxUnitTestsApp {
    void run(){
    }
};

int main( int argc, char* argv[] ) {
    // Initialising a mock app is mandatory, otherwise graphic functions throw errors
    ofInit();
    auto window = make_shared<ofAppNoWindow>();
    auto app = make_shared<TestApp>();
    ofRunApp(window, app);
    
    // Let's do the actual testing
    int result = Catch::Session().run( argc, argv );
    
    ofRunMainLoop();
    
    return result;
}
