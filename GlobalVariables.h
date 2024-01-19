#pragma once
#include <variant>
#include <Vector3.h>
#include <iostream>
#include <string>
#include <map>

class GlobalVariables final{
public:
	static GlobalVariables* GetInstance();

private:
	GlobalVariables() = default;
	~GlobalVariables() = default;
	GlobalVariables(const GlobalVariables& obj) = delete;
	GlobalVariables& operator=(const GlobalVariables& obj) = delete;

	// ����
	struct Item {
		// ���ڂ̒l
		std::variant<int32_t, float, Vector3> value;
	};

	struct Group {
		std::map<std::string, Item> items;
		// �S�f�[�^
		std::map<std::string, Group> datas_;
	};
};
