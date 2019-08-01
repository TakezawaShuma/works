
#include "Utility.h"


namespace Utility
{
	Collistions* Collistions::m_instans = nullptr;

	Collistions::Collistions()
	{
	}

	Collistions::~Collistions()
	{
	}
	Collistions* Collistions::GetInstans()
	{
		if (m_instans == nullptr) { m_instans = new Collistions(); }
		return m_instans;
	}

}