#pragma once

#include "ofMain.h"
#include "ofxSpout2Sender.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	int xStep;
	int yStep;

	float amp;
	bool color;

	int threshold;

	ofPixels pixels;
	ofColor lineColor;
	ofColor fillColor;

	ofVideoPlayer videoPlayer;
	ofVideoGrabber webcam;
	ofFbo fbo;
	ofFbo shaderfbo;
	unsigned int source;
	int stepWidthTexture;
	int stepHeightTexture;

	ofTrueTypeFont font;
	bool drawText;
	ofShader shader;

	ofxSpout2::Sender spout;
	int textureToSend;
};
