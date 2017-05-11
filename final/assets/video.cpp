
//

#include "video.hpp"
#include "cinder/qtime/QuickTimeGl.h"
#include "poShape.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/Timeline.h"
#include "cinder/Utilities.h"

using namespace po::scene;
using namespace ci;

VideoSampleRef VideoSample::create()
{
    VideoSampleRef node(new VideoSample());
    node->setup();
    return node;
}

VideoSample::VideoSample()
{
}

void VideoSample::setup()
{
  
    //mypos = cinder::gl::vec2(520.f,540.f);
    //    mTexture = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset("1.png")));
    //    mTexture->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
    
    //  create a player that loops video
    // capsule = false;
    mVideo = po::scene::VideoGl::create();
    ci::fs::path moviePath = ci::app::getAssetPath("static2.mov");
    ci::fs::path moviePath2 = ci::app::getAssetPath("movev.mov");
    
    try {
        
        movieRef1 = ci::qtime::MovieGl::create(moviePath);
        movieRef2 = ci::qtime::MovieGl::create(moviePath2);
        
        
        mVideo->setMovieRef(movieRef1);
        mVideo->getMovieRef()->setLoop(true);
        mVideo->getMovieRef()->play();
    } catch (...) {
        ci::app::console() << "PlayerNode::setup: Failed to load movie" << std::endl;
    }
    
    mVideo->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mVideo->setPosition(ci::app::getWindowCenter());
    mVideo->getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&VideoSample::onMouseEvent, this, std::placeholders::_1));
    addChild(mVideo);
    
    ci::gl::TextureRef tryit = ci::gl::Texture::create(loadImage(ci::app::loadAsset("TRYIT2.png")));
    ShapeRef tryit1 = Shape::create(tryit);
    
    tryit1->setPosition(320.f,500.f);
    ci::app::timeline().apply(&tryit1->getPositionAnim(),ci::vec2(340.f,500.f),0.4f,ci::EaseInOutQuad()).pingPong().loop();
    addChild(tryit1);
    
//    ci::app::timeline().apply(&tryit1.,1.f,3.f);
//    mNodeContainerB->setAlpha(0.f);
    //    fire->getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&fireworks::onMouseEvent, this, std::placeholders::_1));
  
    
    
}


void VideoSample::onMouseEvent(po::scene::MouseEvent &event)
{
    switch (event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
            //            capsule=!capsule;
            if(mVideo->getMovieRef()==movieRef1){
                mVideo->setMovieRef(movieRef2);
                //mVideo->getMovieRef()->seekToStart();
                mVideo->getMovieRef()->play();
                mVideo->getMovieRef()->setLoop(false);
            }else{
                mToggleStateChangeSignal.emit(2);
                mVideo->setMovieRef(movieRef1);
                 mVideo->getMovieRef()->seekToStart();
                mVideo->getMovieRef()->setLoop(true);
                //mVideo->getMovieRef()->play();
            }//                ci::app::timeline().apply(&mToggleCircle->getPositionAnim(), mActivePosition, mAnimationTime, ci::EaseOutExpo());
            //                mToggleStateChangeSignal.emit(true);
            //            }
            break;
        default:
            break;
    }
}

