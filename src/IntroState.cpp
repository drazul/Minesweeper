#include "IntroState.h"
#include "PlayState.h"

template<> IntroState* Ogre::Singleton<IntroState>::msSingleton = 0;

void
IntroState::enter ()
{
  std::cout << "Estado intro " << std::endl;
  _level = Difficulty::Easy;
  _minesweeper.set_difficulty(_level);
  _minesweeper.initialize();  _root = Ogre::Root::getSingletonPtr();

  _sceneManager = _root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
  _camera = _sceneManager->createCamera("MainCamera");

  _camera->setPosition(Vector3(7.19941, 13.4578, -10.0267));
  _camera->setDirection(Vector3(-0.00103734, -0.62784, 0.778358));
  _camera->setNearClipDistance(0.1);
  _camera->setFarClipDistance(100);
  _root->getAutoCreatedWindow()->addViewport(_camera);

  createScene();
  createOverlay();

  //_framelistener = new MyFrameListener(_root->getAutoCreatedWindow(), _camera, _overlayManager, _sceneManager, _minesweeper, _entityNodes);
  //_root->addFrameListener(_framelistener);
  
  _root->startRendering();

  _exitGame = false;
}

void IntroState::createOverlay() {
  _overlayManager = OverlayManager::getSingletonPtr();
  Overlay *overlay = _overlayManager->getByName("Info");
  overlay->show();
}


void IntroState::createScene() {

  createGroundScene();
  //createPlane4RayQuery();
  createBoardScene();
}

void IntroState::createBoardScene() {
  //Se debe sustitutir esto por el nivel correspondiente
  Ogre::Entity * entity;
  Ogre::SceneNode * sceneNode = _sceneManager->createSceneNode("BoardSceneNode");
  Ogre::SceneNode * sceneNodeCells;
  std::stringstream sceneNodeName;

  std::vector<char> visibleBoard = _minesweeper.get_visible_board();

  for(int i = 0; i < _level; i++) {
    for(int j = 0; j < _level; j++) {
      sceneNodeName << "Cell" << i << j << "";

      sceneNodeCells = _sceneManager->createSceneNode(sceneNodeName.str());
      entity = _sceneManager->createEntity("Cell.mesh");
      entity->setMaterialName("hierba");

      sceneNodeCells->attachObject(entity);
      //Multiplico por 2 porque ese es el tamaño de cada celda, el 0.1 restante es para separarlas un poquito
      sceneNodeCells->setPosition(2.1 * i, 0, 2.1 * j);
      sceneNode->addChild(sceneNodeCells);

      sceneNodeName.str(""); sceneNodeName.str(""); // Limpiamos el stream

      _entityNodes.push_back(entity);
    }
  }
  _sceneManager->getRootSceneNode()->addChild(sceneNode);
}

void IntroState::createGroundScene() {
  //Creo el plano del suelo
  Ogre::Plane planeGround(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("planeGround",
  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeGround,
  200,200,1,1,true,1,20,20,Ogre::Vector3::UNIT_Z);

  //Creo el nodo de escena y la entidad que van a contener al plano
  Ogre::SceneNode* GroundNode = _sceneManager->createSceneNode("Ground");
  Ogre::Entity* groundEnt = _sceneManager->createEntity("Ground", "planeGround");
  groundEnt->setMaterialName("Ground");
  GroundNode->attachObject(groundEnt);

  //Añado una luz a la escena, le doy una direccion y la adjunto al nodo de escena
  _sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE); 
  Ogre::Light* light = _sceneManager->createLight("Light");
  light->setType(Ogre::Light::LT_DIRECTIONAL);
  light->setDirection(Ogre::Vector3(1,-1,0));
  GroundNode->attachObject(light);

  //Adjunto al nodo de escena principal el nodo de escena creado
  _sceneManager->getRootSceneNode()->addChild(GroundNode);
}

void
IntroState::exit()
{
  _sceneManager->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void
IntroState::pause ()
{
}

void
IntroState::resume ()
{
}

bool
IntroState::frameStarted
(const Ogre::FrameEvent& evt) 
{
  return true;
}

bool
IntroState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;
  
  return true;
}

void
IntroState::keyPressed
(const OIS::KeyEvent &e)
{
  // Transición al siguiente estado.
  // Espacio --> PlayState
  if (e.key == OIS::KC_SPACE) {
    changeState(PlayState::getSingletonPtr());
  }
}

void
IntroState::keyReleased
(const OIS::KeyEvent &e )
{
  if (e.key == OIS::KC_ESCAPE) {
    _exitGame = true;
  }
}

void
IntroState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
IntroState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
IntroState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

IntroState*
IntroState::getSingletonPtr ()
{
return msSingleton;
}

IntroState&
IntroState::getSingleton ()
{ 
  assert(msSingleton);
  return *msSingleton;
}