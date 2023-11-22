#ifndef APPLIANCE_H
#define APPLIANCE_H

#include "SMSManager.h"

#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include <sstream>
#include <functional>
#include <conio.h>
#include <iomanip>
#include <memory>

const unsigned long max_size = std::numeric_limits<std::streamsize>::max();

#define MAX_NAME_LEN 20

#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable : 4996)


enum ApplianceType {
    AIR_CONDITIONER = 1,
    RICE_COOKER,
    WASHER,
    LIGHT
};

class Appliance {

    SMSManager* smsManager = nullptr;

public:
    Appliance(const std::string& name, ApplianceType type);
    virtual ~Appliance();

    void powerOn();
    void powerOff();
    virtual void control() = 0;
    virtual void display() const = 0;

    void setSMSManager(SMSManager* manager) { smsManager = manager; }

    void setPowerConsumption(int power) {powerConsumption = power;}
    void setIsPowerOn(bool value) { powerFlag = value; }
    void setState1(int value) { state1 = value; }
    void setState2(int value) { state2 = value; }
    void setStartHour(time_t time) { startHour = time; }

    const std::string& getName() const { return machineName; }
    ApplianceType getType() const { return type; }
    bool isPowerOn() const { return powerFlag; }
    int getPowerConsumption() const { return powerConsumption; }
    time_t getStartTime() const { return startHour; }
    time_t getUsageTime() const { return useHour; }
    int getState1() const{ return state1; }
    int getState2() const { return state2; }


    time_t getStartHour() const { return startHour; }

private:
    std::string machineName;
    ApplianceType type;
    bool powerFlag;
    int state1;
    int state2;
    int powerConsumption;
    time_t useHour;
    time_t startHour;
};

class AirConditioner : public Appliance {
public:
    AirConditioner(const std::string& name);
    void control() override;
    void display() const override;
};

class RiceCooker : public Appliance {
public:
    RiceCooker(const std::string& name);
    void control() override;
    void display() const override;
};

class Washer : public Appliance {
public:
    Washer(const std::string& name);
    void control() override;
    void display() const override;
};

class Light : public Appliance {
public:
    Light(const std::string& name);
    void control() override;
    void display() const override;
};

#endif