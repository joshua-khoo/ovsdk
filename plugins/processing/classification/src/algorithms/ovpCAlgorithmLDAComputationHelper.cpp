#include "ovpCAlgorithmLDAComputationHelper.h"

#include <sstream>
#include <vector>

using namespace OpenViBE;
using namespace OpenViBE::Kernel;
using namespace OpenViBE::Plugins;

using namespace OpenViBEPlugins::Classification;

using namespace OpenViBEToolkit;

using namespace Eigen;


namespace{
	const char* const c_sBaseNodeName     = "Class-config";
	const char* const c_sWeightNodeName   = "Weights";
	const char* const c_sBiasNodeName     = "Bias";
}

CAlgorithmLDAComputationHelper::CAlgorithmLDAComputationHelper():m_f64Bias(0)
{
}

void CAlgorithmLDAComputationHelper::setWeight(MatrixXd &rWeigth)
{
	m_oWeight = rWeigth;
}

void CAlgorithmLDAComputationHelper::setBias(float64 f64Bias)
{
	m_f64Bias = f64Bias;
}

float64 CAlgorithmLDAComputationHelper::getValue(MatrixXd &rFeatureVector)
{
	return (m_oWeight * rFeatureVector.transpose()).col(0)(0) + m_f64Bias;
}

boolean CAlgorithmLDAComputationHelper::loadConfiguration(XML::IXMLNode *pConfiguration)
{
	std::stringstream l_sBias(pConfiguration->getChildByName(c_sBiasNodeName)->getPCData());
	l_sBias >> m_f64Bias;

	std::stringstream l_sData(pConfiguration->getChildByName(c_sWeightNodeName)->getPCData());
	std::vector < float64 > l_vCoefficients;
	while(!l_sData.eof())
	{
		float64 l_f64Value;
		l_sData >> l_f64Value;
		l_vCoefficients.push_back(l_f64Value);
	}

	m_oWeight.resize(1,l_vCoefficients.size());
	for(size_t i=0; i<l_vCoefficients.size(); i++)
	{
		m_oWeight(0,i)=l_vCoefficients[i];
	}
	return true;
}

XML::IXMLNode *CAlgorithmLDAComputationHelper::getConfiguration()
{
	XML::IXMLNode* l_pRootNode = XML::createNode(c_sBaseNodeName);


	std::stringstream l_sWeigths;
	std::stringstream l_sBias;


	l_sWeigths << std::scientific;
	for(int32 i=0; i<m_oWeight.size(); i++)
	{
		l_sWeigths << " " << m_oWeight(0,i);
	}

	l_sBias << m_f64Bias;

	XML::IXMLNode* l_pTempNode = XML::createNode(c_sWeightNodeName);
	l_pTempNode->setPCData(l_sWeigths.str().c_str());
	l_pRootNode->addChild(l_pTempNode);

	l_pTempNode = XML::createNode(c_sBiasNodeName);
	l_pTempNode->setPCData(l_sBias.str().c_str());
	l_pRootNode->addChild(l_pTempNode);

	return l_pRootNode;
}
