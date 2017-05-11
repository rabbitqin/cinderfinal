#pragma once
#include "cinder/Perlin.h"
#include "cinder/Rand.h"
#include "cinder/app/RendererGl.h"
#include "poNodeContainer.h"
#include "cinder/gl/gl.h"
#include "poShape.h"
#include "cinder/Signals.h"
#include "poVideo.h"
#include "poTextBox.h"


class rolypoly;
typedef std::shared_ptr<rolypoly> rolypolyRef;
typedef ci::signals::Signal<void(int state)> ToggleStateChangeSignal;

class rolypoly
: public po::scene::NodeContainer{
public:
    
    static rolypolyRef create();
    ToggleStateChangeSignal& getToggleStateChangeSignal(){return mToggleStateChangeSignal;}
    
private:
    rolypoly();
    void setup();
    void update();
    void onMouseEvent(po::scene::MouseEvent &event);
    void goback(po::scene::MouseEvent &event);
    void trigger(po::scene::MouseEvent &event);
    
    ToggleStateChangeSignal mToggleStateChangeSignal;
    po::scene::VideoGlRef       mRoly;
    po::scene::ShapeRef     mHistory;
    po::scene::ShapeRef     info;
    po::scene::ShapeRef     buttom;
    
    po::scene::TextBoxRef mText;
    
    bool tri;
    
    ci::qtime::MovieGlRef movieRef1;
    ci::qtime::MovieGlRef movieRef2;
};

