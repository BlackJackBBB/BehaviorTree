#pragma once
#include <unordered_set>


class IObserver {

	friend class Observable;

public:

	virtual ~IObserver() {}
	

private:

	virtual void observerCallback() = 0;

};


class Observable {
public:

	Observable();

	Observable& notifyObservers();

	Observable& detachObserver(IObserver& observer);

	Observable& attachObserver(IObserver& observer);

	bool hasAttachedObserver();

private:

	std::unordered_set<IObserver*> _observers;
	bool _isNotifying;

};


