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
            std::string message = machineName + " ������ �������ϴ�.";
            smsManager->send_sms(machineName, message);
        }
        else {
            std::cout << "=================================================\n";
            std::cout << "< �޴��� ��ȣ�� ��ϵ��� ���� ��ǰ�Դϴ�. >" << std::endl;
        }
    }
}

void Appliance::powerOff() {
    setIsPowerOn(false);
    time_t currentTime = time(nullptr);
    useHour += currentTime - getStartHour(); 
    if (smsManager) {
        std::string message = machineName + " ������ �������ϴ�.";
        smsManager->send_sms(machineName, message);
    }
}

AirConditioner::AirConditioner(const std::string& name)
    : Appliance(name, AIR_CONDITIONER) {}


void AirConditioner::control() {
    std::cout << "=================================================\n";
    if (!isPowerOn()) {
        std::cout << getName() << " ������ ������ ���� �ֽ��ϴ�. ������ �ѽðڽ��ϱ�? (1: �ѱ� / 2: ���): ";
        int powerChoice;
        std::cin >> powerChoice;
        if (std::cin.fail()){
            std::cout << "���ڸ� �߸��Է��߽��ϴ�. ���ڷ� �ٽ� �Է��ϼ���\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
            getch();
            return;
        }
        if (powerChoice == 1) {
            powerOn(); // ������ �մϴ�.
        }
        else {
            std::cout << "������ ���� �ʾ����Ƿ� ��� �����մϴ�." << std::endl;
            getch();
            return;
        }
    }
    std::cout << "=================================================\n";
    std::cout << getName() << " �������� �����մϴ�." << std::endl;
    std::cout << "=================================================\n";
    int choice;
    std::cout << "1. ��ǳ\n2. �ù�\n3. ����\n4. �µ� ����\n5. ���� ����\n����: ";
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cout << "���ڸ� �߸��Է��߽��ϴ�. ���ڷ� �ٽ� �Է��ϼ���\n";
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
        getch();
    }
    switch (choice) {
    case 1:
        setState1(1);
        std::cout << getName() << " �������� ��ǳ ���� �����߽��ϴ�." << std::endl;
        break;
    case 2:
        setState1(2);
        std::cout << getName() << " �������� �ù� ���� �����߽��ϴ�." << std::endl;
        std::cout << "���� �µ�: " << getState2() << "��" << std::endl;
        int newTemperature;
        std::cout << "�µ��� �����ϼ���: ";
        std::cin >> newTemperature;
        if (std::cin.fail()) {
            std::cout << "���ڸ� �߸��Է��߽��ϴ�. ���ڷ� �ٽ� �Է��ϼ���\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
        }
        setState2(newTemperature);
        std::cout << getName() << " ������ �µ��� " << newTemperature << "���� �����߽��ϴ�." << std::endl;
        break;
    case 3:
        setState1(3);
        std::cout << getName() << " �������� ���� ���� �����߽��ϴ�." << std::endl;
        std::cout << "���� �µ�: " << getState2() << "��" << std::endl;
        std::cout << "�µ��� �����ϼ���: ";
        std::cin >> newTemperature;
        if (std::cin.fail()) {
            std::cout << "���ڸ� �߸��Է��߽��ϴ�. ���ڷ� �ٽ� �Է��ϼ���\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
        }
        setState2(newTemperature);
        std::cout << getName() << " ������ �µ��� " << newTemperature << "���� �����߽��ϴ�." << std::endl;
        break;
    case 4:
        switch (getState1()) {
        case 1:
            std::cout << getName() << " : ���� ��ǳ ����Դϴ�." << std::endl;
            break;
        case 2:
            std::cout << getName() << " : ���� �ù� ����Դϴ�." << std::endl;
            break;
        case 3:
            std::cout << getName() << " : ���� ���� ����Դϴ�." << std::endl;
            break;
        default:
            std::cout << getName() << " : ��� ������ �� �� �����ϴ�." << std::endl;
            break;
        }
        std::cout << "���� �µ�: " << getState2() << "��" << std::endl;
        std::cout << "�µ��� �����ϼ���: ";
        std::cin >> newTemperature;
        if (std::cin.fail()) {
            std::cout << "���ڸ� �߸��Է��߽��ϴ�. ���ڷ� �ٽ� �Է��ϼ���\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
        }
        setState2(newTemperature);
        std::cout << getName() << " ������ �µ��� " << newTemperature << "���� �����߽��ϴ�." << std::endl;
        break;
    case 5:
        powerOff();
        std::cout << getName() << " ������ ������ ���ϴ�." << std::endl;
        break;
    default:
        std::cout << "�߸��� �����Դϴ�." << std::endl;
        break;
    }
    std::cout << "=================================================\n";
}

void AirConditioner::display() const {
    std::cout << "=================================================\n";
    std::cout << "������ǰ��: " << getName() << std::endl;
    std::cout << "������ǰ ����: ������" << std::endl;
    std::cout << "���� ����: " << (isPowerOn() ? "����" : "����") << std::endl;
    std::cout << "�⺻ ����: ";

    switch (getState1()) {
    case 1:
        std::cout << "��ǳ";
        break;
    case 2:
        std::cout << "�ù�";
        break;
    case 3:
        std::cout << "����";
        break;
    default:
        std::cout << "�� �� ����";
        break;
    }
    std::cout << std::endl;
    std::cout << "�⺻ ���� �µ�: " << getState2() << "��" << std::endl;
    std::cout << "�ð��� ���� �Ҹ�: " << getPowerConsumption() << "W" << std::endl;

    std::cout << "��� ���� �ð�: ";
    time_t startHourCopy = getStartHour(); // �ӽ� ������ ����
    std::cout << std::put_time(std::localtime(&startHourCopy), "%Y-%m-%d %H:%M:%S") << std::endl;

    int hours = getUsageTime() / 3600;
    int minutes = getUsageTime() % 3600 / 60;
    int seconds = getUsageTime() % 60;
    std::cout << "���� ��� �ð�: " << hours << "�ð� " << minutes << "�� " << seconds << "��" << std::endl;
    std::cout << "=================================================\n";

}

RiceCooker::RiceCooker(const std::string& name)
    : Appliance(name, RICE_COOKER) {}

void RiceCooker::control() {
    std::cout << "=================================================\n";
    if (!isPowerOn()) {
        std::cout << getName() << " ��� ������ ���� �ֽ��ϴ�. ������ �ѽðڽ��ϱ�? (1: �ѱ� / 2: ���): ";
        int powerChoice;
        std::cin >> powerChoice;
        if (std::cin.fail()) {
            std::cout << "���ڸ� �߸��Է��߽��ϴ�. ���ڷ� �ٽ� �Է��ϼ���\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
            getch();
        }
        if (powerChoice == 1) {
            powerOn(); // ������ �մϴ�.
        }
        else {
            std::cout << "������ ���� �ʾ����Ƿ� ��� �����մϴ�." << std::endl;
            getch();
            return;
        }
    }
    std::cout << getName() << " ����� �����մϴ�." << std::endl;
    int choice;
    std::cout << "1. ������\n2. ����\n3. ������\n4. �����\n5. ���� ����\n����: ";
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cout << "���ڸ� �߸��Է��߽��ϴ�. ���ڷ� �ٽ� �Է��ϼ���\n";
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
        getch();
    }
    switch (choice) {
    case 1:
        setState1(1);
        std::cout << getName() << " ����� ������ ���� �����߽��ϴ�." << std::endl;
        break;
    case 2:
        setState1(2);
        std::cout << getName() << " ����� ���� ���� �����߽��ϴ�." << std::endl;
        break;
    case 3:
        setState1(3);
        std::cout << getName() << " ����� ������ ���� �����߽��ϴ�." << std::endl;
        break;
    case 4:
        setState1(4);
        std::cout << getName() << " ����� ����� ���� �����߽��ϴ�." << std::endl;
        break;
    case 5:
        powerOff();
        std::cout << getName() << " ��� ������ ���ϴ�." << std::endl;
        break;
    default:
        std::cout << "�߸��� �����Դϴ�." << std::endl;
        break;
    }
    std::cout << "=================================================\n";
}

void RiceCooker::display() const {
    std::cout << "=================================================\n";
    std::cout << "������ǰ��: " << getName() << std::endl;
    std::cout << "������ǰ ����: ���" << std::endl;
    std::cout << "���� ����: " << (isPowerOn() ? "����" : "����") << std::endl;
    std::cout << "�⺻ ����: ";

    switch (getState1()) {
    case 1:
        std::cout << "������";
        break;
    case 2:
        std::cout << "����";
        break;
    case 3:
        std::cout << "������";
        break;
    case 4:
        std::cout << "�����";
        break;
    default:
        std::cout << "�� �� ����";
        break;
    }
    std::cout << std::endl;
    std::cout << "�ð��� ���� �Ҹ�: " << getPowerConsumption() << "W" << std::endl;
    std::cout << "��� ���� �ð�: ";
    time_t startHourCopy = getStartHour(); // �ӽ� ������ ����
    std::cout << std::put_time(std::localtime(&startHourCopy), "%Y-%m-%d %H:%M:%S") << std::endl;
    int hours = getUsageTime() / 3600;
    int minutes = getUsageTime() % 3600 / 60;
    int seconds = getUsageTime() % 60;
    std::cout << "���� ��� �ð�: " << hours << "�ð� " << minutes << "�� " << seconds << "��" << std::endl;
    std::cout << "=================================================\n";
}

Washer::Washer(const std::string& name)
    : Appliance(name, WASHER) {}

void Washer::control() {
    std::cout << "=================================================\n";
    if (!isPowerOn()) {
        std::cout << getName() << " ��Ź�� ������ ���� �ֽ��ϴ�. ������ �ѽðڽ��ϱ�? (1: �ѱ� / 2: ���): ";
        int powerChoice;
        std::cin >> powerChoice;
        if (std::cin.fail()) {
            std::cout << "���ڸ� �߸��Է��߽��ϴ�. ���ڷ� �ٽ� �Է��ϼ���\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
            getch();
        }
        if (powerChoice == 1) {
            powerOn(); // ������ �մϴ�.
        }
        else {
            std::cout << "������ ���� �ʾ����Ƿ� ��� �����մϴ�." << std::endl;
            getch();
            return;
        }
    }
    std::cout << getName() << " ��Ź�⸦ �����մϴ�." << std::endl;
    int choice;
    std::cout << "1. ������\n2. �Ϲݻ���\n3. ��������\n4. ����\n5. ���� ����\n����: ";
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cout << "���ڸ� �߸��Է��߽��ϴ�. ���ڷ� �ٽ� �Է��ϼ���\n";
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
        getch();
    }
    switch (choice) {
    case 1:
        setState1(1);
        std::cout << getName() << " ��Ź�⸦ ������ ���� �����߽��ϴ�" << std::endl;
        break;
    case 2:
        setState1(2);
        std::cout << getName() << " ��Ź�⸦ �Ϲݻ��� ���� �����߽��ϴ�." << std::endl;
        break;
    case 3:
        setState1(3);
        std::cout << getName() << " ��Ź�⸦ �������� ���� �����߽��ϴ�." << std::endl;
        break;
    case 4:
        setState1(4);
        std::cout << getName() << " ��Ź�⸦ ���� ���� �����߽��ϴ�." << std::endl;
        break;
    case 5:
        powerOff();
        std::cout << getName() << " ��Ź�� ������ ���ϴ�." << std::endl;
        break;
    default:
        std::cout << "�߸��� �����Դϴ�." << std::endl;
        break;
    }
    std::cout << "=================================================\n";
}

void Washer::display() const {
    std::cout << "=================================================\n";
    std::cout << "������ǰ��: " << getName() << std::endl;
    std::cout << "������ǰ ����: ��Ź��" << std::endl;
    std::cout << "���� ����: " << (isPowerOn() ? "����" : "����") << std::endl;
    std::cout << "�⺻ ����: ";

    switch (getState1()) {
    case 1:
        std::cout << "������";
        break;
    case 2:
        std::cout << "�Ϲݻ���";
        break;
    case 3:
        std::cout << "��������";
        break;
    case 4:
        std::cout << "����";
        break;
    default:
        std::cout << "�� �� ����";
        break;
    }
    std::cout << std::endl;
    std::cout << "�ð��� ���� �Ҹ�: " << getPowerConsumption() << "W" << std::endl;
    std::cout << "��� ���� �ð�: ";
    time_t startHourCopy = getStartHour(); // �ӽ� ������ ����
    std::cout << std::put_time(std::localtime(&startHourCopy), "%Y-%m-%d %H:%M:%S") << std::endl;
    int hours = getUsageTime() / 3600;
    int minutes = getUsageTime() % 3600 / 60;
    int seconds = getUsageTime() % 60;
    std::cout << "���� ��� �ð�: " << hours << "�ð� " << minutes << "�� " << seconds << "��" << std::endl;
    std::cout << "=================================================\n";
}

Light::Light(const std::string& name)
    : Appliance(name, LIGHT) {}

void Light::control() {
    std::cout << "=================================================\n";
    if (!isPowerOn()) {
        std::cout << getName() << " ���� ������ ���� �ֽ��ϴ�. ������ �ѽðڽ��ϱ�? (1: �ѱ� / 2: ���): ";
        int powerChoice;
        std::cin >> powerChoice;
        if (std::cin.fail()) {
            std::cout << "���ڸ� �߸��Է��߽��ϴ�. ���ڷ� �ٽ� �Է��ϼ���\n";
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
            getch();
        }
        if (powerChoice == 1) {
            powerOn(); // ������ �մϴ�.
        }
        else {
            std::cout << "������ ���� �ʾ����Ƿ� ��� �����մϴ�." << std::endl;
            getch();
            return;
        }
    }
    std::cout << getName() << " ������ �����մϴ�." << std::endl;
    int choice;
    std::cout << "1. �Ϲ�����\n2. ��������\n3. �������\n����: ";
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cout << "���ڸ� �߸��Է��߽��ϴ�. ���ڷ� �ٽ� �Է��ϼ���\n";
        std::cin.clear();
        std::cin.ignore(max_size, '\n');
        getch();
    }
    switch (choice) {
    case 1:
        setState1(1);
        std::cout << getName() << " �Ϲ��������� �մϴ�." << std::endl;
        break;
    case 2:
        setState1(2);
        std::cout << getName() << " ������������ �մϴ�." << std::endl;
        break;
    case 3:
        setState1(3);
        powerOff();
        std::cout << getName() << " ������ �����ϴ�." << std::endl;
        break;
    default:
        std::cout << "�߸��� �����Դϴ�." << std::endl;
        break;
    }
    std::cout << "=================================================\n";
}

void Light::display() const {
    std::cout << "=================================================\n";
    std::cout << "������ǰ��: " << getName() << std::endl;
    std::cout << "������ǰ ����: ����" << std::endl;
    std::cout << "���� ����: " << (isPowerOn() ? "����" : "����") << std::endl;
    std::cout << "�⺻ ����: ";

    switch (getState1()) {
    case 1:
        std::cout << "�Ϲ�����";
        break;
    case 2:
        std::cout << "��������";
        break;
    default:
        std::cout << "�� �� ����";
        break;
    }
    std::cout << std::endl;
    std::cout << "�ð��� ���� �Ҹ�: " << getPowerConsumption() << "W" << std::endl;
    std::cout << "��� ���� �ð�: ";
    time_t startHourCopy = getStartHour(); // �ӽ� ������ ����
    std::cout << std::put_time(std::localtime(&startHourCopy), "%Y-%m-%d %H:%M:%S") << std::endl;
    int hours = getUsageTime() / 3600;
    int minutes = getUsageTime() % 3600 / 60;
    int seconds = getUsageTime() % 60;
    std::cout << "���� ��� �ð�: " << hours << "�ð� " << minutes << "�� " << seconds << "��" << std::endl;
    std::cout << "=================================================\n";
}