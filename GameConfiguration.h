#pragma once
class GameConfiguration
{
public:
	bool sound_enabled;
	static void setSound(bool enabled);
private:
	GameConfiguration() {};
};