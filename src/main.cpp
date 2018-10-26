#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetLogLevel(OF_LOG_VERBOSE);
	int windowWidth = 1280;
	int windowHeight = 720;

#ifdef TARGET_OPENGLES
	ofGLESWindowSettings settings;
	settings.width = windowWidth;
	settings.height = windowHeight;
	settings.setGLESVersion(2);
	ofCreateWindow(settings);
#else
	ofSetupOpenGL(windowWidth, windowHeight, OF_WINDOW);
#endif
	ofRunApp(new ofApp());

}
