#pragma once

enum class AttenuationType;

class SoundSource;

class SoundSourceInterface
{
public:
	virtual void setNewPosition(float X, float Y) = 0;
	virtual void setLwa(float newLwa) = 0;
	virtual void setIsOccludable(bool newIsOccludable) = 0;
	virtual void setAttenuationCurve(AttenuationType newAttenuation) = 0;
	virtual void setMaxDistance(float newMaxDistance) = 0;
	virtual void printInfo() const = 0;
	virtual void printDetailedInfo() const = 0;
	virtual float getCurrentAttenuation() const = 0;
	virtual int getId() const = 0;
	virtual float getLwa() const = 0;
	virtual AttenuationType getAttenuationType() const = 0;
	virtual float getMaxDistance() const = 0;
	virtual bool ifOccluded() const = 0;
	virtual bool ifOccludable() const = 0;
	virtual bool ifVirtual() const = 0;
};