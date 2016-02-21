#include"space.h"
#include<d3d9.h>
#include<string>



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


