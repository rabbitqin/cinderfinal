#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "poScene.h"
#include "poNodeContainer.h"
#include "poShape.h"
#include "poVideo.h"
#include "video.hpp"
#include "toy1.hpp"
#include "sparkle.hpp"
#include "transition.hpp"
#include "toy2.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class finalApp : public App {
public:
    void setup() override;
    
    void update() override;
    void draw() override;
    void onStateChange(int state);
    
    po::scene::SceneRef mScene;
    
    po::scene::NodeContainerRef  mNodeContainerA;
    po::scene::NodeContainerRef  mNodeContainerC;
    po::scene::NodeContainerRef  mNodeContainerD;
    po::scene::NodeContainerRef  mContainer;
    
    int mCurrentState;
    
    VideoSampleRef video;
    fireworksRef toy1;
    TransitionRef Trans;
    rolypolyRef toy2;

    
     bool fireworks;
};

void finalApp::setup()
{
    setWindowSize( 1280,800 );
    
    mCurrentState = 1;
 
    fireworks = false;
    
    setFullScreen(true);
    
    mContainer = po::scene::NodeContainer::create();
    
    mScene = po::scene::Scene::create(mContainer);
    
    mNodeContainerA = po::scene::NodeContainer::create();
    mNodeContainerC = po::scene::NodeContainer::create();
     mNodeContainerD = po::scene::NodeContainer::create();
    

    
    mContainer->addChild(mNodeContainerA);
    mContainer->addChild(mNodeContainerC);
    mContainer->addChild(mNodeContainerD);
    
    video = VideoSample::create();
    
    video->setDrawBounds(false);
    video->getToggleStateChangeSignal().connect(std::bind(&finalApp::onStateChange, this, std::placeholders::_1));
    mNodeContainerA->addChild(video);
    
    mNodeContainerC->setAlpha(0.f);
    mNodeContainerA->setAlpha(1.f);
    mNodeContainerD->setAlpha(0.f);
    
}

void finalApp::onStateChange(int state)
{
    mCurrentState = state;
    ci::app::console() << "state " << mCurrentState << std::endl;

    if(mNodeContainerD->hasChildren()==true)
        mNodeContainerD->removeChild(toy2);
    if(mNodeContainerC->hasChildren()==true)
        mNodeContainerC->removeChild(toy1);
    
    if(mCurrentState==1){
         fireworks = false;
        video = VideoSample::create();
        video->getToggleStateChangeSignal().connect(std::bind(&finalApp::onStateChange, this, std::placeholders::_1));
        mNodeContainerA->addChild(video);

         ci::app::timeline().apply(&mNodeContainerA->getAlphaAnim(),1.f,3.f);
    }
      else if(mCurrentState==3){
        if(mNodeContainerD->hasChildren()==true)
        mNodeContainerD->removeAllChildren();
        if(mNodeContainerA->hasChildren()==true)
        mNodeContainerA->removeAllChildren();
        
        toy1 = fireworks::create();
        toy1->setDrawBounds(false);
        toy1->getToggleStateChangeSignal().connect(std::bind(&finalApp::onStateChange, this, std::placeholders::_1));
        mNodeContainerC->addChild(toy1);
        
       fireworks = true;
        ci::app::timeline().apply(&mNodeContainerC->getAlphaAnim(),1.f,3.f);
    }
    
    
    else if(mCurrentState==4){
        fireworks = false;
        if(mNodeContainerC->hasChildren()==true)
             mNodeContainerC->removeAllChildren();
        if(mNodeContainerA->hasChildren()==true)
            mNodeContainerA->removeAllChildren();
        
        toy2 = rolypoly::create();
        toy2->getToggleStateChangeSignal().connect(std::bind(&finalApp::onStateChange, this, std::placeholders::_1));
        mNodeContainerD->addChild(toy2);

        ci::app::timeline().apply(&mNodeContainerD->getAlphaAnim(),1.f,3.f);
    }
}

void finalApp::update()
{
    mScene->update();
}

void finalApp::draw()
{
    if(fireworks)
         gl::clear( Color( 0, 0, 0 ) );
    else
    gl::clear( Color( 255, 255, 255 ) );
     mScene->draw();
    ci::gl::color(0,0,0);
    cinder::gl::drawSolidRect(Rectf(0,0,400,getWindowHeight()));
    cinder::gl::drawSolidRect(Rectf(getWindowWidth()-400,0,getWindowWidth(),getWindowHeight()));
}

CINDER_APP( finalApp, RendererGl )
