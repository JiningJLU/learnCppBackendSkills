#include <iostream>
#include <map>
#include <memory>

class ChatDialog{
public:
    ChatDialog() {
        std::cout << "ChatDialog constructor" << std::endl;
    }   
    ~ChatDialog() {
        std::cout << "ChatDialog destructor" << std::endl;
    }  
    void active() {
        // 实现省略
    }
};

std::map<int64_t, std::unique_ptr<ChatDialog>> m_ChatDialogs;

void onDoubleClickFriendItem3(int64_t userId) {
    auto [iter, inserted] = m_ChatDialogs.try_emplace(userId, nullptr);
    if (inserted) {
        auto spChatDialog = std::make_unique<ChatDialog>();
        iter->second = std::move(spChatDialog);
    }
    iter->second->active();
}

int main() {
    onDoubleClickFriendItem3(906106643L);
    onDoubleClickFriendItem3(906106644L);
    onDoubleClickFriendItem3(906106643L);
}