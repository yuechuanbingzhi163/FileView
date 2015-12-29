#pragma once
#include "stdafx.h"
#include <list>

class CDataCenter
{
public:    
    ~CDataCenter();

    static CDataCenter *SingleInstance();

private:
    static CDataCenter *m_SingleDataCenter;

private:
    CDataCenter();

    class destroy
    {
    public:
        destroy();
        ~destroy();
    };

};

