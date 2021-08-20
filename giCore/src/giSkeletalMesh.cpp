#include "giSkeletalMesh.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace giEngineSDK {

  void 
  SkeletalMesh::update(float inDeltaTime, Vector<Matrix4>& inTransforms) {
    
    //for(auto mesh : m_meshes) {
      //mesh.update(inDeltaTime, inTransforms, m_globalInverseTransform);
    //}
  }


  bool 
  SkeletalMesh::loadFromFile(const String& inPath) {
    return false;
  }

  bool 
  SkeletalMesh::loadFromMemory(const char* inData, size_T inSizeOfData) {
    return false;
  }

  void 
  SkeletalMesh::unload() {

  }

  void 
  SkeletalMesh::saveToFile(const String& inFile) {

  }



  /*
  void 
  Mesh::update(float inDeltaTime, 
               Vector<Matrix4>& inTransforms, 
               const Matrix4& inGlobalTransform) {
    Matrix4 iden;
    iden = Matrix4::IDENTITY;

    
    
    float TicksPerSecond = m_scene->mAnimations[0]->mTicksPerSecond != 0 ?
                            m_scene->mAnimations[0]->mTicksPerSecond : 25.0f;
    float TimeInTicks = inDeltaTime * TicksPerSecond;
    float AnimationTime = fmod(TimeInTicks, m_scene->mAnimations[0]->mDuration);

    readNodeHeirarchy(AnimationTime, m_scene->mRootNode, iden, inGlobalTransform);

    inTransforms.resize(m_numBones);

    for (uint32 i = 0 ; i < m_numBones; i++) {
        inTransforms[i] = m_boneInfo[i].transformation;
    }
  }*/


  /*
  void 
  readNodeHeirarchy(float inAnimationTime, 
                    const aiNode* inNode, 
                    const Matrix4& inParentTransform,
                    const Matrix4& inGlobalTransform) {

    String NodeName(inNode->mName.data);

    const aiAnimation* pAnimation = m_scene->mAnimations[0];

    Matrix4 NodeTransformation;
    memcpy(&NodeTransformation, &inNode->mTransformation, sizeof(Matrix4));

    const aiNodeAnim* pNodeAnim = findNodeAnim(pAnimation, NodeName);

    if (pNodeAnim) {
      Transform tempTransform;
      // Interpolate scaling and generate scaling transformation matrix
      aiVector3D Scaling;
      calcInterpolatedScaling(Scaling, inAnimationTime, pNodeAnim);
      
      tempTransform.setScale({Scaling.x, Scaling.y, Scaling.z});

      // Interpolate rotation and generate rotation transformation matrix
      aiQuaternion RotationQ;
      Quaternion tmpQuad;
      calcInterpolatedRotation(RotationQ, inAnimationTime, pNodeAnim);
      Matrix4 RotationM;
      memcpy(&tmpQuad, &RotationQ, sizeof(Quaternion));
      RotationM = tmpQuad.getMatrix();
      tempTransform.setRotation(tmpQuad);

      // Interpolate translation and generate translation transformation matrix
      aiVector3D Translation;
      calcInterpolatedPosition(Translation, inAnimationTime, pNodeAnim);
      
      tempTransform.setTranslation({Translation.x, Translation.y, Translation.z});



      // Combine the above transformations
      NodeTransformation = tempTransform.getMatrix();
    }

    Matrix4 GlobalTransformation = NodeTransformation * inParentTransform;

    if (m_boneMapping.find(NodeName) != m_boneMapping.end()) {
      uint32 BoneIndex = m_boneMapping[NodeName];
      m_boneInfo[BoneIndex].transformation = GlobalTransformation * inGlobalTransform *
                                             m_boneInfo[BoneIndex].offset;
    }

    for (uint32 i = 0; i < inNode->mNumChildren; i++) {
      readNodeHeirarchy(inAnimationTime, inNode->mChildren[i], GlobalTransformation, inGlobalTransform);
    }
  }

  const aiNodeAnim* 
  findNodeAnim(const aiAnimation* inAnim, const String inNodeName) {
    for(int32 i = 0; i < inAnim->mNumChannels; i++) {
      const aiNodeAnim * temp = inAnim->mChannels[i];
      return inNodeName == String(temp->mNodeName.data) ? temp : nullptr;
    }
    return nullptr;
  }

  void 
  calcInterpolatedRotation(aiQuaternion& Out, 
                           float AnimationTime, 
                           const aiNodeAnim* pNodeAnim) {


     // we need at least two values to interpolate...
    if (pNodeAnim->mNumRotationKeys == 1) {
        Out = pNodeAnim->mRotationKeys[0].mValue;
        return;
    }

    uint32 RotationIndex = findRotation(AnimationTime, pNodeAnim);
    uint32 NextRotationIndex = (RotationIndex + 1);
    assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
    float DeltaTime = pNodeAnim->mRotationKeys[NextRotationIndex].mTime - 
                      pNodeAnim->mRotationKeys[RotationIndex].mTime;
    float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
    aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
    Out = Out.Normalize();
  }

  uint32 
  findRotation(float AnimationTime, const aiNodeAnim* pNodeAnim) {
    assert(pNodeAnim->mNumRotationKeys > 0);

    for (uint32 i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
      if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
        return i;
      }
    }

    return(0);
  }

  void 
  calcInterpolatedScaling(aiVector3D& Out, 
                          float inAnimationTime, 
                          const aiNodeAnim* inNodeAnim) {

    if(1 == inNodeAnim->mNumScalingKeys) {
      Out.x = inNodeAnim->mScalingKeys[0].mValue.x;
      Out.y = inNodeAnim->mScalingKeys[0].mValue.y;
      Out.z = inNodeAnim->mScalingKeys[0].mValue.z;
      return;
    }
     uint32 scalingIndex = findScaling(inAnimationTime, inNodeAnim);
     uint32 nextScalingIndex = scalingIndex + 1;

     float deltaTime = inNodeAnim->mRotationKeys[nextScalingIndex].mTime - 
                       inNodeAnim->mRotationKeys[scalingIndex].mTime;

    float factor = (inAnimationTime - (float)inNodeAnim->mRotationKeys[scalingIndex].mTime) / deltaTime;

    aiVector3D tmpStart;
    tmpStart.x = inNodeAnim->mScalingKeys[scalingIndex].mValue.x;
    tmpStart.y = inNodeAnim->mScalingKeys[scalingIndex].mValue.y;
    tmpStart.z = inNodeAnim->mScalingKeys[scalingIndex].mValue.z;

    aiVector3D tmpEnd;
    tmpEnd.x = inNodeAnim->mScalingKeys[nextScalingIndex].mValue.x;
    tmpEnd.y = inNodeAnim->mScalingKeys[nextScalingIndex].mValue.y;
    tmpEnd.z = inNodeAnim->mScalingKeys[nextScalingIndex].mValue.z;

    aiVector3D delta = tmpEnd - tmpStart;

    Out = tmpStart + (factor * delta);

  }

  uint32 
  findScaling(float AnimationTime, const aiNodeAnim* pNodeAnim) {
    assert(pNodeAnim->mNumScalingKeys > 0);

    for (uint32 i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
      if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
        return i;
      }
    }

    return(0);
  }

  void 
  calcInterpolatedPosition(aiVector3D& Out, 
                           float inAnimationTime, 
                           const aiNodeAnim* inNodeAnim) {
    if (1 == inNodeAnim->mNumPositionKeys) {
      Out.x = inNodeAnim->mPositionKeys[0].mValue.x;
      Out.y = inNodeAnim->mPositionKeys[0].mValue.y;
      Out.z = inNodeAnim->mPositionKeys[0].mValue.z;
      return;
    }
    uint32 positionIndex = findPosition(inAnimationTime, inNodeAnim);
    uint32 nextPositionIndex = positionIndex + 1;

    float deltaTime = inNodeAnim->mPositionKeys[nextPositionIndex].mTime -
                      inNodeAnim->mPositionKeys[positionIndex].mTime;

    float factor = (inAnimationTime - (float)inNodeAnim->mPositionKeys[positionIndex].mTime) / deltaTime;

    aiVector3D tmpStart;
    tmpStart.x = inNodeAnim->mPositionKeys[positionIndex].mValue.x;
    tmpStart.y = inNodeAnim->mPositionKeys[positionIndex].mValue.y;
    tmpStart.z = inNodeAnim->mPositionKeys[positionIndex].mValue.z;

    aiVector3D tmpEnd;
    tmpEnd.x = inNodeAnim->mPositionKeys[nextPositionIndex].mValue.x;
    tmpEnd.y = inNodeAnim->mPositionKeys[nextPositionIndex].mValue.y;
    tmpEnd.z = inNodeAnim->mPositionKeys[nextPositionIndex].mValue.z;

    aiVector3D delta = tmpEnd - tmpStart;

    Out = tmpStart + (factor * delta);
  }

  uint32 
  findPosition(float inAnimationTime, const aiNodeAnim* inNodeAnim) {
    assert(inNodeAnim->mNumPositionKeys > 0);

    for (uint32 i = 0; i < inNodeAnim->mNumPositionKeys - 1; i++) {
      if (inAnimationTime < (float)inNodeAnim->mPositionKeys[i + 1].mTime) {
        return i;
      }
    }

    return(0);
  }
  */

}