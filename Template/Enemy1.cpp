#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Enemy1
{
private:
	string name;
	int damage;
	int health;

public:
	Enemy1(string n, int D, int H)
	{
		name = n;
		damage = D;
		health = H;
	}

	int getdamage() const
	{
		return damage;
	}

	int gethealth() const
	{
		return health;
	}

	string getEnemy1info()
	{
		stringstream e;
		e << "Enemy name: " << name << "\t Damage it can deal: " << damage
			<< "Health they have: " << health << endl;
		return e.str();
	}
};


int main()
{
	Enemy1 e1("Bobby", 17, 72);
	cout << e1.getEnemy1info();
	return 0;
}
