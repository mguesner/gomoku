#include "Sound.hpp"

Sound::Sound()
{

}

Sound::Sound(int i)
{
	willPlay = i;

}

bool Sound::Play()
{
	son = fork();
	if (son == 0)
	{
		if (willPlay == 5)
			execl("/usr/bin/afplay", "afplay", "Scott D. Davis - Master Of Puppets.mp3", (char *) 0);
		execl("/usr/bin/afplay", "afplay", "Scott D. Davis - Master Of Puppets.mp3", (char *) 0);
		perror("failed music");
		exit(0);
	}
	return true;
}

bool Sound::Stop()
{
	if (!kill(son, SIGTERM))
		return true;
	else if (!kill(son, SIGKILL))
		return true;
	return false;
}

Sound::~Sound()
{
	Stop();
}
