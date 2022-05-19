/**
 * @file    giSceneGraph.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    16/07/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giSceneGraph.h"


namespace giEngineSDK {


  SceneGraph::SceneGraph() {
    m_numActors = 0;
    SharedPtr<Actor> sceneActor;
    m_root = make_shared<SceneNode>();
    sceneActor = make_shared<Actor>();
    m_root->m_actor = sceneActor;
    m_root->m_actor->m_actorName = "Root";
  }

  void 
  SceneGraph::addActor(const SharedPtr<Actor>& inActor, SharedPtr<SceneNode> inParent) {
    m_numActors++;
    inActor->m_actorId = m_numActors;
    SharedPtr<SceneNode> tmpNode = make_shared<SceneNode>();
    tmpNode->m_actor = inActor;
    tmpNode->m_parent = inParent;
    m_root->getNodesByParent(inParent).push_back(tmpNode);
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

  List<SharedPtr<SceneNode>>&
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
  }

  void 
  SceneGraph::draw() {
    m_root->render();
  }

  
  SceneGraph&
  g_sceneGraph() {
    return SceneGraph::instance();
  }
}