#include "ofMain.h"
#include "App.h"

//========================================================================
int main(int argc,char* argv[] ){
    ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
    
    // Search for a path inbetween the arguments
    if (std::filesystem::is_directory(argv[1])) {
        MidiSettings::set_data_path(argv[1]);
    }
        
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new App());
    
}
