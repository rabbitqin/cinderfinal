#pragma once
#include "cinder/Perlin.h"
#include "cinder/Rand.h"
#include "cinder/app/RendererGl.h"
#include "poNodeContainer.h"
#include "cinder/gl/gl.h"
#include "poShape.h"
#include "cinder/Signals.h"
#include "cinder/ImageIo.h"
#include "poVideo.h"
#include "poTextBox.h"



class fireworks;
typedef std::shared_ptr<fireworks> fireworksRef;
typedef ci::signals::Signal<void(int state)> ToggleStateChangeSignal;

class fireworks
: public po::scene::NodeContainer{
public:

    static fireworksRef create();
    ToggleStateChangeSignal& getToggleStateChangeSignal(){return mToggleStateChangeSignal;}
    
private:
    fireworks();
    void setup();
    void update();
    void trigger(po::scene::MouseEvent &event);
    void trigger2(po::scene::MouseEvent &event);
    void fire(po::scene::MouseEvent &event);
        
    ci::TextBox ciTextBox1;
    ci::TextBox ciTextBox;
    ci::qtime::MovieGlRef movieRef1;
     ci::qtime::MovieGlRef movieRef2;
    
    po::scene::ShapeRef     mHistory;
    po::scene::ShapeRef     info;
    po::scene::ShapeRef     buttom;
    po::scene::VideoGlRef       mFire;
    bool tri;
    
    po::scene::TextBoxRef mText;
    
    
private:
    
    ToggleStateChangeSignal mToggleStateChangeSignal;
    };

