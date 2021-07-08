#include "pch.h"
#include "VarietyStore.h"

#include <iostream>

using namespace std;

ostream& operator<<(ostream& s, Item* item)
{
	s << item->name << ", " << item->sellDeadline << ", " << item->price;
	return s;
}

/*
int fun()
{
	vector<Item> items;
	items.push_back(Item("���", 10, 20));
	items.push_back(Item("ę́", 2, 0));
	items.push_back(Item("������", 5, 7));
	items.push_back(Item("���", 0, 80));
	items.push_back(Item("���", -1, 80));
	items.push_back(Item("�����", 15, 20));
	items.push_back(Item("�����", 10, 49));
	items.push_back(Item("�����", 5, 49));
	//TODO �㽶 �����Ʒ�Ĺ����߼���û�����
	items.push_back(Item("�㽶", 3, 6));
	VarietyStore app(items);

	cout << "��ӭ���� 8-12 ������!" << endl;

	for (int day = 0; day <= 30; day++)
	{
		cout << "-------- �� " << day << " �� --------" << endl;
		cout << "����, ������, ��Ǯ" << endl;
		for (vector<Item>::iterator i = items.begin(); i != items.end(); i++)
		{
			cout << *i << endl;
		}
		//cout << endl;

		app.updateItems();
	}

}
*/

/*
int main() {
	Item *p1 = new Item("���", 10, 20);
	auto *p2 = new Maotai("ę́", 2, 0);
	auto *p3 = new Item("������", 5, 7);
	auto *p4 = new Diamond("���", 0, 80);
	auto *p5 = new Diamond("���", -1, 80);
	auto *p6 = new Kimi("�����", 15, 20);
	auto *p7 = new Kimi("�����", 10, 49);
	auto *p8 = new Kimi("�����", 5, 49);
	auto* p9 = new Banana("�㽶", 3, 6);
	VarietyStore app;
	app.addItem(p1);
	app.addItem(p2);
	app.addItem(p3);
	app.addItem(p4);
	app.addItem(p5);
	app.addItem(p6);
	app.addItem(p7);
	app.addItem(p8);
	app.addItem(p9);

	cout << "��ӭ���� 8-12 ������!" << endl;

	for (int day = 0; day <= 30; day++)
	{
		cout << "-------- �� " << day << " �� --------" << endl;
		cout << "����, ������, ��Ǯ" << endl;
		for (auto i = app.items.begin(); i != app.items.end(); i++)
		{
			cout << *i << endl;
		}
		app.updateItems();
		cout << endl;
	}
}

*/