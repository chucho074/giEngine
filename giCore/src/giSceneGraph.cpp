/**
 * @file    giSceneGraph.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    16/07/2021
 * @brief   An implementation of a Scene Graph.
 */
 
/**
 * @include
 */
#include "giSceneGraph.h"

namespace giEngineSDK {

  SceneGraph::SceneGraph() {
    init();
  }

  void 
  SceneGraph::init() {
    m_sceneID = UUID();
    m_numActors = 0;
    SharedPtr<Actor> sceneActor;
    m_root = make_shared<SceneNode>();
    sceneActor = make_shared<Actor>();
    m_root->m_actor = sceneActor;
    m_root->m_actor->m_actorName = "Root";

    //Editor camera
    m_editorCamera = make_shared<Camera>();
    m_editorCamera->init(Degrees(75.0f).getRadians(),
                         1280.f / 720.f,
                         0.01f,
                         1000.0f);
  }

  void
  SceneGraph::addActor(const SharedPtr<Actor>& inActor, 
                       SharedPtr<SceneNode> inParent) {
    m_numActors++;
    inActor->m_actorId = m_numActors;
    SharedPtr<SceneNode> tmpNode = make_shared<SceneNode>();
    tmpNode->m_actor = inActor;
    tmpNode->m_parent = inParent;
    m_root->m_childs.push_back(tmpNode);
  }

  SharedPtr<Actor>
  SceneGraph::getActorByID(const uint32& inID) {
    return m_root->getActorByID(inID);  
  }

  SharedPtr<Actor>
  SceneGraph::getActorByName(const String& inName) {
    return m_root->getActorByName(inName);
  }

  Vector<SharedPtr<Actor>>
  SceneGraph::getActorsFromRoot() {
    Vector<SharedPtr<Actor>> tmpVector;
    for (auto nodes : m_root->m_childs) {
      tmpVector.push_back(nodes->m_actor);
    }

    return tmpVector;
  }

  List<SharedPtr<SceneNode>>
  SceneGraph::getNodesByParent(WeakPtr<SceneNode> inParent) {
    if (SharedPtr<SceneNode>(nullptr) == inParent.lock()) {
      List<SharedPtr<SceneNode>> tmpList;
      tmpList.push_back(m_root);
      return tmpList;
    }

    return m_root->getNodesByParent(inParent);
  }

  SharedPtr<SceneNode>
  SceneGraph::getRoot() {
    return m_root;
  }

  void
  SceneGraph::deleteActor(const SharedPtr<Actor>& inActor) {
    m_root->deleteActor(inActor);
  }

  void
  SceneGraph::update(float inDelta) {
    m_root->udpate(inDelta);
    m_editorCamera->update(inDelta);
  }

  void 
  SceneGraph::draw() {
    m_root->render();
  }

  void 
  SceneGraph::clearGraph() {
    m_sceneName = "Untitled scene";
    m_sceneID = 0;
    //m_selectedActor;
    m_numActors = 0;
    
    m_root->destroy();
    m_editorCamera->destroy();

    init();
  }

  void 
  SceneGraph::resizeMainCamera(int32 inW, int32 inH) {

    m_editorCamera->resize(inW, inH);
    
  }

  SceneGraph&
  g_sceneGraph() {
    return SceneGraph::instance();
  }
}