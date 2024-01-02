#include <iostream>

class Marine {
private:
    static int total_marine_num;
    int hp;
    int coord_x, coord_y;
    bool is_dead;
    const int default_damage;
public:
    Marine();
    Marine(int x, int y);
    Marine(int x, int y, int default_damage);

    int attack() const;
    Marine& be_attacked(int damage_earn); // return *this
    Marine& be_healed(int heal); // return *this

    void move(int x, int y);
    void show_status();
    static void show_total_marine();
    ~Marine() { total_marine_num--; }
    };
//----------------------------------------------------------------------------------

int Marine::total_marine_num = 0;
void Marine::show_total_marine() {
    std::cout << "Total Marine Number : " << total_marine_num << std::endl;
    }
Marine::Marine()
    : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
    total_marine_num++;
    }
Marine::Marine(int x, int y)
    : coord_x(x),
    coord_y(y),
    hp(50),
    default_damage(5),
    is_dead(false) {
    total_marine_num++;
    }
Marine::Marine(int x, int y, int default_damage)
    : coord_x(x),
    coord_y(y),
    hp(50),
    default_damage(default_damage),
    is_dead(false) {
    total_marine_num++;
    }
void Marine::move(int x, int y) {
    coord_x = x;
    coord_y = y;
    }
int Marine::attack() const { return default_damage; }
Marine& Marine::be_attacked(int damage_earn) {
    this->hp -= damage_earn;
    if (hp <= 0) is_dead = true;
    return *this;
    }

Marine& Marine::be_healed(int heal) {
    this->hp += heal;
	if (hp > 100) hp = 100;
	return *this;
	}


void Marine::show_status() {
    std::cout << this << " *** Marine *** " << std::endl;
    std::cout << " Location : ( " << coord_x << ", " << coord_y << " ) " << std::endl;
    std::cout << " HP : " << hp << std::endl;
    }
//----------------------------------------------------------------------------------

class Medic : public Marine {
public:
    int id;
public:
    Medic(int x, int y, int id);
    void heal(Marine* marine);
	};

//----------------------------------------------------------------------------------

Medic::Medic(int x, int y, int id)
	: Marine(x, y), id(id) {
	}

void Medic::heal(Marine* marine) {
	marine->be_healed(15);
    
	}


//----------------------------------------------------------------------------------

class ChiefMarine : public Marine {
public:
    int id;
public:
    ChiefMarine(int x, int y, int default_damage, int id);

    };
//----------------------------------------------------------------------------------

ChiefMarine::ChiefMarine(int x, int y, int default_damage, int id)
    : Marine(x, y, default_damage), id(id) {
    }


//----------------------------------------------------------------------------------




int main() {

    Marine marine1(2, 3, 10);
    marine1.show_status();
    Marine marine2(3, 5, 10);
    marine2.show_status();
    ChiefMarine chief_marine1(2, 3, 10, 1);
    chief_marine1.show_status();
    ChiefMarine chief_marine2(3, 5, 10, 2);
    chief_marine2.show_status();
    Medic medic1(1, 1, 1);
    medic1.show_status();
    
    std::cout << std::endl << chief_marine1.id << " attacks " << chief_marine2.id << std::endl;
    chief_marine2.be_attacked(chief_marine1.attack()).be_attacked(chief_marine1.attack());
        

    chief_marine1.show_status();
    chief_marine2.show_status();

    medic1.heal(&chief_marine2);
    std::cout << std::endl << "chief "<< chief_marine2.id << " is being healed by medic " << std::endl;
	chief_marine2.show_status();

    medic1.heal(&marine1);
    std::cout << std::endl << "marine1 is healed by medic  " << std::endl;
    marine1.show_status();


    Marine::show_total_marine();
    return 0;
    }
