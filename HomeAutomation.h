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
        std::shared_ptr<PopupMenu> rootMenu = std::make_shared<PopupMenu>("Ȩ ������̼� �޴�");
        std::shared_ptr<PopupMenu> applianceMenu = std::make_shared<PopupMenu>("���� ��ǰ ����");
        std::shared_ptr<PopupMenu> controlAllMenu = std::make_shared<PopupMenu>("��ü ������ǰ ����");
        
        applianceMenu->add(std::make_shared<MenuItem>("���� ��ǰ ����", 1, std::bind(&HomeAutomation::listDisplayAppliance, this)));
        applianceMenu->add(std::make_shared<MenuItem>("���� ��ǰ ���", 2, std::bind(&HomeAutomation::addAppliance, this)));
        applianceMenu->add(std::make_shared<MenuItem>("���� ��ǰ�� �޴��� ��ȣ �߰�", 3, std::bind(&HomeAutomation::addPhoneNumberToAppliance, this)));
        applianceMenu->add(std::make_shared<MenuItem>("���� ��ǰ ����", 4, std::bind(&HomeAutomation::controlAppliance, this)));
        applianceMenu->add(std::make_shared<MenuItem>("��ü ������ǰ ���� �ѱ�", 5, std::bind(&HomeAutomation::turnAllAppliancesOn, this)));
        applianceMenu->add(std::make_shared<MenuItem>("��ü ������ǰ ���� ����", 6, std::bind(&HomeAutomation::turnAllAppliancesOff, this)));
        applianceMenu->add(std::make_shared<MenuItem>("���� ��ǰ ����", 7, std::bind(&HomeAutomation::deleteAppliance, this)));
        applianceMenu->add(std::make_shared<MenuItem>("��ü ���� ��ǰ ���� ���� �� �Һ� ���� Ȯ��", 8, std::bind(&HomeAutomation::powerDisplay, this)));

        rootMenu->add(applianceMenu);

        rootMenu->command();
    }
};
#endif
