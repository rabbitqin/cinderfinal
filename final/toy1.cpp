#include "toy1.hpp"
#include "poShape.h"
#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"
#include "TextSample.hpp"
#include "cinder/ImageIo.h"
#include "cinder/qtime/QuickTimeGl.h"

using namespace po::scene;

fireworksRef fireworks::create()
{
    fireworksRef node(new fireworks());
    node->setup();
    return node;
}

fireworks::fireworks()
{
}

void fireworks::setup()
{
    tri = false;
    
    mFire = po::scene::VideoGl::create();
    ci::fs::path moviePath = ci::app::getAssetPath("nofire.mov");
    ci::fs::path moviePath2 = ci::app::getAssetPath("fire.mov");
    
    
    try {
        movieRef1 = ci::qtime::MovieGl::create(moviePath);
        movieRef2 = ci::qtime::MovieGl::create(moviePath2);
        mFire->setMovieRef(movieRef1);
        mFire->getMovieRef()->play();
    } catch (...) {
        ci::app::console() << "PlayerNode::setup: Failed to load movie" << std::endl;
    }
    
    mFire->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mFire->setPosition(ci::app::getWindowWidth()/2.f,ci::app::getWindowHeight()/2.f-80.f);
    mFire->getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&fireworks::fire, this, std::placeholders::_1));
    addChild(mFire);
   
    ci::gl::TextureRef temp = ci::gl::Texture::create(loadImage(ci::app::loadAsset("history1802.png")));
    buttom = Shape::create(temp);
    buttom->setAlignment(po::scene::Alignment::CENTER_CENTER);
    buttom->setPosition(ci::app::getWindowWidth()/2.f+200.f,100.f);
    buttom->getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&fireworks::trigger, this, std::placeholders::_1));
    addChild(buttom);
    
    ci::gl::TextureRef home = ci::gl::Texture::create(loadImage(ci::app::loadAsset("back1802.png")));
    ShapeRef ball = Shape::create(home);
    ball->setAlignment(po::scene::Alignment::CENTER_CENTER);
    ball->setPosition(ci::app::getWindowWidth()/2.f-200.f,100.f);
    ball->getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&fireworks::trigger2, this, std::placeholders::_1));
    addChild(ball);
    
    ci::gl::TextureRef his = ci::gl::Texture::create(loadImage(ci::app::loadAsset("fireinfo.png")));
    mHistory = Shape::create(his);
    mHistory->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mHistory->setPosition(ci::app::getWindowWidth()*0.5, ci::app::getWindowHeight()*0.5+300.f);
    mHistory->setAlpha(1.f);
    addChild(mHistory);
    
    ci::gl::TextureRef shange = ci::gl::Texture::create(loadImage(ci::app::loadAsset("shange.png")));
    info = Shape::create(shange);
    info->setAlignment(po::scene::Alignment::CENTER_CENTER);
    info->setPosition(ci::app::getWindowWidth()*0.5, ci::app::getWindowHeight());
    info->setAlpha(0);
    addChild(info);

    
    
    
    std::string text = "Fireworks are a class of low explosive pyrotechnic devices used for aesthetic and entertainment purposes. The most common use of a firework is as part of a fireworks display (also called a fireworks show or pyrotechnics), a display of the effects produced by firework devices.";
    
    
    std::string text1 = "The earliest documentation of fireworks dates back to 7th century China (time of the Tang Dynasty), where they were invented. The fireworks were used to accompany many festivities. It is thus a part of the culture of China and had its origin there; eventually it spread to other cultures and societies.[3] The art and science of firework making has developed into an independent profession. In China, pyrotechnicians were respected for their knowledge of complex techniques in mounting firework displays.[4] Chinese people originally believed that the fireworks could expel evil spirits and bring about luck and happiness.";
    
    //	Create the ci textbox
    ciTextBox1 = ci::TextBox();
    ciTextBox1.size(250, 350);
    ciTextBox1.color(ci::Color(0.2, 0.2, 0.2));
    ciTextBox1.text(text1);
    ciTextBox1.alignment(ci::TextBox::Alignment::LEFT);
    ciTextBox1.font(ci::Font("Arial", 15));
    
    mText = TextBox::create(ciTextBox1);
    mText->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mText->setPosition(ci::app::getWindowWidth() * 0.5, ci::app::getWindowHeight() * 0.5);
    mText->setAlpha(0);
    addChild(mText);
    
    
}

void fireworks::update(){
    
}

void fireworks::trigger(po::scene::MouseEvent &event)
{
    tri=!tri;
    if(tri){
        ci::app::timeline().apply(&info->getPositionAnim(),ci::vec2(ci::app::getWindowWidth() * 0.5,ci::app::getWindowHeight() * 0.5),0.5f,ci::EaseInOutQuad());
        ci::app::timeline().apply(&info->getAlphaAnim(),1.f,0.5f);
        ci::app::timeline().apply(&mText->getPositionAnim(),ci::vec2(ci::app::getWindowWidth() * 0.5,ci::app::getWindowHeight() * 0.5),0.5f,ci::EaseInOutQuad());
        ci::app::timeline().apply(&mText->getAlphaAnim(),1.f,0.5f);
    }
    else{
        ci::app::timeline().apply(&info->getPositionAnim(),ci::vec2(ci::app::getWindowWidth() * 0.5,ci::app::getWindowHeight()),0.5f,ci::EaseInOutQuad());
        ci::app::timeline().apply(&info->getAlphaAnim(),0.f,0.3f);
        ci::app::timeline().apply(&mText->getPositionAnim(),ci::vec2(ci::app::getWindowWidth() * 0.5,ci::app::getWindowHeight()),0.5f,ci::EaseInOutQuad());
        ci::app::timeline().apply(&mText->getAlphaAnim(),0.f,0.3f);
        }

}

void fireworks::fire(po::scene::MouseEvent &event)  {
            if(mFire->getMovieRef()==movieRef1){
                mFire->setMovieRef(movieRef2);
                mFire->getMovieRef()->seekToStart();
                mFire->getMovieRef()->play();
        }else{
            mFire->setMovieRef(movieRef1);
            }
}

void fireworks::trigger2(po::scene::MouseEvent &event)
{
           mToggleStateChangeSignal.emit(1);
  
}


