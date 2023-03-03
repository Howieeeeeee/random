#pragma once

#ifndef RANDOM_H
#define RANDOM_H

#include <utility>
#include <set>
#include <vector>

#define MAX_NUM 100000

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
	Make_Pair RandomGenerate();
	double GetXLocation();
	double GetYLocation();
	int GetIndex();
	void AddDuration(double duration);
private:
	Make_Pair m_coordiate;
	double m_horizon;
	double m_vertical;
	double centre_h;
	double centre_v;
	double radius;
	int m_index;
};
 
class Restaurant : public Coordiante
{
public:
private:
	double m_readytime;
	
};
class Customer : public Coordiante
{
public:
	Customer(int index, double h, double v, double r);
public:
	double GetDuration();
private:
	double m_duration;
	double startTime;
	double endTime;
};
class Rider : public Coordiante
{

};

class RandomGenerator
{
public:
	RandomGenerator() = default;
public:
	void Create();
private:
	std::vector<Coordiante*> m_samplelist;

};

}

#endif