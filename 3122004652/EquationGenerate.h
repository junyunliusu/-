#pragma once
#include "Fraction.h"
#include <unordered_set>

struct Node {
	Fraction fr;
	string eq;
	string checkeq;
	string op;
	int l, r;//��¼
	bool bracketadd;
	void swapkey(Node& x) {
		swap(fr, x.fr); swap(eq, x.eq);
		swap(checkeq, x.checkeq); swap(op, x.op);
		swap(bracketadd, x.bracketadd);
	}
};

string getRandomOperator() {
	int rd = rand() % 4;
	if (rd == 0) return "+";
	else if (rd == 1) return "-";
	else if (rd == 2) return "*";
	else return "��";
}

Node getRandomEquation(unordered_set<string>& vis) {
	int siz = (rand() % operatorLimit + 1) * 2 + 1;
	vector <Node> List(siz);//��vectorʵ�ֽ������ɵ�Ĺ���
	vector <int> priority;//���ȼ�
	List[0].fr.random_init(); List[0].checkeq = List[0].eq = List[0].fr.write();
	List[0].l = -1, List[0].r = 1; List[0].bracketadd = 0;
	for (int i = 1; i < siz; i += 2) {//�ڵ����ݳ�ʼ��,ʹ���������������������Ľṹ(����һ���Ϸ�������������������ʽ)
		List[i].l = i - 1; List[i].r = i + 1;
		List[i].op = getRandomOperator();
		List[i].checkeq = List[i].eq = List[i].op;
		List[i].bracketadd = false;
		priority.push_back(i);
		List[i + 1].l = i; List[i + 1].r = i + 2;
		List[i + 1].fr.random_init();
		List[i + 1].checkeq = List[i + 1].eq = List[i + 1].fr.write();
		List[i + 1].bracketadd = false;
	}

	random_shuffle(priority.begin(), priority.end());//��������Ի����������������ȼ�
	for (auto id : priority)
	{
		/*
		�úϲ����̿��Կ����������ݽڵ����ȼ�����һ����
		��ʼÿ���ڵ��Ӧ�ֱ�һ���Ϸ�������������������ʽ�����ֺ������
		�����ȼ��𼶲������ϵ�������ڵ㣬ÿ�ζ�һ��������ڵ����ʱ��
		���ȸ��������������ֽڵ�����ݸ��µ�ǰ������ڵ�Ӷ��õ��µ����ֽڵ㣬��������������ȼ��ж��Ƿ�������š�
		Ȼ���������ڵ����ֽڵ������ɾ�����ò���ͨ���޸��±�ʵ����ɾ��)
		��ʱ���Կ������ϵ�һ��������ڵ�������ڵ����ֽڵ�ϲ������µ����ֽڵ㡣
		�ظ����������������ϵ����нڵ�ϲ���ɣ�����ʣ�µĽڵ��������������ʽ����Ŀ����ʽ��
		�����ַ����������ֽڵ��ںϲ��а��ֵ����С�����кϲ���ʼ��������ŵĽ��(��ȷ�����޴ν�����ͬ���ַ���������ַ���һ����
		*/
		int lid = List[id].l, rid = List[id].r;//��ȡ��������Ԫ�ص��±�
		string lop = List[lid].l == -1 ? "#" : List[List[lid].l].op;//��ȡ���������ߵ������
		string rop = List[rid].r == siz ? "#" : List[List[rid].r].op;//��ȡ��������ұߵ������
		List[id].fr = autoCal(List[lid].fr, List[id].op, List[rid].fr);
		if (List[id].fr < 0) {//�ϲ��ڵ�ֵС��0�������ϲ�˳�򲢸�������
			if ((List[lid].op == "-" || List[lid].op == "+") && List[lid].bracketadd == false) {
				List[lid].eq = '(' + List[lid].eq + ')';
				List[lid].bracketadd = true;
			}
			if ((List[rid].op == "-" || List[rid].op == "+") && List[rid].bracketadd == true) {
				List[rid].eq = List[rid].eq.substr(1, (int)List[rid].eq.size() - 2);
				List[rid].bracketadd = false;
			}
			List[lid].swapkey(List[rid]);//�����ڵ�Ĺؼ�ֵ
			List[id].fr = autoCal(List[lid].fr, List[id].op, List[rid].fr);
			if (List[id].fr.error_check())//��ʽ������̷�����0����
				return { Fraction(),"","","",0,0 };
		}

		if (getPriority(lop) < getPriority(List[id].op) && getPriority(List[id].op) >= getPriority(rop))//�������ȼ��ж��Ƿ��������
			List[id].eq = List[lid].eq + List[id].eq + List[rid].eq;
		else
		{
			if (getPriority(lop) >= getPriority(List[lid].op) && getPriority(List[lid].op) >= getPriority(List[id].op) && List[lid].bracketadd == true) {
				List[lid].eq = List[lid].eq.substr(1, (int)List[lid].eq.size() - 2);//�Ƴ�����Ҫ������
				List[lid].bracketadd = false;
			}
			List[id].eq = '(' + List[lid].eq + List[id].eq + List[rid].eq + ')';
			List[id].bracketadd = true;
		}

		if ((List[id].op == "+" || List[id].op == "*") && List[lid].checkeq > List[rid].checkeq)//checkȫ�̼����Ų��ܱ�֤������ȷ��
			List[id].checkeq = '(' + List[rid].checkeq + List[id].checkeq + List[lid].checkeq + ')';
		else
			List[id].checkeq = '(' + List[lid].checkeq + List[id].checkeq + List[rid].checkeq + ')';

		List[id].r = List[rid].r;
		List[id].l = List[lid].l;
		if (List[id].l != -1)  List[List[id].l].r = id;
		if (List[id].r != siz) List[List[id].r].l = id;
	}
	Node ans = List[priority.back()];
	if (vis.find(ans.checkeq) != vis.end())
		return { Fraction(),"","","",0,0 };
	vis.insert(ans.checkeq);
	return ans;
}