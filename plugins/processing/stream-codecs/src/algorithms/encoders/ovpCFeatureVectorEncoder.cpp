#include "ovpCFeatureVectorEncoder.h"

using namespace OpenViBE;
using namespace OpenViBE::Kernel;
using namespace OpenViBE::Plugins;

using namespace OpenViBEPlugins;
using namespace OpenViBEPlugins::StreamCodecs;


boolean CFeatureVectorEncoder::processHeader(void)
{
	OV_ERROR_UNLESS_KRF(
		ip_pMatrix->getDimensionCount() == 1,
		"Invalid feature vector: found " << ip_pMatrix->getDimensionCount() << " dimensions, 1 expected",
		OpenViBE::Kernel::ErrorType::BadInput
	);

	CStreamedMatrixEncoder::processHeader();

	return true;
}
