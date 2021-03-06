#include "ovkCKernelObjectFactory.h"

#include "ovkCConfigurable.h"

#include "plugins/ovkCPluginModule.h"

#include <string>
#include <algorithm>

using namespace std;
using namespace OpenViBE;
#define boolean bool

#define create(rcid,cid,sptr,cl) \
	if(rcid==cid) \
	{ \
		sptr=new cl(getKernelContext()); \
		if(sptr) \
		{ \
			m_oCreatedObjects.push_back(sptr); \
		} \
	}

Kernel::CKernelObjectFactory::CKernelObjectFactory(const Kernel::IKernelContext& rKernelContext)
	:TKernelObject<IKernelObjectFactory>(rKernelContext)
{
}

IObject* Kernel::CKernelObjectFactory::createObject(
	const CIdentifier& rClassIdentifier)
{
	IObject* l_pResult=NULL;

	create(rClassIdentifier, OV_ClassId_Kernel_Plugins_PluginModule,              l_pResult, Kernel::CPluginModule);

	create(rClassIdentifier, OV_ClassId_Kernel_Configurable,                      l_pResult, Kernel::CConfigurable);

	OV_ERROR_UNLESS_KRN(
		l_pResult,
		"Unable to allocate object with class id " << rClassIdentifier.toString(),
		ErrorType::BadAlloc
	);

	return l_pResult;
}

boolean Kernel::CKernelObjectFactory::releaseObject(
	IObject* pObject)
{
	if(!pObject)
	{
		return true;
	}

	CIdentifier l_rClassIdentifier;
	l_rClassIdentifier=pObject->getClassIdentifier();

	vector<IObject*>::iterator i;
	i=find(m_oCreatedObjects.begin(), m_oCreatedObjects.end(), pObject);

	OV_ERROR_UNLESS_KRF(
		i != m_oCreatedObjects.end(),
		"Can not release object with final class id " << l_rClassIdentifier.toString() << " - it is not owned by this fatory",
		ErrorType::ResourceNotFound
	);

	m_oCreatedObjects.erase(i);
	delete pObject;

	this->getLogManager() << LogLevel_Debug << "Released object with final class id " << l_rClassIdentifier << "\n";

	return true;
}
