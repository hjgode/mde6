// MDEStringArray.cpp: implementation of the MDEStringArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MDEStringArray::MDEStringArray() : CStringArray()
{
}
//---------------------------------------------------------------------
void MDEStringArray::Swap(int i, int j)
{
CString tmp(GetAt(i));
SetAt(i,GetAt(j));
SetAt(j,tmp);
}
//---------------------------------------------------------------------
void MDEStringArray::Sort(BOOL sortDown,BOOL compareNoCase)
{
if(sortDown)
    {
    for(int i = 0; i < GetCount()-1; i++)
        {
        for(int j = i+1; j < GetCount(); j++)
            {
            if(compareNoCase)
                {
                if(GetAt(i).CompareNoCase(GetAt(j)) > 0)
                    Swap(i,j);
                }
            else
                {
                if(GetAt(i).Compare(GetAt(j)) > 0)
                    Swap(i,j);
                }
            }
        }
    }
else
    {
    for(int i = 0; i < GetCount()-1; i++)
        {
        for(int j = i+1; j < GetCount(); j++)
            {
            if(compareNoCase)
                {
                if(GetAt(i).CompareNoCase(GetAt(j)) < 0)
                    Swap(i,j);
                }
            else
                {
                if(GetAt(i).Compare(GetAt(j)) < 0)
                    Swap(i,j);
                }
            }
        }
    }
}
