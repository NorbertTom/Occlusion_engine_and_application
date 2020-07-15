#include "SoundSource.h"
#include "Receiver.h"
#include "Obstacle.h"
#include "ErrorLogging.h"

SoundSource::SoundSource(SoundSourceDescriptor& sourceDescriptor) : BasicMath::Point(sourceDescriptor.m_x, sourceDescriptor.m_y),
m_Lwa(sourceDescriptor.m_Lwa), m_attenuationType(sourceDescriptor.m_attenuationType), m_maxDistance(sourceDescriptor.m_maxDistance),
m_isOccludable(sourceDescriptor.m_isOccludable), m_id(sourceDescriptor.m_id)
{
}

SoundSource::~SoundSource()
{
}

void SoundSource::setNewPosition(float newX, float newY)
{
	setPosX(newX);
	setPosY(newY);
}

void SoundSource::setLwa(float newLwa) { m_Lwa = newLwa; }

void SoundSource::setIsOccludable(bool newIsOccludable) { m_isOccludable = newIsOccludable; }

void SoundSource::setAttenuationCurve(AttenuationType newAttenuation) { m_attenuationType = newAttenuation; }

void SoundSource::setMaxDistance(float newMaxDistance) { m_maxDistance = newMaxDistance; }

float SoundSource::getCurrentAttenuation() const {	return m_currentAttenuation; }

void SoundSource::printInfo() const
{
	std::cout << "SoundSource ID: " << m_id << ", Position: " << getPosX() << ", "
		<< getPosY() << ", Current attenuation: " << m_currentAttenuation << "dB; is occluded: "
		<< m_isOccluded << "\n";
}

void SoundSource::printDetailedInfo() const
{
	std::cout << "SoundSource ID: " << m_id << ", Position: " << getPosX() << ", "
		<< getPosY() << "; Lwa = " << m_Lwa << "dB, Attenuation type: " <<
		static_cast<int>(m_attenuationType) << ", Max Distance: " << m_maxDistance <<
		", Current attenuation: " << m_currentAttenuation << "dB; Is Occludable: "
		<< m_isOccludable << ", is occluded: " << m_isOccluded <<
		", is virtualized: " << m_isVirtualized << "\n";
}

void SoundSource::setAttenuation(float newAttenuation)
{
	m_currentAttenuation = newAttenuation;
}

void SoundSource::setIsVirtualized(bool newIsVirtualized)
{
	m_isVirtualized = newIsVirtualized;
	m_currentAttenuation = 120;
}

void SoundSource::setIsOccluded(bool isOccluded)
{
	m_isOccluded = isOccluded;
}

void SoundSource::addOccluder(Obstacle* occluder)
{
	setIsOccluded(true);
//	m_listOfOccluders.push_back(occluder);
}

void SoundSource::clearOccluders()
{
/*	if (m_listOfOccluders.size() > 0)
	{
		m_listOfOccluders.clear();
	}
*/}

void SoundSource::printOccluders() const
{
/*	const int nrOfOccluders = m_listOfOccluders.size();
	for (int i = 0; i < nrOfOccluders; i++)
	{
		std::cout << "Occluder nr " << i << " of " << nrOfOccluders << " Id is: " << m_listOfOccluders[i]->getId();
	}
*/}

bool SoundSource::operator== (SoundSource& const otherSource) const
{
	bool result = false;
	if (this->getPosX() == otherSource.getPosX())
	{
		if (this->getPosY() == otherSource.getPosY())
		{
			if (this->getLwa() == otherSource.getLwa())
			{
				if (this->getMaxDistance() == otherSource.getMaxDistance())
				{
					if (this->getAttenuationType() == otherSource.getAttenuationType())
					{
						if (this->ifOccludable() == otherSource.ifOccludable())
						{
							result = true;
						}
					}
				}
			}
		}
	}
	return result;
}