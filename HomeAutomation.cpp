#include "HomeAutomation.h"
#include <iostream>
#include <algorithm>

HomeAutomation::HomeAutomation() {}

HomeAutomation::~HomeAutomation() {
    applianceArray.clear();
    std::cout << "=================================================\n";
    std::cout << "Ȩ ������̼� �ý����� ����Ǿ����ϴ�." << std::endl;
    std::cout << "=================================================\n";
}

void HomeAutomation::listDisplayAppliance() const {
    std::cout << "=================================================\n";
    if (applianceArray.empty()) {
        std::cout << "��ϵ� ���� ��ǰ�� ���� �����ϴ�." << std::endl;
        std::cout << "=================================================\n";
        getch();
        return;
    }
    std::cout << "< ���� ��ǰ ��� >:" << std::endl;
    for (const std::shared_ptr<Appliance>& appliance : applianceArray) {
        appliance->display();
    }
    getch();
}

void HomeAutomation::addAppliance() {
    std::cout << "=================================================\n";
    if (applianceArray.size() >= APPLIANCE_MAX_CNT) {
        std::cout << "�� �̻� ���� ��ǰ�� �߰��� �� �����ϴ�, �ִ� ���� �����߽��ϴ�." << std::endl;
        std::cout << "=================================================\n";
        getch();
        return;
    }
    std::string name;
    int type;
    int power; // �Һ������� �Է¹��� ������ �߰��մϴ�.

    std::cout << "���� ��ǰ ������ �����ϼ��� (1. ������, 2. ���, 3. ��Ź��, 4. ����): ";
    std::cin >> type;
    if (std::cin.fail()) {
        std::cout << "���ڸ� �߸��Է��߽��ϴ�. 1 ~ 4 ���ڷ� �ٽ� �Է��ϼ���\n";
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
        getch();
    }
    else if (type < 1 || type > 4) {
        std::cout << "��ȿ���� ���� ���� ��ǰ �����Դϴ�." << std::endl;
        getch();
    }
    else {
        std::cout << "���� ��ǰ �̸��� �Է��ϼ���: ";
        std::cin >> name;

        std::cout << "���� ��ǰ�� �Һ������� �Է��ϼ���: ";
        std::cin >> power;

        if (std::cin.fail() || power <= 0) {
            std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
            getch();
        }
        else {
            ApplianceType applianceType = static_cast<ApplianceType>(type);
            //�ߺ� �̸� �˻�
            bool isNameDuplicate = std::any_of(applianceArray.begin(), applianceArray.end(),
                [&name](const std::shared_ptr<Appliance>& appliance) { return appliance->getName() == name; });

            if (!isNameDuplicate) {
                std::shared_ptr<Appliance> newAppliance;
                switch (applianceType) {
                case AIR_CONDITIONER:
                    newAppliance = std::make_shared<AirConditioner>(name);
                    break;
                case RICE_COOKER:
                    newAppliance = std::make_shared<RiceCooker>(name);
                    break;
                case WASHER:
                    newAppliance = std::make_shared<Washer>(name);
                    break;
                case LIGHT:
                    newAppliance = std::make_shared<Light>(name);
                    break;
                default:
                    std::cout << "��ȿ���� ���� ���� ��ǰ �����Դϴ�." << std::endl;
                    std::cout << "=================================================\n";
                    getch();
                    return;
                }
                newAppliance->setPowerConsumption(power);
                newAppliance->setSMSManager(&smsManager);
                applianceArray.push_back(newAppliance);
                std::cout << "=================================================\n";
                std::cout << newAppliance->getName() << " ��ǰ�� ��ϵǾ����ϴ�." << std::endl;
                std::cout << "=================================================\n";
                getch();
            }
        }
    }
}

void HomeAutomation::deleteAppliance() {
    std::cout << "=================================================\n";
    if (applianceArray.empty()) {
        std::cout << "������ ���� ��ǰ�� �����ϴ�." << std::endl;
        getch();
        std::cout << "=================================================\n";
        return;
    }
    std::cout << "���� ��ǰ ���:" << std::endl;
    for (int i = 0; i < applianceArray.size(); ++i) {
        std::cout << i + 1 << ": " << applianceArray[i]->getName() << std::endl;
    }
    int index;
    std::cout << "������ ���� ��ǰ�� �ε����� �Է��ϼ���: ";
    std::cin >> index;
    if (std::cin.fail()) {
        std::cout << "���ڸ� �߸��Է��߽��ϴ�. ���ڷ� �ٽ� �Է��ϼ���\n";
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
        getch();
    }

    if (index > 0 && index <= applianceArray.size()) {
        //delete applianceArray[index - 1];
        applianceArray.erase(applianceArray.begin() + (index - 1));
        std::cout << "���� ��ǰ�� �����߽��ϴ�." << std::endl;
    }
    else {
        std::cout << "��ȿ���� ���� �ε����Դϴ�." << std::endl;
    }
    getch();
    std::cout << "=================================================\n";
}

void HomeAutomation::controlAppliance() {
    std::cout << "=================================================\n";
    if (applianceArray.empty()) {
        std::cout << "������ ���� ��ǰ�� �����ϴ�." << std::endl;
        getch();
        std::cout << "=================================================\n";
        return;
    }

    std::cout << "���� ��ǰ ���:" << std::endl;
    for (int i = 0; i < applianceArray.size(); ++i) {
        std::cout << i + 1 << ": " << applianceArray[i]->getName() << std::endl;
    }

    int index;
    std::cout << "������ ���� ��ǰ�� �ε����� �Է��ϼ���: ";
    std::cin >> index;
    if (std::cin.fail()) {
        std::cout << "���ڸ� �߸��Է��߽��ϴ�. ���ڷ� �ٽ� �Է��ϼ���\n";
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
    }
    else if (index > 0 && index <= applianceArray.size()) {
        applianceArray[index - 1]->control();
    }
    else {
        std::cout << "��ȿ���� ���� �ε����Դϴ�." << std::endl;
    }
    getch();
}

void HomeAutomation::powerDisplay() const {
    std::cout << "=================================================\n";
    if (applianceArray.empty()) {
        std::cout << "���� ���¸� ǥ���� ���� ��ǰ�� �����ϴ�." << std::endl;
        std::cout << "=================================================\n";
        getch();
        return;
    }

    double totalPowerWatt = 0.0;
    double totalPowerKWh = 0.0;

    // �� ���� ��ǰ�� ���� �ݺ�
    //for(const Appliance* appliance : applianceArray)
    for (const std::shared_ptr<Appliance>& appliance : applianceArray) {
        //���ð��� �ִ� ���� ��ǰ�� ���ؼ��� ���
        if (appliance->getUsageTime() > 0) {
            totalPowerWatt += appliance->getPowerConsumption(); // ���� �Ҹ��� Watt ������ �ջ�
            double usageTimeHours = appliance->getUsageTime() / 3600.0; // ��� �ð��� �ð� ������ ��ȯ
            totalPowerKWh += (appliance->getPowerConsumption() * usageTimeHours) / 1000.0; // ������ �Ҹ��� kWh ������ �ջ�
        }
    }
    //���� ���� ��ǰ ON/OFF ����
    std::cout << "< ���� ��ǰ ���� �Ҹ� >:" << std::endl;
    //for(const Appliance* appliance : applianceArray)
    for (const std::shared_ptr<Appliance>& appliance : applianceArray) {
        std::cout << appliance->getName() << ": " << (appliance->isPowerOn() ? "����" : "����") << std::endl;
    }

    //�Ҽ��� 6°�ڸ����� ���
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "��ü ���� ��ǰ�� ���� �Ҹ�: " << totalPowerWatt << " Watt" << std::endl;
    std::cout << "��ü ���� ��ǰ�� ������ �Ҹ�: " << totalPowerKWh << " kWh" << std::endl;
    std::cout << "=================================================\n";
    getch();
}

void HomeAutomation::addPhoneNumberToAppliance() {
    std::cout << "=================================================\n";
    if (applianceArray.empty()) {
        std::cout << "��ϵ� ���� ��ǰ�� �����ϴ�." << std::endl;
        std::cout << "=================================================\n";
        getch();
        return;
    }
    std::cout << "���� ��ǰ ���:" << std::endl;
    for (int i = 0; i < applianceArray.size(); ++i) {
        std::cout << i + 1 << ": " << applianceArray[i]->getName() << std::endl;
    }
    std::cout << "=================================================\n";
    int index;
    std::cout << "��ȣ�� �߰��� ���� ��ǰ�� �ε����� �Է��ϼ���: ";
    std::cin >> index;
    if (std::cin.fail() || index <= 0 || index > applianceArray.size()) {
        std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << std::endl;
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
        std::cout << "=================================================\n";
        getch();
        return;
    }
    std::string phoneNumber;
    char addMore = 'y';
    do {
        std::cout << "=================================================\n";
        std::cout << "�߰��� �޴��� ��ȣ�� �Է��ϼ���: ";
        std::cin >> phoneNumber;
        std::cout << "=================================================\n";
        smsManager.add_sms_number(applianceArray[index - 1]->getName(), phoneNumber);
        std::cout << "��ȣ�� �߰��Ǿ����ϴ�." << std::endl;
        std::cout << "=================================================\n";
        std::cout << "�� ���� ��ȣ�� �߰��Ͻðڽ��ϱ�? (y/n): ";
        std::cin >> addMore;
        if (std::cin.fail()) {
            std::cout << "���ڸ� �߸��Է��߽��ϴ�. ���ڷ� �ٽ� �Է��ϼ���\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
        }
        std::cout << "=================================================\n";
    } while (addMore == 'y' || addMore == 'Y');
    std::cout << "��ȣ �߰��� �Ϸ� �Ǿ����ϴ�.): " << std::endl;;
    std::cout << "=================================================\n";
    getch();
}

void HomeAutomation::turnAllAppliancesOn() {
    std::cout << "=================================================\n";
    if (applianceArray.empty()) {
        std::cout << "��ϵ� ��ǰ�� �����ϴ�." << std::endl;
    }
    else {
        for (auto& appliance : applianceArray) {
            if (!appliance->isPowerOn()) {
                appliance->powerOn();
            }
        }
        std::cout << "��� ��ǰ�� ������ �������ϴ�" << std::endl;
    }
    std::cout << "=================================================\n";
    getch();
}

void HomeAutomation::turnAllAppliancesOff() {
    std::cout << "=================================================\n";
    if (applianceArray.empty()) {
        std::cout << "��ϵ� ��ǰ�� �����ϴ�." << std::endl;
    }
    else {
        for (auto& appliance : applianceArray) {
            if (appliance->isPowerOn()) {
                appliance->powerOff();
            }
        }
        std::cout << "��� ��ǰ�� ������ �������ϴ�" << std::endl;
    }
    std::cout << "=================================================\n";
    getch();
}
