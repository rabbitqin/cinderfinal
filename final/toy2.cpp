#include "toy2.hpp"
#include "poShape.h"
#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"
#include "TextSample.hpp"
#include "cinder/ImageIo.h"
#include "cinder/qtime/QuickTimeGl.h"

using namespace po::scene;

rolypolyRef rolypoly::create()
{
    rolypolyRef node(new rolypoly());
    node->setup();
    return node;
}

rolypoly::rolypoly()
{
}

void rolypoly::setup()
{
    tri = false;
    
    mRoly = po::scene::VideoGl::create();
    ci::fs::path moviePath = ci::app::getAssetPath("Comp1.mov");
    ci::fs::path moviePath2 = ci::app::getAssetPath("Comp2.mov");
    
    try {
        
        movieRef1 = ci::qtime::MovieGl::create(moviePath);
        movieRef2 = ci::qtime::MovieGl::create(moviePath2);
        
        
        mRoly->setMovieRef(movieRef1);
        mRoly->getMovieRef()->play();
    } catch (...) {
        ci::app::console() << "PlayerNode::setup: Failed to load movie" << std::endl;
    }
    
    mRoly->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mRoly->setPosition(ci::app::getWindowCenter());
    mRoly->getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&rolypoly::onMouseEvent, this, std::placeholders::_1));
    addChild(mRoly);
    
    ci::gl::TextureRef home = ci::gl::Texture::create(loadImage(ci::app::loadAsset("back180.png")));
    ShapeRef ball = Shape::create(home);
    ball->setAlignment(po::scene::Alignment::CENTER_CENTER);
    ball->setPosition(ci::app::getWindowWidth() * 0.5-200.f,100.f);
    ball->getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&rolypoly::goback, this, std::placeholders::_1));
    addChild(ball);
    
    std::string text = "Fireworks are a class of low explosive pyrotechnic devices used for aesthetic and entertainment purposes. The most common use of a firework is as part of a fireworks display (also called a fireworks show or pyrotechnics), a display of the effects produced by firework devices.";
    
    
    std::string text1 = "You got a roly-poly toy!";
    
    //	Create the ci textbox
    ci::TextBox ciTextBox = ci::TextBox();
    ciTextBox.size(200, 200);
    ciTextBox.color(ci::Color(0.7, 0.7, 0.7));
    ciTextBox.text(text);
    ciTextBox.alignment(ci::TextBox::Alignment::CENTER);
    ciTextBox.font(ci::Font("Arial", 15));
//
//    //	Create a text box that rotates
    
    ci::gl::TextureRef temp = ci::gl::Texture::create(loadImage(ci::app::loadAsset("history180.png")));
    buttom = Shape::create(temp);
    buttom->setAlignment(po::scene::Alignment::CENTER_CENTER);
    buttom->setPosition(ci::app::getWindowWidth()/2.f+200.f,100.f);
    buttom->getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&rolypoly::trigger, this, std::placeholders::_1));
    addChild(buttom);
    
    ci::gl::TextureRef his = ci::gl::Texture::create(loadImage(ci::app::loadAsset("rolypolyinfo.png")));
    mHistory = Shape::create(his);
    mHistory->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mHistory->setPosition(ci::app::getWindowWidth()*0.5, ci::app::getWindowHeight()*0.5+260.f);
    mHistory->setAlpha(1.f);
    addChild(mHistory);
    
    ci::gl::TextureRef shange = ci::gl::Texture::create(loadImage(ci::app::loadAsset("pic.png")));
    info = Shape::create(shange);
    info->setAlignment(po::scene::Alignment::CENTER_CENTER);
    info->setPosition(ci::app::getWindowWidth()*0.5, ci::app::getWindowHeight());
    info->setAlpha(0);
    addChild(info);
    
    mText = TextBox::create(ciTextBox);
    mText->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mText->setPosition(ci::app::getWindowWidth() * 0.5, ci::app::getWindowHeight() * 0.5);
    mText->setAlpha(0);
    addChild(mText);


}

void rolypoly::update(){
    
}

void rolypoly::onMouseEvent(po::scene::MouseEvent &event)
{
    switch (event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
            if(mRoly->getMovieRef()==movieRef1){
                mRoly->setMovieRef(movieRef2);
                mRoly->getMovieRef()->seekToStart();
                mRoly->getMovieRef()->play();
            }else{
                mRoly->setMovieRef(movieRef1);
            }
            break;
        default:
            break;
    }
}

void rolypoly::trigger(po::scene::MouseEvent &event){
    tri=!tri;
    if(tri){
        ci::app::timeline().apply(&info->getPositionAnim(),ci::vec2(ci::app::getWindowWidth() * 0.5,ci::app::getWindowHeight() * 0.5),0.5f,ci::EaseInOutQuad());
               ci::app::timeline().apply(&info->getAlphaAnim(),1.f,0.5f);
    }
    else{
        ci::app::timeline().apply(&info->getPositionAnim(),ci::vec2(ci::app::getWindowWidth() * 0.5,ci::app::getWindowHeight()),0.5f,ci::EaseInOutQuad());
        ci::app::timeline().apply(&info->getAlphaAnim(),0.f,0.3f);
    }
}

void rolypoly::goback(po::scene::MouseEvent &event){
mToggleStateChangeSignal.emit(1);
}
