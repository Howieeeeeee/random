#include "random.h"
#include <math.h>

using namespace randomA;

Coordiante::Coordiante(int index, double h, double v, double r)
	: m_index(index)
	, centre_h(h)
	, centre_v(v)
	, radius(r)
	, m_coordiate(0,0)
{
	m_horizon = centre_h;
	m_vertical = centre_v;

	//double x = (2 * (double)rand() / RAND_MAX - 1.0) * radius;
	//double y = (2 * (double)rand() / RAND_MAX - 1.0) * radius;
	//if (x * x + y * y <= radius * radius)
	//{
	//	m_horizon = x + centre_h;
	//	m_vertical = y + centre_v;
	//	m_coordiate =  Make_Pair(m_horizon, m_vertical);
	//}

	double angle = (double)rand() / RAND_MAX * 360;
	double rad = (double)rand() / RAND_MAX * radius;
	m_horizon = rad * sin(angle) + centre_h;
	m_vertical = rad * cos(angle) + centre_v;
	m_coordiate = Make_Pair(m_horizon, m_vertical);
}

double Coordiante::GetXLocation()
{
	return centre_h;
}
double Coordiante::GetYLocation()
{
	return centre_v;
}
double Coordiante::GetRadius()
{
	return radius;
}
double Coordiante::GetX()
{
	return m_horizon;
}
double Coordiante::GetY()
{
	return m_vertical;
}
int Coordiante::GetIndex()
{
	return m_index;
}

Customer::Customer(Restaurant* pRestaurant, int index, double h, double v, double r)
	: Coordiante(index, h, v, r)
	, m_pRestaurant(pRestaurant)
{
	double distance = pow(pow(fabs(pRestaurant->GetX() - this->GetX()), 2) + pow(fabs(pRestaurant->GetY() - this->GetY()), 2), 0.5);
	m_duration = distance * 1.0 * rand() / RAND_MAX * 1.5;
}
double Customer::GetDuration()
{
	return m_duration;
} 
void Customer::SetTime(double readytime)
{
	m_duration += readytime;
}
Restaurant::Restaurant(int index, double h, double v, double r)
	: Coordiante(index, h, v, r)
	, ReadyTimeMinimum(10)
	, ReadyTimeMaximum(100)
	, m_pCustomer(nullptr)
{
	m_readytime = ReadyTimeMinimum;
	m_readytime += 1.0 * rand() / RAND_MAX * (ReadyTimeMaximum - ReadyTimeMinimum);
}
void Restaurant::CreateCustomer()
{
	m_pCustomer = new Customer(this, this->GetIndex(),this->GetXLocation(),
		this->GetYLocation(), this->GetRadius());
	m_pCustomer->SetTime(m_readytime);
}
void Restaurant::CreateCustomerOtherZone(int index, double h, double v, double r)
{
	m_pCustomer = new Customer(this, index, h, v, r);
	m_pCustomer->SetTime(m_readytime);
}
double Restaurant::GetReadyTime()
{
	return m_readytime;
}
Customer* Restaurant::GetCustomer()
{
	return m_pCustomer;
}
RandomGenerator::~RandomGenerator()
{
	for (auto it : m_pRestaurantList)
	{
		if (it)
		{
			delete it;
			it = nullptr;
		}
	}
}
void RandomGenerator::Create(int num, int index, double h, double v, double r)
{
	if (num <= MAX_RESTAURANT_NUM)
	{
		for (int i = 0; i < num; ++i)
		{
			m_pRestaurantList[i] = new Restaurant(index, h, v, r);
		}
	}
}
Restaurant* RandomGenerator::GetRestaurantList(int index)
{
	return m_pRestaurantList[index];
}
