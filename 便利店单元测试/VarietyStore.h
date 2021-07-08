#include <string>
#include <vector>

using namespace std;

/**
 * @author jarenzhang
 * ����˵�����Ĵ���
 */
class Item
{
public:
    string name;
    int sellDeadline;
    int price;
    Item(string name, int sellDeadline, int price) : name(name), sellDeadline(sellDeadline), price(price)
    {}
    virtual void updateItem();
};


class VarietyStore
{
public:
    //vector<Item>& items;
     // VarietyStore(vector<Item>& items);
    vector<Item*> items;
    VarietyStore();
 
    void addItem(Item* rhs);
    void updateItems();
private:
	void updateSingleItem(int idx);
};


class Maotai :public Item { //ę́
public:
    Maotai(string name, int sellDeadline, int price) :Item(name, sellDeadline, price) {}
    virtual void updateItem() override;
};

class Kimi :public Item {  //�����
public:
    Kimi(string name, int sellDeadline, int price) :Item(name, sellDeadline, price) {}
    virtual void updateItem() override;
};

class Diamond :public Item {  //��ʯ
public:
    Diamond(string name, int sellDeadline, int price) :Item(name, sellDeadline, price) {}
    virtual void updateItem() override;
};


class Banana :public Item { //�㽶
public:
    Banana(string name, int sellDeadline, int price) :Item(name, sellDeadline, price) {}
    virtual void updateItem() override;
};