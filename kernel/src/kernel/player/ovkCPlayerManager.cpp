#include "ovkCPlayerManager.h"
#include "ovkCPlayer.h"

#include "../../ovk_tools.h"

#include <system/ovCMath.h>

using namespace OpenViBE;
using namespace Kernel;
using namespace std;

CPlayerManager::CPlayerManager(const IKernelContext& rKernelContext)
	:TKernelObject<IPlayerManager>(rKernelContext)
{
}

boolean CPlayerManager::createPlayer(
	CIdentifier& rPlayerIdentifier)
{
	rPlayerIdentifier=getUnusedIdentifier();
	m_vPlayer[rPlayerIdentifier]=new CPlayer(getKernelContext());
	return true;
}

boolean CPlayerManager::releasePlayer(
	const CIdentifier& rPlayerIdentifier)
{
	map<CIdentifier, CPlayer*>::iterator itPlayer;
	itPlayer=m_vPlayer.find(rPlayerIdentifier);

	OV_ERROR_UNLESS_KRF(
		itPlayer != m_vPlayer.end(),
		"Player release failed, identifier :" << rPlayerIdentifier.toString(),
		ErrorType::ResourceNotFound
	);

	delete itPlayer->second;
	m_vPlayer.erase(itPlayer);
	return true;
}

IPlayer& CPlayerManager::getPlayer(
	const CIdentifier& rPlayerIdentifier)
{
	map<CIdentifier, CPlayer*>::const_iterator itPlayer;
	itPlayer=m_vPlayer.find(rPlayerIdentifier);

	// use fatal here because the signature does not allow
	// proper checking
	OV_FATAL_UNLESS_K(
		itPlayer != m_vPlayer.end(),
		"Trying to retrieve non existing player with id " << rPlayerIdentifier.toString(),
		ErrorType::ResourceNotFound
	);

	// use a fatal here because failing to meet this invariant
	// means there is a bug in the manager implementation
	OV_FATAL_UNLESS_K(
		itPlayer->second,
		"Null player found for id " << rPlayerIdentifier.toString(),
		ErrorType::BadValue
	);

	return *itPlayer->second;
}

CIdentifier CPlayerManager::getNextPlayerIdentifier(
	const CIdentifier& rPreviousIdentifier) const
{
	return getNextIdentifier < CPlayer* >(m_vPlayer, rPreviousIdentifier);
}

CIdentifier CPlayerManager::getUnusedIdentifier(void) const
{
	uint64 l_ui64Identifier=System::Math::randomUInteger64();
	CIdentifier l_oResult;
	map<CIdentifier, CPlayer*>::const_iterator i;
	do
	{
		l_ui64Identifier++;
		l_oResult=CIdentifier(l_ui64Identifier);
		i=m_vPlayer.find(l_oResult);
	}
	while(i!=m_vPlayer.end() || l_oResult==OV_UndefinedIdentifier);
	return l_oResult;
}
