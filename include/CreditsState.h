#ifndef CreditsState_H
#define CreditsState_H

#include <Ogre.h>
#include <OIS/OIS.h>

#include "GameState.h"

class CreditsState : public Ogre::Singleton<CreditsState>, public GameState
{
 public:
  CreditsState() {}

  void enter ();
  void exit ();
  void pause ();
  void resume ();

  void keyPressed (const OIS::KeyEvent &e);
  void keyReleased (const OIS::KeyEvent &e);

  void mouseMoved (const OIS::MouseEvent &e);
  void mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
  void mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

  bool frameStarted (const Ogre::FrameEvent& evt);
  bool frameEnded (const Ogre::FrameEvent& evt);

  // Heredados de Ogre::Singleton.
  static CreditsState& getSingleton ();
  static CreditsState* getSingletonPtr ();

 protected:
  Ogre::Root* _root;
  Ogre::SceneManager* _sceneManager;
  Ogre::SceneNode* _sceneNode;
  Ogre::Viewport* _viewport;
  Ogre::Camera* _camera;

  bool _exitGame;
  std::string _message;
};

#endif
