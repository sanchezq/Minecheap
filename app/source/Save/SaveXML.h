#pragma once

#include <tinyxml2.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "World.h"
#include "Maths/vec3.h"

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

class SaveXML
{
public:
	SaveXML() = default;
	~SaveXML() = default;

	static void CheckError(const int xmlErrorNb);

	// Export
	int ExportSave(const char* saveName, const World& world);
	
	// Import
	int ImportSave(const char* saveName, World& world);
	void LoadSavesName();

private:
	// Export
	void AddIntElement(tinyxml2::XMLDocument& xmlDoc, tinyxml2::XMLElement* const parent, const char* name, const int value);
	void AddFloatElement(tinyxml2::XMLDocument& xmlDoc, tinyxml2::XMLElement* const parent, const char* name, const float value);
	void AddVec3fElement(tinyxml2::XMLDocument& xmlDoc, tinyxml2::XMLElement* const parent, const char* name, const float x, const float y, const float z);
	void AddSlotElement(tinyxml2::XMLDocument& xmlDoc, tinyxml2::XMLElement* const parent, const int id, const int quantity);
	
	// Import
	int ReadVec3f(tinyxml2::XMLElement* const parent, const char* name, Core::Maths::vec3& target);
	std::vector<std::string> m_savesList;
};