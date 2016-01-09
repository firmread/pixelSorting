#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofImage fuckImageRows(ofImage input);
    ofImage fuckImageCols(ofImage input);
    void exportImage();
    string getOutFilename();
    
    
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
};
