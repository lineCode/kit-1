#include <memory>
#include <deque>
#include <tuple>
#include <boost/algorithm/string.hpp>
#include "schema.h"

template<class Mutex>
Schema<Mutex> :: Schema(const std::shared_ptr<Meta<Mutex>>& m):
    m_pSchema(m)
{
    assert(m);
}

template<class Mutex>
template<class TMutex>
void Schema<Mutex> :: validate(const std::shared_ptr<Meta<TMutex>>& m) const
{
    // our stack for keeping track of location in tree while iterating
    std::deque<std::tuple<
        std::shared_ptr<Meta<TMutex>>,
        std::unique_lock<TMutex>,
        std::string
    >> metastack;
    
    // TODO: loop thru schema, look up required fields in m
    
    m->each([this, &metastack](
        const std::shared_ptr<Meta<TMutex>>& parent,
        MetaElement& e,
        unsigned level
    ){
        //LOGf("level: %s, key: %s", level % e.key);
        //if(boost::algorithm::starts_with(e.key, "."))
        //{
            
        //}
        
        if(e.type.id != MetaType::ID::META) {
        
            std::vector<std::string> path;
            for(auto&& d: metastack) {
                std::string key = std::get<2>(d);
                if(!key.empty())
                    path.push_back(std::get<2>(d));
            }
            path.push_back(e.key);
            if(path.empty())
                return MetaLoop::CONTINUE;
            
        //LOGf("path element: %s", boost::algorithm::join(path,"/"));
        
        std::tuple<std::shared_ptr<Meta<Mutex>>, bool> r;
        try{
            r = m_pSchema->path(path);
            auto schema_metadata = std::get<0>(r);
            bool valid_value = false;
            //LOGf("json: %s", schema_metadata->serialize(MetaFormat::JSON));
                for(auto&& val: *schema_metadata->meta(".values")) {
                    //LOGf("key: %s", e.key);
                    if(kit::any_eq(val.value, e.value)) {
                        valid_value = true;
                        break;
                    }
                }
                if(!valid_value)
                    ERROR(PARSE, "schema validation failed");
                    
            //}catch(const boost::bad_any_cast&){
            }catch(const std::out_of_range&){
            }
            
            // metastack -> path
            // path -> schema format
            // look up path->at(".values")->have(element) in schema
            // alternative: dictionary with key=".value" value
            //
            // example:
            // {
            //   "pick_a_number": {
            //     // first way
            //     ".values":[
            //        1,2,3
            //     ]
            //     // second way
            //     ".values:[
            //       {".value": 1},
            //       {".value": 3},
            //       {".value": 2}
            //     ]
            //   }
            // Should be able to mix and match the above ^
            //
            // TODO: other hints:
            //   .min/gte, .max/lte, .gt, .lt
            //
            // throw out_of_range if not
        }
        
        return MetaLoop::STEP;
    },
        (unsigned)Meta<>::EachFlag::DEFAULTS |
            (unsigned)Meta<>::EachFlag::RECURSIVE,
        &metastack
    );
}

template<class Mutex>
template<class TMutex>
void Schema<Mutex> :: add_missing_fields(std::shared_ptr<Meta<TMutex>>& m) const
{
}

template<class Mutex>
template<class TMutex>
void Schema<Mutex> :: add_required_fields(std::shared_ptr<Meta<TMutex>>& m) const
{
}

template<class Mutex>
template<class TMutex>
std::shared_ptr<Meta<TMutex>> Schema<Mutex> :: make_default() const
{
    return std::shared_ptr<Meta<TMutex>>();
}
