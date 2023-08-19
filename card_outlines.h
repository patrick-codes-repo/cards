#include <string.h>
#include <utility>
#include <iomanip>
#include "abilities.h"


using namespace std;

class card
{
	protected:
		int cost;
		string name;
	public:
		card(int c, string n)
		{
			cost = c;
			name = n;
		}

		void show_stats()
		{
			cout << "Name: " << name << "\tCost: " << cost << endl;
		}	
};

class unit : public card
{
	protected:
		int health;
		int damage;

	public:
		unit(int c, string n, int h, int d) : card(c, n)
		{
			health = h;
			damage = d;
		}
		void attack()
		{
			cout << "I am attacking" << endl;
			return;
		}

		void block()
		{
			cout << "I am blocking" << endl;
			return;
		}

		void show_stats()
		{
			card::show_stats();
			cout << "Health: " << health << "\tDamage: " << damage << endl;
		}
};

class ability_class
{
	protected:
		float *multipliers;
		int *abilities;
		int multipliers_size;
		int abilities_size;

	public:
		ability_class(int m, int a, float *mults, int *abils)
		{
			multipliers_size = m;
			multipliers = new float[m];
			abilities_size = a;
			abilities = new int[a];
			
			for(int i = 0; i < multipliers_size; i++)
			{
				multipliers[i] = mults[i];
			}

			for(int i = 0; i < abilities_size; i++)
			{
				abilities[i] = abils[i];
			}

		}

		void display_abilities()
		{
			string ability;
			int mult_count = 0;
			string number;
			string temp;

			for (int i = 0; i < abilities_size; i++)
			{
				ability = get_ability(abilities[i]);

				size_t pos = ability.find("1");
				while(pos != string::npos)
				{
					temp = "";
					number = to_string(multipliers[mult_count]);
					for(int x = 0; x < number.length(); x++)
					{
						if(number[x] != '0')
							temp += number[x];
					}
					if(temp[temp.length() -1] == '.')
						temp = temp.substr(0, temp.length() - 1);
					if(temp[0] == '.')
						temp = "0" + temp;
					number = temp;

					ability.replace(pos, 1, number);
					pos = ability.find("1", pos + number.length());
					//if(abilities[i] >= 50 && pos != string::npos)
					mult_count++;
				}
	
				cout << "My ability is: " << ability << endl;
			}
		}
};

class special: public unit, public ability_class 
{
	public:
		special(int c, string n, int h, int d, int m_s, int a_s, float *m, int *a) : unit(c, n, h, d), ability_class(m_s, a_s, m, a)
	{
	}

	void show_stats()
	{
		unit::show_stats();
		ability_class::display_abilities();
		cout << endl;
	}
};

class spell: public ability_class, public card
{
	public:
		spell(int c, string n, int m_s, int a_s, float *m, int *a) : card(c, n), ability_class(m_s, a_s, m, a)
	{
	}

	void show_stats()
	{
		card::show_stats();
		ability_class::display_abilities();
		cout << endl;
	}
};
