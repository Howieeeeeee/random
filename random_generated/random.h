#pragma once

#ifndef RANDOM_H
#define RANDOM_H

#include <utility>
#include <set>
#include <vector>
//#include <chrono>

#define MAX_RESTAURANT_NUM 1000

typedef std::pair<double, double> Make_Pair;

namespace randomA 
{
class Coordiante
{
public:
	static std::set<double> m_set;
public:
	Coordiante() = delete;
	Coordiante(int index, double h, double v, double r);
public:
	double GetXLocation();
	double GetYLocation();
	double GetRadius();
	double GetX();
	double GetY();
	int GetIndex();
private:
	Make_Pair m_coordiate;
	double m_horizon;
	double m_vertical;
	double centre_h;
	double centre_v;
	double radius;
	int m_index;
};

class Restaurant;
class Customer : public Coordiante
{
public:
	Customer(Restaurant* pRestaurant, int index, double h, double v, double r);
public:
	double GetDuration();
	void SetTime(double readytime);
private:
	double m_duration;
	Restaurant* m_pRestaurant;
};
class Restaurant : public Coordiante
{
public:
	Restaurant(int index, double h, double v, double r);
public:
	void CreateCustomer();
	void CreateCustomerOtherZone(int index, double h, double v, double r);
	Customer* GetCustomer();
	double GetReadyTime();
private:
	double ReadyTimeMinimum;
	double ReadyTimeMaximum;
	double m_readytime;
	Customer* m_pCustomer;

};
class RandomGenerator
{
public:
	RandomGenerator() = default;
	~RandomGenerator();
public:
	void Create(int num, int index, double h, double v, double r);
	Restaurant* GetRestaurantList(int index);
private:
	Restaurant* m_pRestaurantList[MAX_RESTAURANT_NUM];
};
}

#endif