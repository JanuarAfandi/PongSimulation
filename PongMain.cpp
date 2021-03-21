#include <iostream>
#include <thread>
#include <stdlib.h>
#include <chrono>
#include <random>
#include <mutex>
#include "Players.h"
#include "Score.h"

using namespace std;

Score score(0, 0); //Global variable
mutex m;

void randomFirstTurn(int* player)
{

	int* i = new int;
	srand((int)i);
	delete i;
	*player = rand() % 2;
}

void PLayerHitRandoms(Player* player, bool* isOver)
{

	int* i = new int;
	m.lock();
	//random number 0-100
	srand((int)i);
	delete i;
	player->SetHits(rand() % 100);
	m.unlock();

	
	cout << "Hit (Point) : " << player->GetHits();
	if (player->GetPleyer() == 0) {
		cout << " Player X ";
	}
	else {
		cout << " Player Y ";
	}

	if (player->GetHits() <= 50)
	{
		if (player->GetPleyer() == 0)
		{
			cout << "Player Y Mendapat 1 Skor" << endl;
			score.AddSkorY();
		}
		else
		{
			cout << "Player X Mendapat 1 Skor" << endl;
			score.AddSkorX();
		}
		cout << "Tidak Kena" << endl;

		*isOver = true;
	}
	else
	{
		cout << "Kena" << endl;
	}

	this_thread::sleep_for(chrono::seconds(1));
}


int main()
{
	srand(time(0));

	Player playerX(0);

	Player playerY = playerX; //clone player

	int mulaiRonde = 1;
	while (score.skorX() < 10 && score.skorY() < 10)
	{
		int mulaiRandom;
		thread RandomFirst(randomFirstTurn, &mulaiRandom);
		RandomFirst.join();
		bool roundOver = false;

		cout << "Ronde : " << mulaiRonde << endl;
		while (roundOver == false) {
			if (mulaiRandom == 0)
			{
				cout << "Player X dapat giliran Pertama" << endl;

				thread playerXThread(PLayerHitRandoms, &playerX, &roundOver); //Thread PlayerX
				playerXThread.join();

				if (roundOver == true) {
					mulaiRonde++;
					break;
				}

				thread playerYThread(PLayerHitRandoms, &playerY, &roundOver); //Thread PlayerY
				playerYThread.join();

				if (roundOver == true) {
					mulaiRonde++;
					break;
				}
			}
			else if (mulaiRandom == 1)
			{
				cout << "Player Y dapat giliran Pertama" << endl;

				thread playerYThread(PLayerHitRandoms, &playerY, &roundOver);
				playerYThread.join();

				if (roundOver == true)
				{
					mulaiRonde++;
					break;
				}

				thread playerXThread(PLayerHitRandoms, &playerX, &roundOver);
				playerXThread.join();

				if (roundOver == true) {
					mulaiRonde++;
					break;
				}
			}
		}
	}
	//Winning Announcement
	cout << "\nHsil" << endl;
	if (score.skorX() >= 10) {
		cout << "Player X Menang :  " << endl << score.skorX() << "-" << score.skorY() << endl;
	}
	else {
		cout << "Player Y Menang :  " << endl << score.skorY() << "-" << score.skorX() << endl;
	}

	return 0;
}