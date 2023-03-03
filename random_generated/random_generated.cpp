#include "random.h"
#include <pthread.h>

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
void Customer::SetIsDead(bool Dead)
{
	isDead = Dead;
}
bool Customer::GetIsDead()
{
	return isDead;
}

void* scan(void* args)
{
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> tm = end - RandomGenerator::m_starttime;
	if (!Coordiante::m_set.empty())
	{
		double duration = tm.count();
		auto it_index = Coordiante::m_set.lower_bound(duration);
		for (auto it = Coordiante::m_set.begin(); it != it_index; it++)
		{
			auto deadline = *it_index;
			for (int i = 0;i < RandomGenerator::m_samplelist.size();i++)
			{
				if (RandomGenerator::m_samplelist[i]->GetDuration() < deadline)
				{
					RandomGenerator::m_samplelist[i]->SetIsDead(true);
				}
			}
		}
	}
}  

void RandomGenerator::Create()
{
	for (int i = 0; i < MAX_NUM; ++i)
	{
		if (i == 0)
		{
			int ret = pthread_create(&m_threadid, NULL, scan, NULL);
			m_starttime = std::chrono::high_resolution_clock::now();
			if (ret)
			{
				return;
			}
		}
		m_samplelist[i] = new Customer(1, 2, 2, 2);
	}
}
