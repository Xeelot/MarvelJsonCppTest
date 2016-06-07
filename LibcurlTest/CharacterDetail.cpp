#include "CharacterDetail.h"
#include <iostream>

const char* ROOT_STATUS = "status";

const char* DATA = "data";
const char* DATA_OFFSET = "offset";
const char* DATA_LIMIT = "limit";
const char* DATA_TOTAL = "total";
const char* DATA_COUNT = "count";

const char* RESULTS = "results";
const char* RESULTS_ID = "id";
const char* RESULTS_NAME = "name";
const char* RESULTS_DESC = "description";
const char* RESULTS_THUMB = "thumbnail";
const char* RESULTS_THUMB_PATH = "path";
const char* RESULTS_THUMB_EXT = "extension";
const char* RESULTS_CHARURI = "resourceURI";

const char* RESULTS_COMICS = "comics";
const char* RESULTS_COMICS_AVAILABLE = "available";
const char* RESULTS_COMICS_COLLECTIONURI = "collectionURI";
const char* RESULTS_COMICS_RETURNED = "returned";

const char* RESULTS_COMICS_ITEMS = "items";
const char* RESULTS_COMICS_COMICURI = "resourceURI";
const char* RESULTS_COMICS_COMICNAME = "name";


CharacterDetail::CharacterDetail()
{
}

CharacterDetail::~CharacterDetail()
{
}

void CharacterDetail::Serialize(Json::Value& root)
{
   root[ROOT_STATUS] = m_status;
   root[DATA_OFFSET] = m_offset;
   root[DATA_LIMIT] = m_limit;
   root[DATA_TOTAL] = m_total;
   root[DATA_COUNT] = m_count;
}

void CharacterDetail::Deserialize(Json::Value& root)
{
   // Clear out vectors
   m_id.clear();
   m_name.clear();
   m_description.clear();
   m_thumbPath.clear();
   m_thumbExtension.clear();
   m_characterUri.clear();
   m_comicsAvailable.clear();
   m_collectionUri.clear();
   m_comicUri.clear();
   m_comicName.clear();

   // Read out root objects
   m_status = root.get(ROOT_STATUS, "").asString();
   // Get data object
   Json::Value data = root.get(DATA, NULL);
   if (data != NULL)
   {
      // Read out data objects
      m_offset = data.get(DATA_OFFSET, 0).asInt();
      m_limit = data.get(DATA_LIMIT, 0).asInt();
      m_total = data.get(DATA_TOTAL, 0).asInt();
      m_count = data.get(DATA_COUNT, 0).asInt();
      // Resize comic arrays by character count
      m_comicUri.resize(m_count);
      m_comicName.resize(m_count);
      // Get results object
      Json::Value results = data.get(RESULTS, NULL);
      if (results != NULL)
      {
         // Loop over results for m_count results returned
         for (Json::Value::iterator iter = results.begin(); iter != results.end(); ++iter)
         {
            // Read out result objects
            m_id.push_back(iter->get(RESULTS_ID, 0).asInt());
            m_name.push_back(iter->get(RESULTS_NAME, "").asString());
            m_description.push_back(iter->get(RESULTS_DESC, "").asString());
            m_characterUri.push_back(iter->get(RESULTS_CHARURI, "").asString());
            // Read thumbnail and parts
            Json::Value thumbnail = iter->get(RESULTS_THUMB, NULL);
            if (thumbnail != NULL)
            {
               m_thumbPath.push_back(thumbnail.get(RESULTS_THUMB_PATH, "").asString());
               m_thumbExtension.push_back(thumbnail.get(RESULTS_THUMB_EXT, "").asString());
            }
            // Get comic objects
            Json::Value comics = iter->get(RESULTS_COMICS, NULL);
            if (comics != NULL)
            {
               // Read out comic objects
               m_comicsAvailable.push_back(comics.get(RESULTS_COMICS_AVAILABLE, 0).asInt());
               m_collectionUri.push_back(comics.get(RESULTS_COMICS_COLLECTIONURI, "").asString());
               m_comicsReturned.push_back(comics.get(RESULTS_COMICS_RETURNED, "").asInt());
               // Get individual comic details
               Json::Value items = comics.get(RESULTS_COMICS_ITEMS, NULL);
               if (items != NULL)
               {
                  for (Json::Value::iterator comic = items.begin(); comic != items.end(); ++comic)
                  {
                     // Read out comic details into 2D vector
                     m_comicUri[std::distance(results.begin(), iter)].push_back(comic->get(RESULTS_COMICS_COMICURI, "").asString());
                     m_comicName[std::distance(results.begin(), iter)].push_back(comic->get(RESULTS_COMICS_COMICNAME, "").asString());
                  }
               }
            }
         }
      }
   }
}
