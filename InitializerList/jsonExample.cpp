/*
    在本例中，可以达到这样的效果:
    json array_not_object = json::array({{"currency", "USD"}, {"value", 42.99}});
*/

#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>

enum class jsonType {
    jsonTypeNull,
    jsonTypeInt,
    jsonTypeLong,
    jsonTypeDouble,
    jsonTypeBool,
    jsonTypeString,
    jsonTypeArray,
    jsonTypeObject
};

struct jsonNode {
    jsonNode(const char* key, const char* value) : m_type(jsonType::jsonTypeDouble), m_key(key), m_value(value) {
        std::cout << "jsonNode constructor1 called." << std::endl;
    }
    jsonNode(const char* key, double value) : m_type(jsonType::jsonTypeDouble), m_key(key), m_value(std::to_string(value)) {
        std::cout << "jsonNode constructor2 called." << std::endl;
    }
    jsonType m_type;
    std::string m_key;
    std::string m_value;
};

class json{
private:
    std::vector<jsonNode> m_nodes;
    static json m_json;
public:
    static json& array(std::initializer_list<jsonNode> nodes) {
        m_json.m_nodes.clear();
        m_json.m_nodes.insert(m_json.m_nodes.end(), nodes.begin(), nodes.end());
        std::cout << "json::array() called." << std::endl;
        return m_json;
    }

    json() {}
    ~json() {}

    std::string toString() {
        size_t size = m_nodes.size();
        for (size_t i=0; i<size; i++) {
            switch (m_nodes[i].m_type)
            {
                // 根据类型组装成一个Json字符串, 代码省略
            case jsonType::jsonTypeDouble:
                break;
            
            default:
                break;
            }
        }
        return "";
    }
};

json json::m_json;

int main() {
    json array_not_object = json::array({{"currency", "USD"}, {"value", 42.99}});
    return 0;
}