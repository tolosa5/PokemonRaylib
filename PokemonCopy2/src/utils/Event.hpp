#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include <map>
#include <vector>
#include <functional>

using namespace std;

template <typename... Args>
class Event
{
public:
    using Callback = function<void(Args...)>;

    void Subscribe(Callback callback)
    {
        listeners.push_back(callback);
    }

    void Invoke(Args... arg)
    {
        for (auto& callback : listeners)
        {
            callback(arg...);
        }
    }

private:
    vector<Callback> listeners;
};

#endif