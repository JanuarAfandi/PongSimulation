
class Player //define player
{
private:

	float Hits;
	enum Players { playerX, playerY } player;

public:

	float GetHits()
	{
		return Hits;
	}

	void SetHits(float h)
	{
		Hits = h;
	}

	Players GetPleyer()
	{
		return player;
	}

	Player(int p)
	{
		if (p == 0)
		{
			player = Players::playerX;
		}
		else
		{
			player = Players::playerY;
		}
		Hits = 0;
	}
	Player(Player& p)
	{
		if (p.player == Players::playerX)
		{
			player = Players::playerY;
		}
		else
		{
			player = Players::playerX;
		}
		Hits = p.Hits;
	}

};
