#include "SoundSourceCalculator.h"

#include "Receiver.h"
#include "Obstacle.h"
#include "SoundSource.h"
#include "ListOfSources.h"
#include "ListOfReceivers.h"
#include "ListOfObstacles.h"
#include "ErrorLogging.h"

SoundSourceCalculator* soundSourceCalculator;

void SoundSourceCalculator::setAllVirtualizations(Receiver* activeReceiverPtr)
{
	int nrOfSources = listOfSourcesPtr->getSourcesAmount();
	for (int i = 0; i < nrOfSources; i++)
	{
		SoundSource* sourcePtr = listOfSourcesPtr->getPtrByNr(i);
		bool virtualize = shouldBeVirtual(sourcePtr, activeReceiverPtr);
		sourcePtr->setIsVirtualized(virtualize);
	}
}

void SoundSourceCalculator::clearAllListsOfOccluders()
{
	int nrOfSources = listOfSourcesPtr->getSourcesAmount();
	for (int i = 0; i < nrOfSources; i++)
	{
		listOfSourcesPtr->getPtrByNr(i)->clearOccluders();
	}
}

void SoundSourceCalculator::calculateAllAttenuations(Receiver* activeReceiverPtr)
{
	const int nrOfSources = listOfSourcesPtr->getSourcesAmount();
	for (int i = 0; i < nrOfSources; i++)
	{
		SoundSource* soundSourcePtr = listOfSourcesPtr->getPtrByNr(i);
		if (soundSourcePtr->ifVirtual() == true)
		{
			continue;
		}
		float distAttenuation = distanceAttenuation(soundSourcePtr, activeReceiverPtr);
		if (soundSourcePtr->ifOccludable() != true)
		{
			soundSourcePtr->setAttenuation(distAttenuation);
			soundSourcePtr->setIsOccluded(false);
			soundSourcePtr->clearOccluders();
		}
		else
		{
			float occlAttenuation = calculateOcclusion(soundSourcePtr, activeReceiverPtr);
			soundSourcePtr->setAttenuation(distAttenuation + occlAttenuation);
		}
	}
}

bool SoundSourceCalculator::shouldBeVirtual(SoundSource* source, Receiver* receiver) const
{
	float receiverX = receiver->getPosX();
	float receiverY = receiver->getPosY();
	float sourceX = source->getPosX();
	float sourceY = source->getPosY();
	float squaredDistance = BasicMath::squaredDistance(receiverX, receiverY, sourceX, sourceY);
	return (squaredDistance > (source->getMaxDistance() * source->getMaxDistance()));
}

float SoundSourceCalculator::distanceAttenuation(SoundSource* sourcePtr, Receiver* activeReceiverPtr) const
{
	if (sourcePtr->getAttenuationType() == AttenuationType::NoAttenuation)
	{
		return 0;
	}

	float receiverX = activeReceiverPtr->getPosX();
	float receiverY = activeReceiverPtr->getPosY();
	float sourceX = sourcePtr->getPosX();
	float sourceY = sourcePtr->getPosY();

	float sqDist = BasicMath::squaredDistance(receiverX, receiverY, sourceX, sourceY);
	float result = 0;

	switch (sourcePtr->getAttenuationType())
	{
	case AttenuationType::PointSource:
		result = 10 * log10f(4 * BasicMath::PI*sqDist) > 0 ? 10 * log10f(4 * BasicMath::PI*sqDist) : 0;
		break;
	case AttenuationType::LineSource:
		result = 10 * log10f(2 * BasicMath::PI*sqDist) > 0 ? 10 * log10f(2 * BasicMath::PI*sqDist) : 0;
		break;
	default:
		LOG_ERROR("WRONG ATTENUATION TYPE, CANT CALCULATE DISTANCE ATTENUATION");
		break;
	}
	return result;
}

float SoundSourceCalculator::calculateOcclusion(SoundSource* sourcePtr, Receiver* activeReceiverPtr) const
{
	float calculatedOcclusion = 0;
	int nrOfObstacles = listOfObstaclesPtr->getObstaclesAmount();
	sourcePtr->setIsOccluded(false);
	for (int i = 0; i < nrOfObstacles; i++)
	{
		Obstacle* obstaclePtr = listOfObstaclesPtr->getPtrByNr(i);
		bool isSourceOccludedByThisObstacle = IsOccludedByObstacle(sourcePtr, obstaclePtr, activeReceiverPtr);
		if (isSourceOccludedByThisObstacle)
		{
			sourcePtr->addOccluder(obstaclePtr);
			float occluderDampening = obstaclePtr->getDampening();
			calculatedOcclusion = calculatedOcclusion + occluderDampening;
		}
	}
	return calculatedOcclusion;
}


bool SoundSourceCalculator::IsOccludedByObstacle(SoundSource* sourcePtr, Obstacle const * obstacPtr, Receiver* activeReceiverPtr) const
{
	float receiverX = activeReceiverPtr->getPosX();
	float receiverY = activeReceiverPtr->getPosY();
	float sourceX = sourcePtr->getPosX();
	float sourceY = sourcePtr->getPosY();
	float obstacleX1 = obstacPtr->getPosX1();
	float obstacleY1 = obstacPtr->getPosY1();
	float obstacleX2 = obstacPtr->getPosX2();
	float obstacleY2 = obstacPtr->getPosY2();


	if ((receiverX - sourceX) < 0.01 && (receiverX - sourceX) > -0.01) // source i listener pionowe
	{
		float xIntersection = (receiverX + sourceX) / 2;

		if ((obstacleX1 - obstacleX2) < 0.01 && (obstacleX1 - obstacleX2) > -0.01) // obstacle pionowe
		{
			float xIntersection2 = (obstacleX1 + obstacleX2) / 2;
			if ((xIntersection2 - xIntersection) < 0.01 && (xIntersection2 - xIntersection) > -0.01)
			{
				float ymin[2], ymax[2];
				BasicMath::MinMax(ymin[0], ymax[0], receiverY, sourceY);
				BasicMath::MinMax(ymin[1], ymax[1], obstacleY1, obstacleY2);
				if ((ymin[0] > ymin[1] && ymin[0] < ymax[1]) || (ymax[0] > ymin[1] && ymax[0] < ymax[1])
					|| (ymin[1] > ymin[0] && ymin[1] < ymax[0]) || (ymax[1] > ymin[0] && ymax[1] < ymax[0]))
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
		{
			BasicMath::Line obstacleLine = obstacPtr->ObstacleLine();
			float xmin, xmax;
			BasicMath::MinMax(xmin, xmax, obstacleX1, obstacleX2);
			if (xIntersection > xmin && xIntersection < xmax)
			{
				float ymin, ymax;
				BasicMath::MinMax(ymin, ymax, receiverY, sourceY);
				float yIntersection = xIntersection * obstacleLine.a + obstacleLine.b;
				if (yIntersection > ymin && yIntersection < ymax)
					return true;
				else
					return false;
			}
			else
				return false;
		}
	}
	else if ((obstacleX1 - obstacleX2) < 0.01 && (obstacleX1 - obstacleX2) > -0.01)  // obstacle pionowe
	{
		float xIntersection = (obstacleX1 + obstacleX2) / 2;
		float xmin, xmax;
		BasicMath::MinMax(xmin, xmax, receiverX, sourceX);
		if (xIntersection > xmin && xIntersection < xmax)
		{
			BasicMath::Line sourceRaycast = raycast(sourcePtr, activeReceiverPtr);
			float ymin, ymax;
			BasicMath::MinMax(ymin, ymax, obstacleY1, obstacleY2);
			float yIntersection = xIntersection * sourceRaycast.a + sourceRaycast.b;
			if (yIntersection > ymin && yIntersection < ymax)
				return true;
			else
				return false;
		}
		else
			return false;
	}

	else // nic nie jest pionowe
	{
		BasicMath::Line sourceRaycast = raycast(sourcePtr, activeReceiverPtr);
		BasicMath::Line obstacleLine = obstacPtr->ObstacleLine();
		float intersection = (obstacleLine.b - sourceRaycast.b) / (sourceRaycast.a - obstacleLine.a);
		float xmin[2];
		float xmax[2];
		BasicMath::MinMax(xmin[0], xmax[0], receiverX, sourceX);
		BasicMath::MinMax(xmin[1], xmax[1], obstacleX1, obstacleX2);

		if ((intersection > xmin[0] - 0.01) && (intersection > xmin[1] - 0.01) && (intersection < xmax[0] + 0.01)
			&& (intersection < xmax[1] + 0.01))
		{
			return true;
		}
		else
			return false;
	}
}

BasicMath::Line SoundSourceCalculator::raycast(SoundSource* sourcePtr, Receiver* activeReceiverPtr) const
{
	float receiverX = activeReceiverPtr->getPosX();
	float receiverY = activeReceiverPtr->getPosY();
	float sourceX = sourcePtr->getPosX();
	float sourceY = sourcePtr->getPosY();

	BasicMath::Line line((sourceY - receiverY) / (sourceX - receiverX),
		receiverY - (receiverX*(sourceY - receiverY) / (sourceX - receiverX)));
	return line;
}