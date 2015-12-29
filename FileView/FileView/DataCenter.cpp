#include "stdafx.h"
#include "DataCenter.h"

CDataCenter * CDataCenter::m_SingleDataCenter = NULL;

CDataCenter::~CDataCenter()
{

}

CDataCenter::CDataCenter()
{

}

CDataCenter * CDataCenter::SingleInstance()
{
    if (m_SingleDataCenter == NULL)
    {
        m_SingleDataCenter = new CDataCenter;	

        static destroy des;
    }

    return m_SingleDataCenter;
}

CDataCenter::destroy::destroy()
{

}

CDataCenter::destroy::~destroy()
{
    if (CDataCenter::m_SingleDataCenter != NULL)
    {        
        delete CDataCenter::m_SingleDataCenter;
    }
}
