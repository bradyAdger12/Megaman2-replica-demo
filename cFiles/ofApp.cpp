#include "ofApp.h"  
#include "object.h"
shared_ptr<ofxBox2dRect> rectangle;  
shared_ptr<ofxBox2dCircle> circle; 
object rect;

//--------------------------------------------------------------
void ofApp::setup(){

	//world setup
	world.init(); 
	world.setFPS(60.0);    
	
	//setup objects
	int diff = 0;
	for (int i = 0; i < 10; i++) {
		object *ob = new object();
		circle = ob->Circle(100 + diff, 100 + diff, 10, 4.0, .5, 0); 
		circles.push_back(circle);
		diff++;
	}  
	rectangle = rect.Rectangle(0, ofGetHeight() - 20, ofGetWidth(), 20, 0 , 0, 2);  
}

//--------------------------------------------------------------
void ofApp::update(){
	world.update();
	for (int i = 0; i < circles.size(); i++) { 
		circles[i].get()->update();
	}
	rectangle.get()->enableGravity(false);
}

//--------------------------------------------------------------
void ofApp::draw(){	 

	//draw world 
	world.draw();  

	//draw circle 
	ofSetColor(0);
	for (int i = 0; i < circles.size(); i++) {
		circles[i].get()->draw();
	}
	ofSetColor(0);
	rectangle.get()->draw();

	  
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){ 
	if (key == 'f') {
		cout << world.getBodyCount() << endl;
		circle.get()->destroy();
		rectangle.get()->destroy();
		cout << world.getBodyCount() << endl;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
