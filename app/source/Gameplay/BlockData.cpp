#include "BlockData.h"


BlockData::BlockData(const BlockID id, const BlockClassType classType, const BlockDestructType destructType, const float durability, const bool isGravity, const float fluidity, const unsigned int distance, const float updateTime) :
	m_ID(id), m_classType(classType), m_destructType(destructType), m_durability(durability), m_isGravity(isGravity), m_fluidity(fluidity), m_distance(distance), m_updateTime(updateTime)
{ }
