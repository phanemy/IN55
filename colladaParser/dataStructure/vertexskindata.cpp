#include "vertexskindata.h"
#include <iostream>
using namespace std;

VertexSkinData::VertexSkinData(){}

void VertexSkinData::addJointEffect(int jointId, float weight){
    QList<float>::iterator itWeights;
    QList<int>::iterator itBone = m_boneIds.begin();
    for(itWeights = m_weights.begin();itWeights != m_weights.end(); ++itWeights)
    {
        if(weight > *itWeights){
            m_boneIds.insert(itBone, jointId);
            m_weights.insert(itWeights, weight);
            return;
        }
        ++itBone;
    }
//	cout << jointId << " "<<weight<<endl;
    m_boneIds.push_back(jointId);
    m_weights.push_back(weight);
}

void VertexSkinData::limitJointNumber(const int  max){
    if(this->m_boneIds.size() > max){
        float* topWeights = new float[max];
        float total = saveTopWeights(topWeights, max);
        refillWeightList(topWeights, total, max);
        removeExcessJointIds(max);
        delete topWeights;
    }else if(this->m_boneIds.size() < max){
        fillEmptyWeights(max);
    }
}

void VertexSkinData::fillEmptyWeights(int max){
    while(this->m_boneIds.size() < max){
        this->m_boneIds.push_back(0);
        this->m_weights.push_back(0);
    }
}

float VertexSkinData::saveTopWeights(float* topWeightsArray, int max){
    float total = 0;
    QList<float>::iterator it = this->m_weights.begin();
    for(int i=0;i<max;i++){
        topWeightsArray[i] = *it;
        total += topWeightsArray[i];
        it++;
    }
    return total;
}

void VertexSkinData::refillWeightList(float* topWeights, float total, int max){
    this->m_weights.clear();
    for(int i=0;i<max;i++){
        m_weights.push_back(fmin(topWeights[i]/total, 1));
    }
}

void VertexSkinData::removeExcessJointIds(int max){
    while(this->m_boneIds.size() > max){
       this->m_boneIds.pop_back();
    }
}

QList<int>& VertexSkinData::getBoneIds(){
    return this->m_boneIds;
}

QList<float>& VertexSkinData::getWeights(){
    return this->m_weights;
}
