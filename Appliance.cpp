#include "Appliance.h"
#include <iostream>
#include <iomanip>

Appliance::Appliance(const std::string& name, ApplianceType type)
    : machineName(name), type(type), powerFlag(false),
    state1(1), state2(25), startHour(0), useHour(0), powerConsumption(0) {}

Appliance::~Appliance() {}

void Appliance::powerOn() {
    setIsPowerOn(true);
    setStartHour(time(nullptr));
    if (smsManager) {
        if (smsManager->hasPhoneNumber(machineName)) {
            std::string message = machineName + " 전원이 켜졌습니다.";
            smsManager->send_sms(machineName, message);
        }
        else {
            std::cout << "=================================================\n";
            std::cout << "< 휴대폰 번호가 등록되지 않은 제품입니다. >" << std::endl;
        }
    }
}

void Appliance::powerOff() {
    setIsPowerOn(false);
    time_t currentTime = time(nullptr);
    useHour += currentTime - getStartHour(); 
    if (smsManager) {
        std::string message = machineName + " 전원이 꺼졌습니다.";
        smsManager->send_sms(machineName, message);
    }
}

AirConditioner::AirConditioner(const std::string& name)
    : Appliance(name, AIR_CONDITIONER) {}


void AirConditioner::control() {
    std::cout << "=================================================\n";
    if (!isPowerOn()) {
        std::cout << getName() << " 에어컨 전원이 꺼져 있습니다. 전원을 켜시겠습니까? (1: 켜기 / 2: 취소): ";
        int powerChoice;
        std::cin >> powerChoice;
        if (std::cin.fail()){
            std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
            getch();
            return;
        }
        if (powerChoice == 1) {
            powerOn(); // 전원을 켭니다.
        }
        else {
            std::cout << "전원을 켜지 않았으므로 제어를 종료합니다." << std::endl;
            getch();
            return;
        }
    }
    std::cout << "=================================================\n";
    std::cout << getName() << " 에어컨을 제어합니다." << std::endl;
    std::cout << "=================================================\n";
    int choice;
    std::cout << "1. 송풍\n2. 냉방\n3. 난방\n4. 온도 조절\n5. 전원 끄기\n선택: ";
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
        getch();
    }
    switch (choice) {
    case 1:
        setState1(1);
        std::cout << getName() << " 에어컨을 송풍 모드로 설정했습니다." << std::endl;
        break;
    case 2:
        setState1(2);
        std::cout << getName() << " 에어컨을 냉방 모드로 설정했습니다." << std::endl;
        std::cout << "현재 온도: " << getState2() << "도" << std::endl;
        int newTemperature;
        std::cout << "온도를 조절하세요: ";
        std::cin >> newTemperature;
        if (std::cin.fail()) {
            std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
        }
        setState2(newTemperature);
        std::cout << getName() << " 에어컨 온도를 " << newTemperature << "도로 조절했습니다." << std::endl;
        break;
    case 3:
        setState1(3);
        std::cout << getName() << " 에어컨을 난방 모드로 설정했습니다." << std::endl;
        std::cout << "현재 온도: " << getState2() << "도" << std::endl;
        std::cout << "온도를 조절하세요: ";
        std::cin >> newTemperature;
        if (std::cin.fail()) {
            std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
        }
        setState2(newTemperature);
        std::cout << getName() << " 에어컨 온도를 " << newTemperature << "도로 조절했습니다." << std::endl;
        break;
    case 4:
        switch (getState1()) {
        case 1:
            std::cout << getName() << " : 현재 송풍 모드입니다." << std::endl;
            break;
        case 2:
            std::cout << getName() << " : 현재 냉방 모드입니다." << std::endl;
            break;
        case 3:
            std::cout << getName() << " : 현재 난방 모드입니다." << std::endl;
            break;
        default:
            std::cout << getName() << " : 모드 정보를 알 수 없습니다." << std::endl;
            break;
        }
        std::cout << "현재 온도: " << getState2() << "도" << std::endl;
        std::cout << "온도를 조절하세요: ";
        std::cin >> newTemperature;
        if (std::cin.fail()) {
            std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
        }
        setState2(newTemperature);
        std::cout << getName() << " 에어컨 온도를 " << newTemperature << "도로 조절했습니다." << std::endl;
        break;
    case 5:
        powerOff();
        std::cout << getName() << " 에어컨 전원을 끕니다." << std::endl;
        break;
    default:
        std::cout << "잘못된 선택입니다." << std::endl;
        break;
    }
    std::cout << "=================================================\n";
}

void AirConditioner::display() const {
    std::cout << "=================================================\n";
    std::cout << "가전제품명: " << getName() << std::endl;
    std::cout << "가전제품 종류: 에어컨" << std::endl;
    std::cout << "전원 상태: " << (isPowerOn() ? "켜짐" : "꺼짐") << std::endl;
    std::cout << "기본 상태: ";

    switch (getState1()) {
    case 1:
        std::cout << "송풍";
        break;
    case 2:
        std::cout << "냉방";
        break;
    case 3:
        std::cout << "난방";
        break;
    default:
        std::cout << "알 수 없음";
        break;
    }
    std::cout << std::endl;
    std::cout << "기본 설정 온도: " << getState2() << "도" << std::endl;
    std::cout << "시간당 전력 소모량: " << getPowerConsumption() << "W" << std::endl;

    std::cout << "사용 시작 시간: ";
    time_t startHourCopy = getStartHour(); // 임시 변수에 복사
    std::cout << std::put_time(std::localtime(&startHourCopy), "%Y-%m-%d %H:%M:%S") << std::endl;

    int hours = getUsageTime() / 3600;
    int minutes = getUsageTime() % 3600 / 60;
    int seconds = getUsageTime() % 60;
    std::cout << "누적 사용 시간: " << hours << "시간 " << minutes << "분 " << seconds << "초" << std::endl;
    std::cout << "=================================================\n";

}

RiceCooker::RiceCooker(const std::string& name)
    : Appliance(name, RICE_COOKER) {}

void RiceCooker::control() {
    std::cout << "=================================================\n";
    if (!isPowerOn()) {
        std::cout << getName() << " 밥솥 전원이 꺼져 있습니다. 전원을 켜시겠습니까? (1: 켜기 / 2: 취소): ";
        int powerChoice;
        std::cin >> powerChoice;
        if (std::cin.fail()) {
            std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
            getch();
        }
        if (powerChoice == 1) {
            powerOn(); // 전원을 켭니다.
        }
        else {
            std::cout << "전원을 켜지 않았으므로 제어를 종료합니다." << std::endl;
            getch();
            return;
        }
    }
    std::cout << getName() << " 밥솥을 제어합니다." << std::endl;
    int choice;
    std::cout << "1. 무동작\n2. 보온\n3. 밥짓기\n4. 데우기\n5. 전원 끄기\n선택: ";
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
        getch();
    }
    switch (choice) {
    case 1:
        setState1(1);
        std::cout << getName() << " 밥솥을 무동작 모드로 설정했습니다." << std::endl;
        break;
    case 2:
        setState1(2);
        std::cout << getName() << " 밥솥을 보온 모드로 설정했습니다." << std::endl;
        break;
    case 3:
        setState1(3);
        std::cout << getName() << " 밥솥을 밥짓기 모드로 설정했습니다." << std::endl;
        break;
    case 4:
        setState1(4);
        std::cout << getName() << " 밥솥을 데우기 모드로 설정했습니다." << std::endl;
        break;
    case 5:
        powerOff();
        std::cout << getName() << " 밥솥 전원을 끕니다." << std::endl;
        break;
    default:
        std::cout << "잘못된 선택입니다." << std::endl;
        break;
    }
    std::cout << "=================================================\n";
}

void RiceCooker::display() const {
    std::cout << "=================================================\n";
    std::cout << "가전제품명: " << getName() << std::endl;
    std::cout << "가전제품 종류: 밥솥" << std::endl;
    std::cout << "전원 상태: " << (isPowerOn() ? "켜짐" : "꺼짐") << std::endl;
    std::cout << "기본 상태: ";

    switch (getState1()) {
    case 1:
        std::cout << "무동작";
        break;
    case 2:
        std::cout << "보온";
        break;
    case 3:
        std::cout << "밥짓기";
        break;
    case 4:
        std::cout << "데우기";
        break;
    default:
        std::cout << "알 수 없음";
        break;
    }
    std::cout << std::endl;
    std::cout << "시간당 전력 소모량: " << getPowerConsumption() << "W" << std::endl;
    std::cout << "사용 시작 시간: ";
    time_t startHourCopy = getStartHour(); // 임시 변수에 복사
    std::cout << std::put_time(std::localtime(&startHourCopy), "%Y-%m-%d %H:%M:%S") << std::endl;
    int hours = getUsageTime() / 3600;
    int minutes = getUsageTime() % 3600 / 60;
    int seconds = getUsageTime() % 60;
    std::cout << "누적 사용 시간: " << hours << "시간 " << minutes << "분 " << seconds << "초" << std::endl;
    std::cout << "=================================================\n";
}

Washer::Washer(const std::string& name)
    : Appliance(name, WASHER) {}

void Washer::control() {
    std::cout << "=================================================\n";
    if (!isPowerOn()) {
        std::cout << getName() << " 세탁기 전원이 꺼져 있습니다. 전원을 켜시겠습니까? (1: 켜기 / 2: 취소): ";
        int powerChoice;
        std::cin >> powerChoice;
        if (std::cin.fail()) {
            std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
            getch();
        }
        if (powerChoice == 1) {
            powerOn(); // 전원을 켭니다.
        }
        else {
            std::cout << "전원을 켜지 않았으므로 제어를 종료합니다." << std::endl;
            getch();
            return;
        }
    }
    std::cout << getName() << " 세탁기를 제어합니다." << std::endl;
    int choice;
    std::cout << "1. 무동작\n2. 일반빨래\n3. 삶은빨래\n4. 건조\n5. 전원 끄기\n선택: ";
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
        getch();
    }
    switch (choice) {
    case 1:
        setState1(1);
        std::cout << getName() << " 세탁기를 무동작 모드로 설정했습니다" << std::endl;
        break;
    case 2:
        setState1(2);
        std::cout << getName() << " 세탁기를 일반빨래 모드로 설정했습니다." << std::endl;
        break;
    case 3:
        setState1(3);
        std::cout << getName() << " 세탁기를 삶은빨래 모드로 설정했습니다." << std::endl;
        break;
    case 4:
        setState1(4);
        std::cout << getName() << " 세탁기를 건조 모드로 설정했습니다." << std::endl;
        break;
    case 5:
        powerOff();
        std::cout << getName() << " 세탁기 전원을 끕니다." << std::endl;
        break;
    default:
        std::cout << "잘못된 선택입니다." << std::endl;
        break;
    }
    std::cout << "=================================================\n";
}

void Washer::display() const {
    std::cout << "=================================================\n";
    std::cout << "가전제품명: " << getName() << std::endl;
    std::cout << "가전제품 종류: 세탁기" << std::endl;
    std::cout << "전원 상태: " << (isPowerOn() ? "켜짐" : "꺼짐") << std::endl;
    std::cout << "기본 상태: ";

    switch (getState1()) {
    case 1:
        std::cout << "무동작";
        break;
    case 2:
        std::cout << "일반빨래";
        break;
    case 3:
        std::cout << "삶은빨래";
        break;
    case 4:
        std::cout << "건조";
        break;
    default:
        std::cout << "알 수 없음";
        break;
    }
    std::cout << std::endl;
    std::cout << "시간당 전력 소모량: " << getPowerConsumption() << "W" << std::endl;
    std::cout << "사용 시작 시간: ";
    time_t startHourCopy = getStartHour(); // 임시 변수에 복사
    std::cout << std::put_time(std::localtime(&startHourCopy), "%Y-%m-%d %H:%M:%S") << std::endl;
    int hours = getUsageTime() / 3600;
    int minutes = getUsageTime() % 3600 / 60;
    int seconds = getUsageTime() % 60;
    std::cout << "누적 사용 시간: " << hours << "시간 " << minutes << "분 " << seconds << "초" << std::endl;
    std::cout << "=================================================\n";
}

Light::Light(const std::string& name)
    : Appliance(name, LIGHT) {}

void Light::control() {
    std::cout << "=================================================\n";
    if (!isPowerOn()) {
        std::cout << getName() << " 조명 전원이 꺼져 있습니다. 전원을 켜시겠습니까? (1: 켜기 / 2: 취소): ";
        int powerChoice;
        std::cin >> powerChoice;
        if (std::cin.fail()) {
            std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
            getch();
        }
        if (powerChoice == 1) {
            powerOn(); // 전원을 켭니다.
        }
        else {
            std::cout << "전원을 켜지 않았으므로 제어를 종료합니다." << std::endl;
            getch();
            return;
        }
    }
    std::cout << getName() << " 조명을 제어합니다." << std::endl;
    int choice;
    std::cout << "1. 일반조명\n2. 무드조명\n3. 조명끄기\n선택: ";
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cout << "문자를 잘못입력했습니다. 숫자로 다시 입력하세요\n";
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
        getch();
    }
    switch (choice) {
    case 1:
        setState1(1);
        std::cout << getName() << " 일반조명으로 켭니다." << std::endl;
        break;
    case 2:
        setState1(2);
        std::cout << getName() << " 무드조명으로 켭니다." << std::endl;
        break;
    case 3:
        setState1(3);
        powerOff();
        std::cout << getName() << " 조명을 껐습니다." << std::endl;
        break;
    default:
        std::cout << "잘못된 선택입니다." << std::endl;
        break;
    }
    std::cout << "=================================================\n";
}

void Light::display() const {
    std::cout << "=================================================\n";
    std::cout << "가전제품명: " << getName() << std::endl;
    std::cout << "가전제품 종류: 조명" << std::endl;
    std::cout << "전원 상태: " << (isPowerOn() ? "켜짐" : "꺼짐") << std::endl;
    std::cout << "기본 상태: ";

    switch (getState1()) {
    case 1:
        std::cout << "일반조명";
        break;
    case 2:
        std::cout << "무드조명";
        break;
    default:
        std::cout << "알 수 없음";
        break;
    }
    std::cout << std::endl;
    std::cout << "시간당 전력 소모량: " << getPowerConsumption() << "W" << std::endl;
    std::cout << "사용 시작 시간: ";
    time_t startHourCopy = getStartHour(); // 임시 변수에 복사
    std::cout << std::put_time(std::localtime(&startHourCopy), "%Y-%m-%d %H:%M:%S") << std::endl;
    int hours = getUsageTime() / 3600;
    int minutes = getUsageTime() % 3600 / 60;
    int seconds = getUsageTime() % 60;
    std::cout << "누적 사용 시간: " << hours << "시간 " << minutes << "분 " << seconds << "초" << std::endl;
    std::cout << "=================================================\n";
}