#pragma once
#include "SoundAPI.h"
#include "BaseClassesFunctions.h"
#include "SoundSourceInterface.h"

#include <vector>

enum class AttenuationType
{ 
	PointSource = 0, 
	LineSource, 
	NoAttenuation 
};

struct SoundSourceDescriptor
{
	float m_x = 0;
	float m_y = 0;
	float m_Lwa = 90;
	float m_maxDistance = 100;
	bool m_isOccludable = true;
	AttenuationType m_attenuationType = AttenuationType::PointSource;
	int m_id = 0;

	SoundSourceDescriptor(float x, float y, float Lwa, float maxDistance, bool isOccludable,
		AttenuationType attenuationType, int Id)
		: m_x(x), m_y(y), m_Lwa(Lwa), m_maxDistance(maxDistance), m_isOccludable(isOccludable),
		m_attenuationType(attenuationType), m_id(Id) {};

	SoundSourceDescriptor(float x, float y, float Lwa, float maxDistance, bool isOccludable,
		AttenuationType attenuationType)
		: m_x(x), m_y(y), m_Lwa(Lwa), m_maxDistance(maxDistance), m_isOccludable(isOccludable),
		m_attenuationType(attenuationType), m_id(0) {};

	SoundSourceDescriptor() {};
	~SoundSourceDescriptor() {};
};

class Obstacle;
class ListOfSources;
class Receiver;
class SoundSourceCalculator;

class SOUND_API SoundSource : public BasicMath::Point, public SoundSourceInterface
{
public:
	void setNewPosition(float newX, float newY) override;
	void setLwa(float newLwa) override;
	void setIsOccludable(bool newIsOccludable) override;
	void setAttenuationCurve(AttenuationType newAttenuation) override;
	void setMaxDistance(float newMaxDistance) override;
	void printInfo() const override;
	void printDetailedInfo() const override; 
	void setAttenuation(float newAttenuation);
	void setIsVirtualized(bool newIsVirtualized);
	void setIsOccluded(bool isOccluded);
	void addOccluder(Obstacle* occluder);
	void clearOccluders();
	void printOccluders() const;

	inline float getCurrentAttenuation() const override;
	int getId() const override { return m_id; };
	float getLwa() const override { return m_Lwa; }
	AttenuationType getAttenuationType() const override { return m_attenuationType; }
	float getMaxDistance() const override { return m_maxDistance; }
	bool ifOccluded() const override { return m_isOccluded; }
	bool ifOccludable() const override { return m_isOccludable; }
	bool ifVirtual() const override { return m_isVirtualized; }

	bool operator==(SoundSource& const otherSource) const;

	static const int memoryPerObject = (4 * sizeof(float)) + sizeof(bool) + sizeof(AttenuationType);	
	
private:

	SoundSource(SoundSourceDescriptor& sourceDescriptor);
	~SoundSource();

	int m_id;
	AttenuationType m_attenuationType;	
	float m_Lwa;
	float m_maxDistance;
	bool m_isOccludable;
	bool m_isVirtualized = false;
	bool m_isOccluded = false;
	float m_currentAttenuation = 0;

	friend class ListOfSources;
};