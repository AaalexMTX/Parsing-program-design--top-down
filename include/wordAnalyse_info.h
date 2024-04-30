#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<cstring>
#include<regex>
#include"../include/Common_data.h"


//判断字符是否为数字
bool isNumber(char& c);

//判断字符是否为单词
bool isLetter(char& c);

//返回表达式 下一起始位置
int getBCExp(char line[], int pos);

//重载一个 做逆波兰式用
int getBCExp(std::string line, int pos);

//表达式类型转换
std::string ExpChange(char line[]);

//适配逆波兰式的词法分析
std::pair<std::string, std::string> wordChange(std::string& line, int& linePf);
