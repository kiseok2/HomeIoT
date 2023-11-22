#ifndef HOMEAUTOMATION_H
#define HOMEAUTOMATION_H

#include "Menu.h"
#include "Appliance.h"
#include "SMSManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <conio.h>
#include <iomanip>

#define APPLIANCE_MAX_CNT 20

using namespace std::placeholders;

class HomeAutomation {

    std::vector<std::shared_ptr<Appliance>> applianceArray;
    SMSManager smsManager;

public:
    HomeAutomation();
    ~HomeAutomation();

    void listDisplayAppliance() const;
    void addAppliance();
    void deleteAppliance();
    void controlAppliance();
    void powerDisplay() const;
    void turnAllAppliancesOn();
    void turnAllAppliancesOff();
    void addPhoneNumberToAppliance();

    void init_menu() {
        std::shared_ptr<PopupMenu> rootMenu = std::make_shared<PopupMenu>("홈 오토메이션 메뉴");
        std::shared_ptr<PopupMenu> applianceMenu = std::make_shared<PopupMenu>("가전 제품 관리");
        std::shared_ptr<PopupMenu> controlAllMenu = std::make_shared<PopupMenu>("전체 가전제품 제어");
        
        applianceMenu->add(std::make_shared<MenuItem>("가전 제품 상태", 1, std::bind(&HomeAutomation::listDisplayAppliance, this)));
        applianceMenu->add(std::make_shared<MenuItem>("가전 제품 등록", 2, std::bind(&HomeAutomation::addAppliance, this)));
        applianceMenu->add(std::make_shared<MenuItem>("가전 제품에 휴대폰 번호 추가", 3, std::bind(&HomeAutomation::addPhoneNumberToAppliance, this)));
        applianceMenu->add(std::make_shared<MenuItem>("가전 제품 제어", 4, std::bind(&HomeAutomation::controlAppliance, this)));
        applianceMenu->add(std::make_shared<MenuItem>("전체 가전제품 전원 켜기", 5, std::bind(&HomeAutomation::turnAllAppliancesOn, this)));
        applianceMenu->add(std::make_shared<MenuItem>("전체 가전제품 전원 끄기", 6, std::bind(&HomeAutomation::turnAllAppliancesOff, this)));
        applianceMenu->add(std::make_shared<MenuItem>("가전 제품 삭제", 7, std::bind(&HomeAutomation::deleteAppliance, this)));
        applianceMenu->add(std::make_shared<MenuItem>("전체 가전 제품 전원 상태 및 소비 전력 확인", 8, std::bind(&HomeAutomation::powerDisplay, this)));

        rootMenu->add(applianceMenu);

        rootMenu->command();
    }
};
#endif
