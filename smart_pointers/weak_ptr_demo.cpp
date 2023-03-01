#include <vector>
#include <memory>

class Subscriber {

};

class SubscribeManager {
public:
    void publish() {
        for (const auto& iter : m_subscribers) {
            if (!iter.expired()) {
                //do sth
            }
        }
    }
private:
    std::vector<std::weak_ptr<Subscriber>> m_subscribers;    
};