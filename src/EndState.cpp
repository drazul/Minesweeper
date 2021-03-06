#include "EndState.h"

template<> EndState* Ogre::Singleton<EndState>::msSingleton = 0;

void
EndState::enter ()
{
  if(_root == nullptr){
    _root = Ogre::Root::getSingletonPtr();

    std::cout << _message << std::endl;
    _sceneManager = _root->getSceneManager("PlaySceneManager");

    _camera = _sceneManager->getCamera("MainCamera");
    _viewport = _root->getAutoCreatedWindow()->getViewport(0);
    _viewport->setBackgroundColour(Ogre::ColourValue(0.0, 1.0, 0.0));

    _sceneNode = _sceneManager->createSceneNode("EndScene");

    if(_level ==Difficulty::Easy) {
      _sceneNode->setScale(2, 1, 2);
      _sceneNode->setPosition(8, 7, 1);
    }else if (_level == Difficulty::Medium) {
      _sceneNode->setScale(4.5, 2, 4.5);
      _sceneNode->setPosition(18, 9, 1);
    }else if (_level == Difficulty::VeryEasy) {
      _sceneNode->setScale(1.5, 0.75, 1.5);
      _sceneNode->setPosition(3, 6, 1);      
    }

    _sceneNode->yaw(Ogre::Degree(180));

    _sceneManager->getRootSceneNode()->addChild(_sceneNode);
  }

  Ogre::Entity* entity;

  if (_message == "GameOver")
    entity = _sceneManager->createEntity("gameOver.mesh");
  else 
    entity = _sceneManager->createEntity("win.mesh");

  _sceneNode->attachObject(entity);

  _exitGame = false;
}

void
EndState::setMessage(std::string message, Difficulty level){
  _message = message;
  _level = level;
}

void
EndState::exit ()
{
  _sceneNode->detachAllObjects();
}

void
EndState::pause ()
{
}

void
EndState::resume ()
{
}

bool
EndState::frameStarted
(const Ogre::FrameEvent& evt)
{
  return true;
}

bool
EndState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;
  
  return true;
}

void
EndState::keyPressed
(const OIS::KeyEvent &e) {
    popState();
}

void
EndState::keyReleased
(const OIS::KeyEvent &e)
{
}

void
EndState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
EndState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  popState();
}

void
EndState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

EndState*
EndState::getSingletonPtr ()
{
return msSingleton;
}

EndState&
EndState::getSingleton ()
{ 
  assert(msSingleton);
  return *msSingleton;
}
