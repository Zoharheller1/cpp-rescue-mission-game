#pragma once

class Observer;
class Subject {
public:
    virtual ~Subject() {}
    virtual void attachObserver(Observer* observer) = 0;
    virtual void detachObserver() = 0;
    virtual void notifyObservers() = 0;
};
