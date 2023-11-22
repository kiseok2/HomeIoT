#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <functional>
#include <memory>

using namespace std::placeholders;

class BaseMenu {
public:
    BaseMenu(const std::string& s);
    virtual ~BaseMenu();
    virtual void command() = 0;
    std::string get_title() const;

private:
    std::string title;
};

class PopupMenu : public BaseMenu {
public:
    PopupMenu(const std::string& s);
    void add(std::shared_ptr<BaseMenu> p); 
    void command() override;

private:
    std::vector<std::shared_ptr<BaseMenu>> v; 
};

class MenuItem : public BaseMenu {
public:
    MenuItem(const std::string& s, int n, std::function<void()> h = nullptr);
    void command() override;

private:
    int id;
    std::function<void()> handler;
};
#endif