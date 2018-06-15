#ifndef VERTEXSKINDATA_H
#define VERTEXSKINDATA_H
#include <QList>
#include <cmath>
using namespace std;

class VertexSkinData
{
public:
    VertexSkinData();
	void addBoneEffect(int boneId, float weight);
	void limitBoneNumber(int max);
    QList<int>& getBoneIds();
    QList<float>& getWeights();

private:
    QList<int> m_boneIds;
    QList<float> m_weights;
    void fillEmptyWeights(int max);
    float saveTopWeights(float* topWeightsArray, int max);
    void refillWeightList(float* topWeights, float total, int max);
	void removeExcessBoneIds(int max);
};

#endif // VERTEXSKINDATA_H
