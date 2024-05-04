#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<algorithm>
#include<iostream>
#include<regex>
#include<string>
#include<vector>
#include<set>
#include<unordered_map>
#include<unordered_set>

//�Ź�ͬʹ�õ�ȫ�ַ��� / ȫ�ֱ���

// ��extern ֻ���ڶ�����ļ�ʹ��
extern std::regex N;
extern std::regex T;							//����

extern char lineToken[128];						//��¼�ķ��ṹ(��¼һ��)
extern char expLineToken[50];					//��¼����ʽ�ṹ��һ�У�
extern char strToken[50];						//�ʷ�������¼


//--�ʷ�����
//�õ���������
std::string getFullChar(std::string candidate, int pos);

//����ָ��Ϊ ��һ���ǿ��ַ�
int getBC(int pos, char line[]);

//--�ķ��ṹ
struct grammarStruct {
	std::string S;
	std::set<std::string>Vt;
	std::unordered_map<std::string, int>Vn;
	std::unordered_map<std::string, std::vector<std::string>>P;

	grammarStruct() {};
};

//�����ķ��ṹ
class Grammar_set {
public:
	const char* readGrammarFile = "./src/textFile/grammarText.txt";
	const char* writeGrammerFile = "";

	//�ķ�
	grammarStruct grammar;
	//˳���¼����ʽ
	std::vector<std::string>Productions;
	Grammar_set() {};

	//����ռ�
	void calculate_NullAble();
	//����First����
	void calculate_First();
	//����Follow����
	void calculate_Follow();

	//�ļ��ж����ķ�
	bool readGrammar(const char* GrammarFile);

	//�ļ�ɨ�����ʽ¼���ķ�
	void scanCandidateIntoGrammar(char line[]);

	//��ʽ������ķ�
	void formatPrint();

	//��ʽ������ķ����ļ�
	void formatPrintLL1IntoFile(const char* writeLL1TransResultFile);

protected:
	std::unordered_set<std::string>NullAble;
	std::unordered_map<std::string, std::unordered_set<std::string>>First, Follow;
};


//--SLR
//��Ŀ -- ֻ��SLR�����Ĺ��� SLR���󲻳���
struct item {
	std::string Proleft;
	std::string ProCandidate;
	int point;

	//����!=
	bool operator != (const item& backitem)const {
		if (this->Proleft != backitem.Proleft ||
			this->ProCandidate != backitem.ProCandidate ||
			this->point != backitem.point) {
			return true;
		}
		return false;
	}
	item() :Proleft(""), ProCandidate(""), point(-1) {}
	//�ò���ʽ + ��λ�ù���item
	item(std::string Pleft, std::string PCan, int p)
		:Proleft(Pleft), ProCandidate(PCan), point(p) {}
};

//��Ŀ���ڵ�
struct items_Node {
	int state_id;			//�����Ŀ��
	std::vector<item>items_Set;	//�ڵ���������Ŀ
	int originNum;			//��¼��ʼ��Ŀ����

	//�޲ι���
	items_Node() :state_id(0), items_Set(0), originNum(0) {}
	//��������Ŀ�������ι���
	items_Node(const items_Node& extendNode) {
		this->state_id = extendNode.state_id;
		for (item i : extendNode.items_Set) {
			this->items_Set.push_back(i);
		}
		this->originNum = extendNode.originNum;
	}
	items_Node(const std::vector<item>& a) {
		this->state_id = 0;
		for (item i : a) {
			this->items_Set.push_back(i);
		}
		this->originNum = a.size();
	}
};