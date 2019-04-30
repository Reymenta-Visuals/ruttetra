#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofEnableAlphaBlending();

	textureToSend = 0;
	bool init = webcam.initGrabber(1280, 720);

	ofSetWindowTitle("RuttEtra");

	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	fbo.begin();
	ofClear(0);
	fbo.end();

	shaderfbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	shaderfbo.begin();
	ofClear(0);
	shaderfbo.end();
	drawText = false;

	//tweakable shizz
	xStep = 204;
	yStep = 153;

	amp = 0.4;
	threshold = 50;


	//white on black
	lineColor = ofColor(255, 255, 255, 150);
	fillColor = ofColor(0, 0, 0, 255);

	//black on white
	//lineColor = ofColor(0, 0, 0, 255);
	//fillColor = ofColor(255, 255, 255, 255);

	//assign pixel colour to line segments
	color = true;

	// text
	font.load("type/verdana.ttf", 100, true, false, true, 0.4, 72);
	// shader
#ifdef TARGET_OPENGLES
	shader.load("shaders_gles/noise.vert", "shaders_gles/noise.frag");
#else
	if (ofIsGLProgrammableRenderer()) {
		shader.load("shaders_gl3/noise.vert", "shaders_gl3/noise.frag");
	}
	else {
		shader.load("shaders/noise.vert", "shaders/noise.frag");
	}
#endif
}

//--------------------------------------------------------------
void ofApp::update() {

		webcam.update();
		pixels = webcam.getPixelsRef();
}

//--------------------------------------------------------------
void ofApp::draw() {
	int stepWidth = ofGetWidth() / xStep;
	int stepHeight = ofGetHeight() / yStep;

		stepWidthTexture = webcam.getWidth() / xStep;
		stepHeightTexture = webcam.getHeight() / yStep;
		
	// draw to fbo begin
	fbo.begin();
	ofClear(fillColor);
	ofSetColor(lineColor);
	ofSetLineWidth(3);

	int cY = 0;
	
	for (cY = 0; cY < yStep; cY++)
	{

		ofPoint lastpoint;
		ofColor currentColor;

		for (int i = 1; i < xStep; i++)
		{

			currentColor = pixels.getColor(i * stepWidthTexture, cY * stepHeightTexture);
			ofPoint thisPoint(i * stepWidth, cY * stepHeight - currentColor.getBrightness() * amp + stepHeight);

			if (currentColor.getBrightness() >= threshold)
			{
				//apply pixel colour to line segement.
			if (color)
				{
					currentColor = ofColor(currentColor[0], currentColor[1], currentColor[2], 200);
					ofSetColor(currentColor);
				}
				else
				{
					//adjust alpha of line segement according to brightness of pixel
					ofSetColor(lineColor.r, lineColor.g, lineColor.b, ofMap(currentColor.getBrightness(), threshold, 255, 0, 255));
				}

				if (i == 1)
				{
					lastpoint = thisPoint;
				}

				ofLine(lastpoint[0], lastpoint[1], thisPoint[0], thisPoint[1]);

			}
			lastpoint = thisPoint;
		}
	}
	
	fbo.end();
	// draw to fbo end

	// fbo for shader begin
	shaderfbo.begin();

	//Shader ready to do any post required.
	shader.begin();
	ofSetColor(255);
	ofFill();
	shader.setUniformTexture( "tex0", fbo.getTextureReference(), 0 );
	//we want to pass in some varrying values to animate our type / color 
	shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1);
	shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18);

	//we also pass in the mouse position 
	//we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped. 
	shader.setUniform2f("mouse", mouseX - ofGetWidth() / 2, ofGetHeight() / 2 - mouseY);
	//fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
	if (drawText) font.drawStringAsShapes("Artist de ouf", 90, 260);
	shader.end();

	shaderfbo.end();
	// fbo for shader end

	//webcam.draw(500, 20);
	// send screen to Spout
	switch (textureToSend) {
	case 0:
		spout.sendTexture(fbo.getTexture(), "RuttEtra");
		break;
	case 1:
		spout.sendTexture(shaderfbo.getTexture(), "RuttEtra");
		break;
	case 2:
		spout.sendTexture(webcam.getTexture(), "RuttEtra");
		break;
	default:
		break;
	}
	
}
void ofApp::exit() {
	spout.exit();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case 'f':
		ofToggleFullscreen();
		break;
	case 't':
		drawText = !drawText;
		break;
	case '0':
		textureToSend = 0;
		break;
	case '2':
		textureToSend = 1;
		break;
	case '3':
		textureToSend = 2;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
