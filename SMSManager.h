#ifndef SMSMANAGER_H
#define SMSMANAGER_H

#include <iostream>
#include <map>
#include <string>
#include <vector> 

class SMSManager
{
	using PHONENUMBER = std::string;

	std::map<std::string, std::vector<PHONENUMBER>> m;

public:
	void add_sms_number(const std::string& key, const PHONENUMBER& number)
	{
		m[key].push_back(number);
	}

	void send_sms(const std::string& key, const std::string& msg)
	{
		auto iter = m.find(key);
		if (iter != m.end()) {   
			for (const PHONENUMBER& number : iter->second) {
				std::cout << "< 휴대폰 번호: " << number << " 에게 전달 메시지 : " << msg << " >" << std::endl;
			}
		}
	}
	bool hasPhoneNumber(const std::string& key) {
		return m.find(key) != m.end() && !m[key].empty();
	}
};

#endif 