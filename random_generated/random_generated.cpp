#include "random.h"

using namespace randomA;

Coordiante::Coordiante(int index, double h, double v, double r)
	: m_index(index)
	, centre_h(h)
	, centre_v(v)
	, radius(r)
{
	m_horizon = centre_h;
	m_vertical = centre_v;
}

Coordiante::~Coordiante()
{
}

double Coordiante::GetXLocation()
{
	return m_horizon;
}
double Coordiante::GetYLocation()
{
	return m_vertical;
}
int Coordiante::GetIndex()
{
	return m_index;
}
Make_Pair Coordiante::RandomGenerate()
{
	double x = (2 * (double)rand() / RAND_MAX - 1.0) * radius;
	double y = (2 * (double)rand() / RAND_MAX - 1.0) * radius;
	if ( x * x + y * y <= radius * radius)
	{
		m_horizon = x + centre_h;
		m_vertical = y + centre_v;
		Make_Pair coordianate(m_horizon, m_vertical);
		return coordianate;
	}
	return;
}
void Coordiante::AddDuration(double duration)
{
	m_set.insert(duration);
}

Customer::Customer(int index, double h, double v, double r)
	: Coordiante(index, h, v, r)
{
	m_duration = startTime; 
	m_duration += 1.0 * rand() / RAND_MAX * (endTime - startTime);
	AddDuration(m_duration);
}

double Customer::GetDuration()
{
	return m_duration;
}

void RandomGenerator::Create()
{

	for (int i = 0; i < MAX_NUM; ++i)
	{
		m_samplelist[i] = new Customer(1, 2, 2, 2);
	}
}
