#include "HomeAutomation.h"
#include <iostream>
#include <algorithm>

HomeAutomation::HomeAutomation() {}

HomeAutomation::~HomeAutomation() {
    applianceArray.clear();
    std::cout << "=================================================\n";
    std::cout << "홈 오토메이션 시스템이 종료되었습니다." << std::endl;
    std::cout << "=================================================\n";
}

void HomeAutomation::listDisplayAppliance() const {
    std::cout << "=================================================\n";
    if (applianceArray.empty()) {
        std::cout << "등록된 가전 제품이 아직 없습니다." << std::endl;
        std::cout << "=================================================\n";
        getch();
        return;
    }
    std::cout << "< 가전 제품 목록 >:" << std::endl;
    for (const std::shared_ptr<Appliance>& appliance : applianceArray) {
        appliance->display();
    }
    getch();
}

void HomeAutomation::addAppliance() {
    std::cout << "=================================================\n";
    if (applianceArray.size() >= APPLIANCE_MAX_CNT) {
        std::cout << "더 이상 가전 제품을 추가할 수 없습니다, 최대 수에 도달했습니다." << std::endl;
        std::cout << "=================================================\n";
        getch();
        return;
    }
    std::string name;
    int type;
    int power; // 소비전력을 입력받을 변수를 추가합니다.

    std::cout << "가전 제품 유형을 선택하세요 (1. 에어컨, 2. 밥솥, 3. 세탁기, 4. 조명): ";
    std::cin >> type;
    if (std::cin.fail()) {
        std::cout << "문자를 잘못입력했습니다. 1 ~ 4 숫자로 다시 입력하세요\n";
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
        getch();
    }
    else if (type < 1 || type > 4) {
        std::cout << "유효하지 않은 가전 제품 유형입니다." << std::endl;
        getch();
    }
    else {
        std::cout << "가전 제품 이름을 입력하세요: ";
        std::cin >> name;

        std::cout << "가전 제품의 소비전력을 입력하세요: ";
        std::cin >> power;

        if (std::cin.fail() || power <= 0) {
            std::cout << "잘못된 입력입니다. 다시 입력하세요.\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
            getch();
        }
        else {
            ApplianceType applianceType = static_cast<ApplianceType>(type);
            //중복 이름 검사
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
                    std::cout << "유효하지 않은 가전 제품 유형입니다." << std::endl;
                    std::cout << "=================================================\n";
                    getch();
                    return;
                }
                newAppliance->setPowerConsumption(power);
                newAppliance->setSMSManager(&smsManager);
                applianceArray.push_back(newAppliance);
                std::cout << "=================================================\n";
                std::cout << newAppliance->getName() << " 제품이 등록되었습니다." << std::endl;
                std::cout << "=================================================\n";
                getch();
            }
        }
    }
}

void HomeAutomation::deleteAppliance() {
    std::cout << "=================================================\n";
    if (applianceArray.empty()) {
        std::cout << "삭제할 가전 제품이 없습니다." << std::endl;
        getch();
        std::cout << "=================================================\n";
        return;
    }
    std::cout << "가전 제품 목록:" << std::endl;
    for (int i = 0; i < applianceArray.size(); ++i) {
        std::cout << i + 1 << ": " << applianceArray[i]->getName() << std::endl;
    }
    int index;
    std::cout << "삭제할 가전 제품의 인덱스를 입력하세요: ";
    std::cin >> index;
    if (std::cin.fail()) {
        std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
        getch();
    }

    if (index > 0 && index <= applianceArray.size()) {
        //delete applianceArray[index - 1];
        applianceArray.erase(applianceArray.begin() + (index - 1));
        std::cout << "가전 제품을 삭제했습니다." << std::endl;
    }
    else {
        std::cout << "유효하지 않은 인덱스입니다." << std::endl;
    }
    getch();
    std::cout << "=================================================\n";
}

void HomeAutomation::controlAppliance() {
    std::cout << "=================================================\n";
    if (applianceArray.empty()) {
        std::cout << "제어할 가전 제품이 없습니다." << std::endl;
        getch();
        std::cout << "=================================================\n";
        return;
    }

    std::cout << "가전 제품 목록:" << std::endl;
    for (int i = 0; i < applianceArray.size(); ++i) {
        std::cout << i + 1 << ": " << applianceArray[i]->getName() << std::endl;
    }

    int index;
    std::cout << "제어할 가전 제품의 인덱스를 입력하세요: ";
    std::cin >> index;
    if (std::cin.fail()) {
        std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
    }
    else if (index > 0 && index <= applianceArray.size()) {
        applianceArray[index - 1]->control();
    }
    else {
        std::cout << "유효하지 않은 인덱스입니다." << std::endl;
    }
    getch();
}

void HomeAutomation::powerDisplay() const {
    std::cout << "=================================================\n";
    if (applianceArray.empty()) {
        std::cout << "전원 상태를 표시할 가전 제품이 없습니다." << std::endl;
        std::cout << "=================================================\n";
        getch();
        return;
    }

    double totalPowerWatt = 0.0;
    double totalPowerKWh = 0.0;

    // 각 가전 제품에 대해 반복
    //for(const Appliance* appliance : applianceArray)
    for (const std::shared_ptr<Appliance>& appliance : applianceArray) {
        //사용시간이 있던 가전 제품에 대해서만 계산
        if (appliance->getUsageTime() > 0) {
            totalPowerWatt += appliance->getPowerConsumption(); // 전력 소모량을 Watt 단위로 합산
            double usageTimeHours = appliance->getUsageTime() / 3600.0; // 사용 시간을 시간 단위로 변환
            totalPowerKWh += (appliance->getPowerConsumption() * usageTimeHours) / 1000.0; // 에너지 소모량을 kWh 단위로 합산
        }
    }
    //현재 가전 제품 ON/OFF 상태
    std::cout << "< 가전 제품 전력 소모량 >:" << std::endl;
    //for(const Appliance* appliance : applianceArray)
    for (const std::shared_ptr<Appliance>& appliance : applianceArray) {
        std::cout << appliance->getName() << ": " << (appliance->isPowerOn() ? "켜짐" : "꺼짐") << std::endl;
    }

    //소수점 6째자리까지 출력
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "전체 가전 제품의 전력 소모량: " << totalPowerWatt << " Watt" << std::endl;
    std::cout << "전체 가전 제품의 에너지 소모량: " << totalPowerKWh << " kWh" << std::endl;
    std::cout << "=================================================\n";
    getch();
}

void HomeAutomation::addPhoneNumberToAppliance() {
    std::cout << "=================================================\n";
    if (applianceArray.empty()) {
        std::cout << "등록된 가전 제품이 없습니다." << std::endl;
        std::cout << "=================================================\n";
        getch();
        return;
    }
    std::cout << "가전 제품 목록:" << std::endl;
    for (int i = 0; i < applianceArray.size(); ++i) {
        std::cout << i + 1 << ": " << applianceArray[i]->getName() << std::endl;
    }
    std::cout << "=================================================\n";
    int index;
    std::cout << "번호를 추가할 가전 제품의 인덱스를 입력하세요: ";
    std::cin >> index;
    if (std::cin.fail() || index <= 0 || index > applianceArray.size()) {
        std::cout << "잘못된 입력입니다. 다시 입력하세요." << std::endl;
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
        std::cout << "추가할 휴대폰 번호를 입력하세요: ";
        std::cin >> phoneNumber;
        std::cout << "=================================================\n";
        smsManager.add_sms_number(applianceArray[index - 1]->getName(), phoneNumber);
        std::cout << "번호가 추가되었습니다." << std::endl;
        std::cout << "=================================================\n";
        std::cout << "더 많은 번호를 추가하시겠습니까? (y/n): ";
        std::cin >> addMore;
        if (std::cin.fail()) {
            std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
        }
        std::cout << "=================================================\n";
    } while (addMore == 'y' || addMore == 'Y');
    std::cout << "번호 추가가 완료 되었습니다.): " << std::endl;;
    std::cout << "=================================================\n";
    getch();
}

void HomeAutomation::turnAllAppliancesOn() {
    std::cout << "=================================================\n";
    if (applianceArray.empty()) {
        std::cout << "등록된 제품이 없습니다." << std::endl;
    }
    else {
        for (auto& appliance : applianceArray) {
            if (!appliance->isPowerOn()) {
                appliance->powerOn();
            }
        }
        std::cout << "모든 제품의 전원이 켜졌습니다" << std::endl;
    }
    std::cout << "=================================================\n";
    getch();
}

void HomeAutomation::turnAllAppliancesOff() {
    std::cout << "=================================================\n";
    if (applianceArray.empty()) {
        std::cout << "등록된 제품이 없습니다." << std::endl;
    }
    else {
        for (auto& appliance : applianceArray) {
            if (appliance->isPowerOn()) {
                appliance->powerOff();
            }
        }
        std::cout << "모든 제품의 전원이 꺼졌습니다" << std::endl;
    }
    std::cout << "=================================================\n";
    getch();
}
