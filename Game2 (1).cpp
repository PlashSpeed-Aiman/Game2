#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <string>


using namespace std;
//"#################################################################"//
void Level_One(void);
void Level_Two(void);
//void print_stats(class);
//int Combat(int &Character, int Enemy);//Passing Character by Reference
//void how_to_play(void);
//void Level_Two(void);
//void Level_Three(void);
//"#################################################################"//



class Character {


private:
    int experience ;
    int player_lvl ;
public:
    string char_name;
    int char_hp;
    int char_attack;
    int char_defence;
    int reset_hp;

    Character(int hp, int attack, int defence) {
        char_hp = hp;
        char_attack = attack;
        char_defence = defence;
        experience = 0;
        player_lvl = 1;
        reset_hp = hp;
    }

    void get_name() {
    	cin.ignore();
        getline(cin,char_name);
        cin.ignore();
    }
	
	int player_level(){
		return player_lvl;
	}
	int player_exp(){
		return experience;
	}
    void display_attribute() {
        cout << "Level:" << player_lvl << endl;
        cout << char_name << "'s" << " Health: "; 
        for(int x = 1;x<=char_hp;x++)
	    {
		cout << "|";
	    }
	    cout << "\n";
        cout << char_name << "'s" << " Attack: " << char_attack << endl;
        cout << char_name << "'s" << " Defence: " << char_defence << endl;
        cout << char_name << "'s" << " XP Points: " << experience << endl;
    }

    void get_dmg(int dmg) {
        char_hp = char_hp - dmg;
    }

    void heal(int x) {
        char_hp = char_hp + x;
    }

    int add_xp(int x) {
        experience += x;
        if (experience > 1000) {
            player_lvl++;
            cout << "Level Up!\n";
            experience = 0;
        }
    }
    int return_char_hp()
    {
        return char_hp;
    }
    
    void reset_player_health(){
    	char_hp = reset_hp;
	}
	
};

class Enemy {

public:
    string char_name;
    int char_hp;
    int char_attack;
    int char_defence;

    Enemy(string name, int hp, int attack, int defence) {
        char_name = name;
        char_hp = hp;
        char_attack = attack;
        char_defence = defence;

    }

    void display_attribute() {
        cout << char_name << "'s" << " Health: "; 
        for(int x = 1;x<=char_hp;x++)
	    {
		cout << "|";
	    }
	    cout << "\n";
        cout << char_name << "'s" << " Attack: " << char_attack << endl;
        cout << char_name << "'s" << " Defence: " << char_defence << endl;

    }

    void get_dmg(int dmg) {
        char_hp = char_hp - dmg;
    }

    void heal(int x) {
        char_hp = char_hp + x;
    }

    ~Enemy() {
    };

};

void print_stats(Character &player)
{
  ofstream outputFile;
  outputFile.open("Stats.txt");
  outputFile << "++++++++Player Stats+++++++\n";  
  outputFile << "Name:";
  outputFile << player.char_name;
  outputFile << "\nAttack: ";
  outputFile << player.char_attack;
  outputFile << "\nDefence: ";
  outputFile << player.char_defence;
  outputFile << "\nLevel: ";
  outputFile << player.player_level();
  outputFile << "\nXP Points: ";
  outputFile << player.player_exp();
  outputFile.close();
}

int Combat_Special(Character &player, Enemy enemy) {

    int choice, dmg_dealt_enemy, dmg_dealt_player, potion = 3;

    double chance_to_heal,chance_to_hit;

    cout << "Battle Commenced!\n";

//    cout << "1.Attack\n2.Heal\n";
    
    player.display_attribute();

    while (player.return_char_hp() > 0 && enemy.char_hp > 0) {

        cout << "1.Attack\n2.Heal\n3.Heavy Attack( Causes high damage but very high chances to miss)\n";
        
		cin >> choice;
        
        if (choice == 1) {

            chance_to_heal = rand() % 100;

            dmg_dealt_enemy = rand() % enemy.char_attack + 5;

            dmg_dealt_player = rand() % player.char_attack + 5;

            cout << "You have attacked the enemy and dealt " << dmg_dealt_player << " damage!" << endl;

            enemy.get_dmg(dmg_dealt_player);

            if (enemy.char_hp >= 0)

                enemy.display_attribute();

            else if (enemy.char_hp < 0) {
                enemy.char_hp = 0;
                enemy.display_attribute();
            }

            player.add_xp(rand() % 200 + 100);

            cout << "The Enemy attacked You and dealt " << dmg_dealt_enemy << " damage!" << endl;

            player.get_dmg(dmg_dealt_enemy);

            player.display_attribute();
            
            if (chance_to_heal > 60) {
                cout << "Enemy healed himself!\n";
                enemy.heal(rand() % 7 + 3);
            }

        } else if (choice == 2) {

            if (potion > 0) {
                player.heal(rand() % 7 + 3);
                player.display_attribute();
                potion--;
                cout << "Potion:" << potion << endl;
            } 
			else
                cout << "You ran out of Potions!";
			
			}
			
			else if(choice == 3)
			{
				chance_to_heal = rand() % 100;
            	
				dmg_dealt_enemy = rand() % enemy.char_attack + 5;
                
				dmg_dealt_player = rand() % player.char_attack + 5;
				
				chance_to_hit = rand() % 100 + 30;
				
				if(chance_to_hit >= 75.0){
				
				enemy.get_dmg(dmg_dealt_player + 20);
			
				player.get_dmg(dmg_dealt_enemy);
				
				enemy.display_attribute();
				
				player.display_attribute();
			}
				else
				{
				cout<< "You missed!" << endl;
				
				player.get_dmg(dmg_dealt_enemy);
				
				enemy.display_attribute();
				
				player.display_attribute();
				}
				
			}
        if (player.char_hp <= 0)
            
			return 1;
            
        else if(enemy.char_hp <=0)
        	{
			player.reset_player_health();
			cout << "Player Survived!" << endl;
			cout << "Enemy is Dead!" << endl;
			return 0;
        }
            
    }
}

int Combat(Character &player, Enemy enemy) {

    int choice, dmg_dealt_enemy, dmg_dealt_player, potion = 3;

    double chance_to_heal;

    cout << "Battle Commenced!\n";

    cout << "1.Attack\n2.Heal\n";
    
    player.display_attribute();

    while (player.return_char_hp() > 0 && enemy.char_hp > 0) {

        cin >> choice;
        cout << "1.Attack\n2.Heal\n";
        system("cls");
        if (choice == 1) {

            chance_to_heal = rand() % 100;

            dmg_dealt_enemy = rand() % enemy.char_attack + 5;

            dmg_dealt_player = rand() % player.char_attack + 5;

			enemy.get_dmg(dmg_dealt_player);

            player.add_xp(rand() % 200 + 100);
            
            cout << "You have attacked the enemy and dealt " << dmg_dealt_player << " damage!" << endl;

            player.get_dmg(dmg_dealt_enemy);

            player.display_attribute();
            
            cout << "The Enemy attacked You and dealt " << dmg_dealt_enemy << " damage!" << endl;

            if (chance_to_heal > 60) {
                cout << "Enemy healed himself!\n";
                enemy.heal(rand() % 7 + 3);
            }
            ////////////////////////////////////////////////////
            if (enemy.char_hp >= 0)

                enemy.display_attribute();

            else if (enemy.char_hp < 0) {
                enemy.char_hp = 0;
                enemy.display_attribute();
            }

        } else if (choice == 2) {

            if (potion > 0) {
                player.heal(rand() % 9 + 3);
                player.display_attribute();
                potion--;
                cout << "Potion:" << potion << endl;
            } else

                cout << "You ran out of Potions!";

        }
        
        
        if (player.char_hp <= 0)
            return 1;
        else if(enemy.char_hp <=0)
        	{
			player.reset_player_health();
			cout << "Player Survived!" << endl;
			cout << "Enemy is Dead!" << endl;
			return 0;
        }
            
    }
    return 0;
}

void Level_One() {
    Character Player(110, 20, 10);
    Enemy Warrior("Warrior", 100, 18, 10);
    int choice, Game_Over;

    cout << "What is your name?\n" << endl;
    Player.get_name();
    cout << "Welcome young " << Player.char_name << endl;
    cout << "You have given 2 choices either to protect your village or go to the frontline and fight Your Enemy "
         << endl;
    cout << "Are you ready " << Player.char_name << " ? " << " (select path 1 or path 2 )" << endl;
    cout << "Enter your Path : " << endl;

    cin >> choice;
    
    if (choice == 1) {
        cout << "\n!!!----------------------Chapter One: Fight----------------------!!!" << endl;
        cout << "\nYou: Where are we going?" << endl;
        cout << "Old warrior: Soon you will know. Just keep walking and focus to your surrounding. " << endl;
        cout << "# Wush!!!\n" << "# You confront the enemy Knight in the Battlefield " << endl;
    } else if (choice == 2) {
        cout << "\n!!!----------------------Chapter One: Defend----------------------!!!" << endl;
        cout << "\nWar Chief : We must prepare for battle, the enemy are marching toward our village. brace youself. "
             << endl;
        cout << "War Chief: Be brave young warrior, you may live to tell the story or die within the history. " << endl;
        cout << "You: Yes sir!!" << endl;
        cout << "# You starting to hear the enemy war cry " << endl;
        cout << "# You confront the enemy Knight " << endl;
    }
    else
    {
    	cout << "Wrong Input" << endl;
    	cin  >> choice;
	}

    Game_Over = Combat(Player, Warrior);
    if (Game_Over == 1) {
        cout << "You Died\n" << "Game Over!" << endl;
        print_stats(Player);
//        exit(0);
        return;
    } else;

    cout << "War Chief : WOW! I have never see a mere foot soldier defeat an enemy knight." << endl;
    cout << "War Chief : You may be the next King's head knight someday. " << endl;
    cout << "You : I was just lucky, today must be my lucky day HaHaHa " << endl;
    cout << "# Suddenly the ground shook like an earth quick ." << endl;
    cout << "# There is a huge looking soldier with a massive battle axe coming toward you.  " << endl;
    cout << "# It almost seem like you will be defeated by it" << endl;
    cout << " Are going to fight or retreat? " << " (Press 1 to Fight or 2 to Retreat)" << endl;

    cin >> choice;
    if (choice == 1) {
        cout << "\n!!!----------------------Chapter Two: Survive----------------------!!!" << endl;
        cout << "\nYou : The enemy is to strong, arghhhh!!" << endl;
        cout << "War Chief : We must keep fighting and wait for the back up. " << endl;
        cout << "# You will fight the huge looking soldier.  " << endl;
    } else if (choice == 2) {
        cout << "\n!!!----------------------Chapter Two: Regroup----------------------!!!" << endl;
        cout << "\nWar Chief : We must split up. " << endl;
        cout << "You: Yeah, you are right. " << endl;
        cout << "You: Lets meet at the Base camp" << endl;
        cout << "# You been chase in the forest and suddenly ....... Dead end .. " << endl;
        cout << "# It looks like you meet a dead end, there is no choice but Fight" << endl;
        cout << "# You confront the Huge soldier. " << endl;
    }
//second function combat with upgraded hp strength and Def
    Game_Over = Combat(Player, Warrior);
    if (Game_Over == 1) {
        cout << "You Died\n" << "Game Over!" << endl;
	print_stats(Player);
//        exit(0);
        return;
    } else;
    
    cout << "# Apparently the huge soldier is a mutant that been biologically engineered to fight us. " << endl;
    cout << "# You have fought bravely and win many fight \n" << endl;
    cout << "#You have win the Battle . CONGraTulaTion....!!" << endl;
	print_stats(Player);
	return;

}

void Level_Two(){
	Enemy Mage("Mage",120,20,5);
	Character Player(110, 20, 10);
	int Game_Over;
	cout << "What is your name, young one?" << endl;
	Player.get_name();
	cout<<"# After your deadly fight, King and The Ruler of The empire Adib Alexander The Third order you to meet a mage named Bloise at the Empire mage school in Hagworth."<<endl;
	cout<<"# Bloise He is known to be the master of the current great sorcerer, Mordorx."<<endl;
	cout<<"#............................................................................................................................\n "<<endl;
	cout<<" Bloise: Hello "<<Player.char_name<<". I have see fight bravely in the war. Your are really unpredictable person, even I can't foresee your future."<<endl;
	cout<<" You: Thanks for the compliment I guess.\n"<<endl;
	cout<<" Bloise: As a gift I will teach you a couple of spells" <<endl;
	cout<<" Bloise: The first spell is called Debilitation and the second is Recovery that you talentedly used in the fight unconsciouslys"<<endl;
	cout<<" Bloise: Debilitation is a spell that can weaken your enemy Defence when you are in battle. But it has it has it rebound after you......\n"<<endl; 
	cout<<" # KAAABoooooMMMM...,"<<endl;
	cout<<" Bloise: I think you will figure it out own your own, this school have been attack you must protect this school. I will help the student escape. " <<endl;
	cout<<" # Pooofft You been teleport to the hall. As you walk at the hall you have encountered a man wearing a black cape.\n"<<endl;
	
    Game_Over = Combat_Special(Player, Mage);
    if (Game_Over == 1) {
    	print_stats(Player);
        cout << "You Died\n" << "Game Over!" << endl;
        return;
    } else;
    Sleep(100);

	cout<<" # As you fight the Black mage, Bloise come and stop the battle. As soon as the black mage saw Bloise, he teleport himself cowardly."<<endl;
	cout<<" # You have survive the deadly match with the  Black mage.\n"<<endl;
	
	cout<<" Bloise: As I expected you can't defeat him now. Not the current you. Do you have any idea who do you against with?"<<endl;
	cout<<" Bloise: That is Mordorx my ex student who turn against the Empire. He must have here to kill you."<<endl;
	cout<<" You   : But, why me?? He does not even know me. "<<endl;
	cout<<" Bloise: It because you have quality and potential to replace me and you can even surpass me."<<endl;
	cout<<" Bloise: He betray me because His thirst for Power. All he thinks about how to get more powerful even he have to sacrifice everyone around him. \n"<<endl;
	
	cout<<" # After the attack you dicided to stay at the school and be Bloise's apprentice."<<endl;
	cout<<" # After a few month of training Mordorx come and attack The mage school again, but now he is more powerfull then the last fight"<<endl;
	cout<<" Bloise : Go my apprentice, defeat him and fulfill your destiny.\n"<<endl;
	
//	combat function 2
    Game_Over = Combat_Special(Player, Mage);
    if (Game_Over == 1) {
    	print_stats(Player);
        cout << "You Died\n" << "Game Over!" << endl;
        return;
    } else;

	cout<<" # You have defeat Mordorx Congratulation........... "<<endl;
	system ("pause");
	print_stats(Player);
	return ;
	
}

int main() {
	system("color 4F");
	puts("####################################################");
	puts("++++++++WELCOME TO OUR TEXT ADVENTURE GAME!+++++++++");
	puts("####################################################");
    	
	
	char harith;
	
	int choice;
	
	int reset_count=0;
    
	while(reset_count <= 0){	
    
	cout << "1.Level 1\n" << "2.Level 2\n" << "3.Exit Game\n" << endl;
    
	cout << "Input a choice:\t";
    
	cin >> choice;
    
	switch (choice) {
    
	    case 1:
    
	        cout << "Level 1" << endl;
    
	        Level_One();
    
	        break;
    
	    case 2:
    
	        cout << "Level 2" << endl;
    		
    		Level_Two();
    
	        break;
    
	    case 3:
    
	        cout << "Exit Game" << endl;
    
	    default:
        ;			
    }
    
    fflush(stdin);
    
	cout<<"Do you wish to continue the game (Y/N) ";
	
	harith= getchar();
	
	if(harith == 'Y' || harith == 'y')
	{
		reset_count = 0;
		system("cls");
	}
	else if(harith == 'N'|| harith == 'n')
		
		reset_count = 1;
		system("cls");

};    
    return 0;
}
