#include "ofApp.h"






void ofApp::setup()
{
	ofSetFrameRate(120);
	ofSetBackgroundColor(11);
	ofSetCircleResolution(25);
	//ofEnableAntiAliasing();
	//ofSetEscapeQuitsApp(false);
	//ofSetVerticalSync(true);
	//ofEnableSmoothing();
	ofDisableSmoothing();
	ofDisableAntiAliasing();
	
	
	//NBodySimulation.setup();
	NBodySimulation.config("Barnes-Hut Simulation", "0");
}




void ofApp::update()
{
	NBodySimulation.update();
}




void ofApp::draw()
{
	NBodySimulation.draw();
}




void ofApp::exit()
{
	NBodySimulation.exit();
}








void ofApp::keyPressed(int key)
{
	NBodySimulation.keyPressed(key);
}


void ofApp::keyReleased(int key)
{
	NBodySimulation.keyReleased(key);
}




void ofApp::mouseMoved(int x, int y )
{
	
}


void ofApp::mouseDragged(int x, int y, int button)
{
	NBodySimulation.mouseDragged(x,y,button);
}

void ofApp::mousePressed(int x, int y, int button)
{
	NBodySimulation.mousePressed(x,y,button);
}


void ofApp::mouseReleased(int x, int y, int button)
{
	NBodySimulation.mouseReleased(x,y,button);
}


void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY)
{
	NBodySimulation.mouseScrolled(x,y,scrollX, scrollY);
}


void ofApp::mouseEntered(int x, int y)
{
	
}


void ofApp::mouseExited(int x, int y)
{
	
}




void ofApp::windowResized(int w, int h)
{
	NBodySimulation.windowResized(w,h);
}





void ofApp::gotMessage(ofMessage msg)
{
	
}





void ofApp::dragEvent(ofDragInfo dragInfo)
{
	
}
