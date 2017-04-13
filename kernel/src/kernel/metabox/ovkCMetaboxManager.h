#ifndef __OpenViBEKernel_Kernel_Metabox_CMetaboxManager_H__
#define __OpenViBEKernel_Kernel_Metabox_CMetaboxManager_H__

#include "../ovkTKernelObject.h"

#include <vector>
#include <map>

#define OVP_ScenarioimportContext_OnLoadMetaboxImport OpenViBE::CIdentifier(0xED48480A, 0x9F6DBAA7)

namespace OpenViBE
{
	namespace Kernel
	{
		class CMetaboxManager : public OpenViBE::Kernel::TKernelObject<OpenViBE::Kernel::IMetaboxManager>
		{
		public:

			explicit CMetaboxManager(const OpenViBE::Kernel::IKernelContext& rKernelContext);
			virtual ~CMetaboxManager(void);

			virtual bool addMetaboxFromFiles(const OpenViBE::CString& rFileNameWildCard);
//			virtual OpenViBE::boolean registerPluginDesc(
//				const OpenViBE::Plugins::IPluginObjectDesc& rPluginObjectDesc);

//			virtual OpenViBE::CIdentifier getNextPluginObjectDescIdentifier(
//				const OpenViBE::CIdentifier& rPreviousIdentifier) const;
//			virtual OpenViBE::CIdentifier getNextPluginObjectDescIdentifier(
//				const OpenViBE::CIdentifier& rPreviousIdentifier,
//				const OpenViBE::CIdentifier& rBaseClassIdentifier) const;

//			virtual OpenViBE::boolean canCreatePluginObject(
//				const OpenViBE::CIdentifier& rClassIdentifier);
//			virtual const OpenViBE::Plugins::IPluginObjectDesc* getPluginObjectDesc(
//				const OpenViBE::CIdentifier& rClassIdentifier) const;
//			virtual const OpenViBE::Plugins::IPluginObjectDesc* getPluginObjectDescCreating(
//				const OpenViBE::CIdentifier& rClassIdentifier) const;

//			virtual OpenViBE::CIdentifier getPluginObjectHashValue(
//				const OpenViBE::CIdentifier& rClassIdentifier) const;
//			virtual OpenViBE::CIdentifier getPluginObjectHashValue(
//				const OpenViBE::Plugins::IBoxAlgorithmDesc& rBoxAlgorithmDesc) const;
//			virtual OpenViBE::boolean isPluginObjectFlaggedAsDeprecated(
//				const OpenViBE::CIdentifier& rClassIdentifier) const;

//			virtual OpenViBE::Plugins::IPluginObject* createPluginObject(
//				const OpenViBE::CIdentifier& rClassIdentifier);
//			virtual OpenViBE::boolean releasePluginObject(
//				OpenViBE::Plugins::IPluginObject* pPluginObject);

//			virtual OpenViBE::Plugins::IAlgorithm* createAlgorithm(
//				const OpenViBE::CIdentifier& rClassIdentifier,
//				const OpenViBE::Plugins::IAlgorithmDesc** ppAlgorithmDesc);
//			virtual OpenViBE::Plugins::IAlgorithm* createAlgorithm(
//				const OpenViBE::Plugins::IAlgorithmDesc& rAlgorithmDesc);
//			virtual OpenViBE::Plugins::IBoxAlgorithm* createBoxAlgorithm(
//				const OpenViBE::CIdentifier& rClassIdentifier,
//				const OpenViBE::Plugins::IBoxAlgorithmDesc** ppBoxAlgorithmDesc);

			_IsDerivedFromClass_Final_(OpenViBE::Kernel::IMetaboxManager, OVK_ClassId_Kernel_Metabox_MetaboxManager)

		protected:

//			template <class IPluginObjectT, class IPluginObjectDescT>
//			IPluginObjectT* createPluginObjectT(
//				const OpenViBE::CIdentifier& rClassIdentifier,
//				const IPluginObjectDescT** ppPluginObjectDescT);

		protected:

//			std::vector < OpenViBE::Kernel::IPluginModule* > m_vPluginModule;
//			std::map < OpenViBE::Plugins::IPluginObjectDesc*, OpenViBE::Kernel::IPluginModule* > m_vPluginObjectDesc;
//			std::map < OpenViBE::Plugins::IPluginObjectDesc*, std::vector<OpenViBE::Plugins::IPluginObject* > > m_vPluginObject;
		};
	};
};

#endif // __OpenViBEKernel_Kernel_Metabox_CMetaboxManager_H__
