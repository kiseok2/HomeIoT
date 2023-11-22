#include "Menu.h" 
#include "Appliance.h" // max_size 변수 가져오기 위함
#include <iostream>
#include <conio.h>

BaseMenu::BaseMenu(const std::string& s) : title(s) {}

BaseMenu::~BaseMenu() {}

std::string BaseMenu::get_title() const {
    return title;
}

PopupMenu::PopupMenu(const std::string& s) : BaseMenu(s) {}

void PopupMenu::add(std::shared_ptr<BaseMenu> p) {
    v.push_back(p);
}

void PopupMenu::command() {
    while (true) {
        system("cls");
        std::cout << "\n================== 홈 오토메이션 메뉴 ===================\n";
        int sz = v.size();
        for (int i = 0; i < sz; i++) {
            std::cout << i + 1 << ". " << v[i]->get_title() << std::endl;
        }
        std::cout << sz + 1 << ". 종료\n";
        std::cout << "=========================================================\n";

        int cmd;
        std::cout << "메뉴를 선택하세요 >> ";
        std::cin >> cmd;
        if (std::cin.fail()) {
            std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
            getch();
        }

        if (cmd == sz + 1)
            break;

        if (cmd < 1 || cmd > sz + 1)
            continue;

        v[cmd - 1]->command();
    }
}

MenuItem::MenuItem(const std::string& s, int n, std::function<void()> h)
    : BaseMenu(s), id(n), handler(h) {}

void MenuItem::command() {
    if (handler != nullptr)
        handler();
}
