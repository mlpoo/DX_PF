#pragma once

template<typename T>
class Singleton
{
public :
    static T* GetInstance()
    {
        static T* instance = new T;
        return instance;
    }

    static void DeleteSingleton()
    { delete GetInstance(); }
};