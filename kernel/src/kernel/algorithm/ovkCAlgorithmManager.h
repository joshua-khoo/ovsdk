#ifndef __OpenViBEKernel_Kernel_Algorithm_CAlgorithmManager_H__
#define __OpenViBEKernel_Kernel_Algorithm_CAlgorithmManager_H__

#include "../ovkTKernelObject.h"

#include <map>

namespace OpenViBE
{
	namespace Kernel
	{
		class CAlgorithmProxy;

		class CAlgorithmManager : public OpenViBE::Kernel::TKernelObject < OpenViBE::Kernel::IAlgorithmManager >
		{
		public:

			explicit CAlgorithmManager(const OpenViBE::Kernel::IKernelContext& rKernelContext);
			virtual ~CAlgorithmManager(void);

			virtual OpenViBE::CIdentifier createAlgorithm(
				const OpenViBE::CIdentifier& rAlgorithmClassIdentifier);
			virtual OpenViBE::CIdentifier createAlgorithm(
				const OpenViBE::Plugins::IAlgorithmDesc& rAlgorithmDesc);
			virtual OpenViBE::boolean releaseAlgorithm(
				const OpenViBE::CIdentifier& rAlgorithmIdentifier);
			virtual OpenViBE::boolean releaseAlgorithm(
				OpenViBE::Kernel::IAlgorithmProxy& rAlgorithm);
			virtual OpenViBE::Kernel::IAlgorithmProxy& getAlgorithm(
				const OpenViBE::CIdentifier& rAlgorithmIdentifier);
			virtual OpenViBE::CIdentifier getNextAlgorithmIdentifier(
				const OpenViBE::CIdentifier& rPreviousIdentifier) const;

			_IsDerivedFromClass_Final_(OpenViBE::Kernel::TKernelObject<OpenViBE::Kernel::IAlgorithmManager>, OVK_ClassId_Kernel_Algorithm_AlgorithmManager);

		protected:

			virtual OpenViBE::CIdentifier getUnusedIdentifier(void) const;

		protected:

			using AlgorithmMap = std::map < OpenViBE::CIdentifier, OpenViBE::Kernel::CAlgorithmProxy* >;
			AlgorithmMap m_vAlgorithms;
		};
	};
};

#endif // __OpenViBEKernel_Kernel_Algorithm_CAlgorithmManager_H__
