#include"space.h"
#include<d3d9.h>
#include<string>
#include"tools.h"


pao::pao(std::string inname)
{
	name = inname;
}

int pao::hpc(int & inint)
{
	hp = hp + inint;
	return 0;
}

int pao::gjout()
{
	return gj;
}


pusher::pusher(std::string inname)
{
	name = inname;
}

pusher::~pusher()
{
}

int pusher::hpc(int & inint)
{
	hp = hp + inint;
	return 0;
}

int pusher::nout()
{
	return n;
}
