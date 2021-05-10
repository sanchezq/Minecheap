#include "SaveXML.h"

#include <tinyxml2.h>
using  namespace tinyxml2;
#include <glm/glm.hpp>
#include "World.h"
#include "Player.h"

void SaveXML::CheckError(const int xmlErrorNb)
{     
    if ((XMLError)xmlErrorNb != XML_SUCCESS)
    {
        printf("Error: %i\n", (XMLError)xmlErrorNb);
    }
}

int SaveXML::ExportSave(const char* saveName, const World& world)
{
    XMLDocument xmlDoc;
    XMLError xmlError;
    // DATA NEEDED 

    // Enemies 
    // List of enemy
    // Position
    // Rotation
    // Health

    // Chests
    // List of chests
    // Chest
    // Lists of slots
    // Slot
    // Id
    // Quantity

   
    // Add save Element
    XMLNode* saveElement = xmlDoc.NewElement("save");

    xmlDoc.InsertFirstChild(saveElement);

    // Player
    {
        XMLElement* playerElement = xmlDoc.NewElement("player");

        AddVec3fElement(xmlDoc, playerElement, "position", world.m_player.GetPosition().m_x , world.m_player.GetPosition().m_y, world.m_player.GetPosition().m_z);
        AddVec3fElement(xmlDoc, playerElement, "rotation", world.m_player.GetRotation().m_x, world.m_player.GetRotation().m_y, world.m_player.GetRotation().m_z);

        XMLElement* inventoryElement = xmlDoc.NewElement("inventory");
        
        for (int nbSlot = 0; nbSlot < world.m_player.GetInventory().GetMaxStack(); nbSlot++)
        {
            AddSlotElement(xmlDoc, inventoryElement, world.m_player.GetInventory().GetObjectList()[0 + nbSlot * 2], world.m_player.GetInventory().GetObjectList()[1 + nbSlot * 2]);
        }

        playerElement->InsertEndChild(inventoryElement);

        AddFloatElement(xmlDoc, playerElement, "health", world.m_player.GetHealth());

        saveElement->InsertEndChild(playerElement);
    }

    // Enemies
    {
        int  id = 0;

        XMLElement* enemiesElement = xmlDoc.NewElement("enemies");

       // for (int nbEnemy = 0; nbEnemy < 5; nbEnemy++)
       // {
            XMLElement* enemyElement = xmlDoc.NewElement("enemy");

            AddIntElement(xmlDoc, enemyElement, "id", id);
            AddVec3fElement(xmlDoc, enemyElement, "position", world.m_zombie->GetPosition().m_x, world.m_zombie->GetPosition().m_y, world.m_zombie->GetPosition().m_z);
            AddVec3fElement(xmlDoc, enemyElement, "rotation", world.m_zombie->GetRotation().m_x, world.m_zombie->GetRotation().m_y, world.m_zombie->GetRotation().m_z);
            AddFloatElement(xmlDoc, enemyElement, "health", world.m_zombie->GetHealth());

            enemiesElement->InsertEndChild(enemyElement);
        //}

        saveElement->InsertEndChild(enemiesElement);
    }
  
    // Blocks
    {
        XMLElement* chunksElement = xmlDoc.NewElement("chunks");
        chunksElement->SetAttribute("nbChunks", world.m_nbChunks);

        for (int nbChunk = 0; nbChunk < world.m_nbChunks; nbChunk++)
        {
            XMLElement* chunkElement = xmlDoc.NewElement("chunk");

            int sqrtNbChunks = (int)sqrt(world.m_nbChunks);
            
            for (int xSizeBlock = 0; xSizeBlock < SIZE_CHUNK_X * sqrtNbChunks; xSizeBlock++)
            {
                for (int ySizeBlock = 0; ySizeBlock < SIZE_CHUNK_Y; ySizeBlock++)
                {
                    for (int zSizeBlock = 0; zSizeBlock < SIZE_CHUNK_Z * sqrtNbChunks; zSizeBlock++)
                    {
                        AddIntElement(xmlDoc, chunkElement, "block", (int)world.GetBlockType(xSizeBlock, ySizeBlock, zSizeBlock));
                    }
                }
            }
            chunksElement->InsertEndChild(chunkElement);
        }
        saveElement->InsertEndChild(chunksElement);
    }

    // Chests
    {
        int  id = 0, quantity = 64;
        float x = 0.0f, y = 0.0f, z = 0.0f;

        XMLElement* chestsElement = xmlDoc.NewElement("chests");

        for (int nbChest = 0; nbChest < 3; nbChest++)
        {
            XMLElement* chestElement = xmlDoc.NewElement("chest");

            AddVec3fElement(xmlDoc, chestElement, "position", x, y, z);
            AddVec3fElement(xmlDoc, chestElement, "rotation", x, y, z);

            XMLElement* inventoryElement = xmlDoc.NewElement("inventory");

            for (int nbSlot = 0; nbSlot < 5; nbSlot++)
            {
                AddSlotElement(xmlDoc, inventoryElement, id, quantity);
            }

            chestElement->InsertEndChild(inventoryElement);
            chestsElement->InsertEndChild(chestElement);
        }

        saveElement->InsertEndChild(chestsElement);
    }

    xmlError = xmlDoc.SaveFile(saveName);

    XMLCheckResult(xmlError);

    return XML_SUCCESS;
}

void SaveXML::AddIntElement(tinyxml2::XMLDocument& xmlDoc, tinyxml2::XMLElement* const parent, const char* name, const int value)
{
    XMLElement* intElement = xmlDoc.NewElement(name);
    intElement->SetText(value);
    parent->InsertEndChild(intElement);
}

void SaveXML::AddFloatElement(tinyxml2::XMLDocument& xmlDoc, tinyxml2::XMLElement* const parent, const char* name, const float value)
{
    XMLElement* floatElement = xmlDoc.NewElement(name);
    floatElement->SetText(value);
    parent->InsertEndChild(floatElement);
}

void SaveXML::AddVec3fElement(tinyxml2::XMLDocument& xmlDoc, tinyxml2::XMLElement* const parent, const char* name, const float x, const float y, const float z)
{
    XMLElement* vec3fElement = xmlDoc.NewElement(name);

    vec3fElement->SetAttribute("x", x);
    vec3fElement->SetAttribute("y", y);
    vec3fElement->SetAttribute("z", z);

    parent->InsertEndChild(vec3fElement);
}

void SaveXML::AddSlotElement(tinyxml2::XMLDocument& xmlDoc, tinyxml2::XMLElement* const parent, const int id, const int quantity)
{
    XMLElement* slotElement = xmlDoc.NewElement("slot");

    AddIntElement(xmlDoc, slotElement, "id", id);
    AddIntElement(xmlDoc, slotElement, "quantity", quantity);

    parent->InsertEndChild(slotElement);
}

int SaveXML::ReadVec3f(tinyxml2::XMLElement* const parent, const char* name, Core::Maths::vec3& target)
{
    XMLError xmlError;
    XMLElement* vector3f = parent->FirstChildElement(name);

    xmlError = vector3f->QueryFloatAttribute("x", &target.m_x);
    XMLCheckResult(xmlError);
    xmlError = vector3f->QueryFloatAttribute("y", &target.m_y);
    XMLCheckResult(xmlError);
    xmlError = vector3f->QueryFloatAttribute("z", &target.m_z);
    XMLCheckResult(xmlError);

    return XML_SUCCESS;
}


int SaveXML::ImportSave(const char* saveName, World& world)
{
    XMLDocument xmlDoc;
    XMLError xmlError;

    printf("Player position before import : x = %f, y = %f, z = %f \n", world.m_player.GetPosition().m_x, world.m_player.GetPosition().m_y, world.m_player.GetPosition().m_z);

    xmlError = xmlDoc.LoadFile(saveName);
    XMLCheckResult(xmlError);

    // Save element
    XMLNode* saveElement = xmlDoc.FirstChild();

    if (saveElement == nullptr)
    {
        return XML_ERROR_FILE_READ_ERROR;
    }

    {
        // Player
        XMLElement* playerElement = saveElement->FirstChildElement("player");
        if (playerElement == nullptr)
        {
            return XML_ERROR_FILE_READ_ERROR;
        }

        ReadVec3f(playerElement, "position", world.m_player.MutatePosition());
        ReadVec3f(playerElement, "rotation", world.m_player.MutateRotation());
        
        // Inventory

        XMLElement* inventoryElement = playerElement->FirstChildElement("inventory");
        XMLElement* slotElement = inventoryElement->FirstChildElement("slot");
        XMLElement* intElement = nullptr;

        int idBuffer = 0;
        int quantityBuffer = 0;
        
        int slotNb = 0;
        while (slotElement != nullptr)
        {
            intElement = slotElement->FirstChildElement("id");
            xmlError = intElement->QueryIntText(&idBuffer);
            XMLCheckResult(xmlError);

            intElement = slotElement->FirstChildElement("quantity");
            xmlError = intElement->QueryIntText(&quantityBuffer);
            XMLCheckResult(xmlError);

            world.m_player.FillOneInventorySlot(slotNb, idBuffer, quantityBuffer);

            slotElement = slotElement->NextSiblingElement("slot");
            slotNb++;
        }

        // Health
        float healthBuffer = 0.0f;
        XMLElement* healthElement = playerElement->FirstChildElement("health");
        xmlError = healthElement->QueryFloatText(&healthBuffer);
        XMLCheckResult(xmlError);
        world.m_player.SetHealth(healthBuffer);

    }

    // ENEMIES

    {
        float health = 0.0f;
        int id = 0;

        XMLElement* enemiesElement = saveElement->FirstChildElement("enemies");
        XMLElement* enemyElement = enemiesElement->FirstChildElement("enemy");
        XMLElement* enemyChildElement = nullptr;

        Resources::Mesh cube = Resources::Mesh::CreateCube();
        world.m_zombie = new Zombie(cube.GetData());

        //

        while (enemyElement != nullptr)
        {
            enemyChildElement = enemyElement->FirstChildElement("id");
            xmlError = enemyChildElement->QueryIntText(&id);
            XMLCheckResult(xmlError);

            ReadVec3f(enemyElement, "position", world.m_zombie->MutatePosition());
            ReadVec3f(enemyElement, "rotation", world.m_zombie->MutateRotation());

            enemyChildElement = enemyElement->FirstChildElement("health");
            xmlError = enemyChildElement->QueryFloatText(&health);
            XMLCheckResult(xmlError);

            
            world.m_zombie->SetHealth(health);

            enemyElement = enemyElement->NextSiblingElement("enemy");

            world.m_zombie->Update(0);
        }
    }

    // CHUNKS

    {
        XMLElement* chunksElement = saveElement->FirstChildElement("chunks");
        int nbChunks = 0;
        xmlError =  chunksElement->QueryIntAttribute("nbChunks", &nbChunks);
        XMLCheckResult(xmlError);
        world.m_nbChunks = nbChunks;
        int sqrtNbChunks = (int)sqrt(nbChunks);
        

        XMLElement* chunkElement = chunksElement->FirstChildElement("chunk");
        XMLElement* blockElement = nullptr;
        int idBuffer = 0;

        for (int chunkId = 0; chunkId < world.m_nbChunks; chunkId++)
        {
            if (chunkElement == nullptr)
            {
                break;
            }

            blockElement = chunkElement->FirstChildElement("block");

            for (int xSizeBlock = 0; xSizeBlock < SIZE_CHUNK_X * sqrtNbChunks; xSizeBlock++)
            {
                for (int ySizeBlock = 0; ySizeBlock < SIZE_CHUNK_Y ; ySizeBlock++)
                {
                    for (int zSizeBlock = 0; zSizeBlock < SIZE_CHUNK_Z * sqrtNbChunks; zSizeBlock++)
                    {
                        xmlError = blockElement->QueryIntText(&idBuffer);
                        XMLCheckResult(xmlError);
                        world.Set(xSizeBlock, ySizeBlock, zSizeBlock, (BlockID)idBuffer);
                        blockElement = blockElement->NextSiblingElement("block");
                    }
                }
            }
            chunkElement = chunkElement->NextSiblingElement("chunk");
        }
    }

    // CHESTS

    {
        float x = 0.0f, y = 0.0f, z = 0.0f;
        int id = 0, quantity = 0;

        XMLElement* chestsElement = saveElement->FirstChildElement("chests");
        XMLElement* chestElement = chestsElement->FirstChildElement("chest");
        XMLElement* vec3f = nullptr;
        XMLElement* inventory = nullptr;
        XMLElement* slot = nullptr;
        XMLElement* intElement = nullptr;

        while (chestElement != nullptr)
        {
            vec3f = chestElement->FirstChildElement("position");
            xmlError = vec3f->QueryFloatAttribute("x", &x);
            XMLCheckResult(xmlError);
            xmlError = vec3f->QueryFloatAttribute("y", &y);
            XMLCheckResult(xmlError);
            xmlError = vec3f->QueryFloatAttribute("z", &z);
            XMLCheckResult(xmlError);

            vec3f = chestElement->FirstChildElement("rotation");
            xmlError = vec3f->QueryFloatAttribute("x", &x);
            XMLCheckResult(xmlError);
            xmlError = vec3f->QueryFloatAttribute("y", &y);
            XMLCheckResult(xmlError);
            xmlError = vec3f->QueryFloatAttribute("z", &z);
            XMLCheckResult(xmlError);


            inventory = chestElement->FirstChildElement("inventory");
            slot = inventory->FirstChildElement("slot");
             
            while (slot != nullptr)
            {
                intElement = slot->FirstChildElement("id");
                xmlError = intElement->QueryIntText(&id);
                XMLCheckResult(xmlError);

                intElement = slot->FirstChildElement("quantity");
                xmlError = intElement->QueryIntText(&quantity);
                XMLCheckResult(xmlError);

                slot = slot->NextSiblingElement("slot");
            }
            chestElement = chestElement->NextSiblingElement("chest");
        }
    }

    printf("Player position after import : x = %f, y = %f, z = %f \n", world.m_player.GetPosition().m_x, world.m_player.GetPosition().m_y, world.m_player.GetPosition().m_z);

    return XML_SUCCESS;
}

void SaveXML::LoadSavesName()
{
    // TODO charger tous les noms de fichiers dans le dossier save avec le nom save-*XXXX*.xml
    m_savesList.push_back("saves/save-1.xml");
}
