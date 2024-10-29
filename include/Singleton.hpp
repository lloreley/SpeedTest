#ifndef SINGLETON
#define SINGLETON

template <class T>
class Singleton
{
protected:
    Singleton() {};
    ~Singleton() {};
    static T *instance;

public:
    Singleton(const Singleton &) = delete;
    T &operator=(const Singleton &) = delete;

    static T &getInstance()
    {
        if (!instance)
        {
            instance = new T;
        }
        return *instance;
    }
};
template <class T>
T *Singleton<T>::instance = nullptr;
#endif