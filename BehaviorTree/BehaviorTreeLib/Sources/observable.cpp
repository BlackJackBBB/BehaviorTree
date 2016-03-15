#include <pch.h>
#include <observer.h>


Observable::Observable() : 
	_isNotifying(false) 
{
	
}


Observable& Observable::notifyObservers() {

	_isNotifying = true;

	for (auto& observer : _observers)
		observer->observerCallback();

	_isNotifying = false;

	return *this;
}


Observable& Observable::attachObserver(IObserver& observer) {

	if (!_isNotifying)
		_observers.insert(&observer);
	
	return *this;
}


Observable& Observable::detachObserver(IObserver& observer) {

	if (!_isNotifying)
		_observers.erase(&observer);

	return *this;
}


bool Observable::hasAttachedObserver() {

	return !_observers.empty();
}