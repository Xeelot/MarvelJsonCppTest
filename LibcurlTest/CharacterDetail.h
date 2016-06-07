#pragma once
#include <cstdlib>
#include <vector>
#include "IJsonSerializable.h"

class CharacterDetail : public IJsonSerializable
{
public:
   CharacterDetail();
   virtual ~CharacterDetail();
   virtual void Serialize(Json::Value& root);
   virtual void Deserialize(Json::Value& root);

private:
   std::string m_status;
   int m_offset;
   int m_limit;
   int m_total;
   int m_count;
   std::vector<int> m_id;
   std::vector<std::string> m_name;
   std::vector<std::string> m_description;
   std::vector<std::string> m_thumbPath;
   std::vector<std::string> m_thumbExtension;
   std::vector<std::string> m_characterUri;
   std::vector<int> m_comicsAvailable;
   std::vector<int> m_comicsReturned;
   std::vector<std::string> m_collectionUri;
   std::vector<std::vector<std::string>> m_comicUri;
   std::vector<std::vector<std::string>> m_comicName;
};

