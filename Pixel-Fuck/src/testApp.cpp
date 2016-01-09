#include "testApp.h"

ofImage inputImg;
ofPixels outputImg;
ofTexture texture;

int NUM_MODES = 6;
int BRIGHTNESS_MODE = 0;
int SATURATION_MODE = 1;
int LIGHTNESS_MODE = 2;
int RED_MODE = 3;
int GREEN_MODE = 4;
int BLUE_MODE = 5;
int curMode = RED_MODE;
bool FUCKROWS = true;

string inFilename = "nn-red-reed.jpg";
//string inFilename = "mountain.jpg";


//--------------------------------------------------------------
void testApp::setup(){
    inputImg.loadImage(inFilename);
    float imgRescale = 0.6;
    inputImg.resize(inputImg.getWidth()*imgRescale,inputImg.getHeight()*imgRescale);
    ofSetWindowShape(inputImg.getWidth()*imgRescale, inputImg.getHeight()*imgRescale);
}

//--------------------------------------------------------------
void testApp::update(){
    ofImage out;
    if(FUCKROWS) {
        out = fuckImageRows(inputImg);
    } else {
        out = fuckImageCols(inputImg);
    }
    texture.loadData(out);
}

//--------------------------------------------------------------
void testApp::draw(){
    texture.draw(0,0);
}
//--------------------------------------------------------------

bool compareBrightness(ofColor a, ofColor b) {
    return a.getBrightness() > b.getBrightness();;
}

//--------------------------------------------------------------

bool compareLightness(ofColor a, ofColor b) {
    return a.getLightness() > b.getLightness();
}

//--------------------------------------------------------------


bool compareSaturation(ofColor a, ofColor b) {
    return a.getSaturation() > b.getSaturation();
}

//--------------------------------------------------------------

bool compareRedness(ofColor a, ofColor b) {
    return a.r > b.r;
}

//--------------------------------------------------------------

bool compareBlueness(ofColor a, ofColor b) {
    return a.b > b.b;
}

//--------------------------------------------------------------

bool compareGreeness(ofColor a, ofColor b) {
    return a.g > b.g;
}

//--------------------------------------------------------------

//for each row in input image, sort pixel brightness ascending, put row in output image
ofImage testApp::fuckImageRows(ofImage input) {
    ofImage out;
    out.allocate(input.getWidth(), input.getHeight(),OF_IMAGE_COLOR);
    out.setColor(255);
    vector<ofColor> line;
    
    for(int y=0; y<input.getHeight(); y++) {
        for(int x=0; x<input.getWidth(); x++){
            line.push_back(input.getColor(x, y));
        }
        
        if(curMode == BRIGHTNESS_MODE) {
            ofSort(line,compareBrightness);
        } else if(curMode == LIGHTNESS_MODE) {
            ofSort(line,compareLightness);
        } else if(curMode == SATURATION_MODE) {
            ofSort(line,compareSaturation);
        } else if(curMode == RED_MODE) {
            ofSort(line,compareRedness);
        } else if(curMode == BLUE_MODE) {
            ofSort(line,compareBlueness);
        } else if(curMode == GREEN_MODE) {
            ofSort(line,compareGreeness);
        }

        for(int x=0; x<input.getWidth(); x++) {
            out.setColor(x, y, line[x]);
        }
        line.clear();
    }

    return out;
}

//--------------------------------------------------------------

ofImage testApp::fuckImageCols(ofImage input) {
    ofImage out;
    out.allocate(input.getWidth(), input.getHeight(),OF_IMAGE_COLOR);
    vector<ofColor> line;
    
    for(int x=0; x<input.getWidth(); x++){
        for(int y=0; y<input.getHeight(); y++) {
            line.push_back(input.getColor(x, y));
        }
        
        if(curMode == BRIGHTNESS_MODE) {
            ofSort(line,compareBrightness);
        } else if(curMode == LIGHTNESS_MODE) {
            ofSort(line,compareLightness);
        } else if(curMode == SATURATION_MODE) {
            ofSort(line,compareSaturation);
        } else if(curMode == RED_MODE) {
            ofSort(line,compareRedness);
        }
        
        for(int y=0; y<input.getHeight(); y++) {
            out.setColor(x, y, line[y]);
        }
        line.clear();
    }
    return out;
}

//--------------------------------------------------------------
void testApp::exportImage(){
    
    ofImage in, out;
    in.loadImage(inFilename);
    string outFilename = getOutFilename();
    
    if(FUCKROWS) {
        out = fuckImageRows(in);
    } else {
        out = fuckImageCols(in);
    }
    cout << "Exporting image " << outFilename << " with width: " << out.getWidth() << ", height: " << out.getHeight() << " :::: input width: " << in.getWidth() << ", height: " << in.getHeight() << endl;
    
    out.saveImage(outFilename);
}

//--------------------------------------------------------------

string testApp::getOutFilename() {
    string fileBase = "out";
    int suffix = 0;
    bool foundUnique = false;
    ofFile f;
    string s;
    
    while (!foundUnique) {
        s = fileBase + ofToString(suffix) + ".png";
        if(f.doesFileExist(s)) {
            suffix++;
            cout << "file " << s << " exists. Trying suffix " << suffix << endl;
        } else {
            cout << "file " << s << " does not exist. Writing."  << endl;
            foundUnique = true;
        }
    }
    return s;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key == '.') {
        curMode = (curMode+1)%NUM_MODES;
        cout << "curMode is " << curMode << endl;
    }

    if(key == ',') {
        curMode = (curMode-1)%NUM_MODES;
                cout << "curMode is " << curMode << endl;
    }
    
    if(key == '>') {
        FUCKROWS = !FUCKROWS;
    }
    
    if(key == '<') {
        FUCKROWS = !FUCKROWS;
    }
    
    if(key == 'e') {
        exportImage();
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}