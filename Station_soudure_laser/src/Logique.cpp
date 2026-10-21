#include "Logique.hpp"

Logique::Logique(CreateSlave slave) : slaveLaser(slave) {}

TypeSortie Logique::entryExitDef(int entryData, int exitData)
{
    readingLaser1 = entryData;
    readingLaser2 = exitData;
    
    if(readingLaser1 == HIGH && readingLaser2 == LOW)
    {
        entryExitType = TypeSortie::Enter;
        return entryExitType;
    }
    else if(readingLaser1 == LOW && readingLaser2 == HIGH)
    {
        entryExitType = TypeSortie::Exit;
        return entryExitType;
    }
    else if(readingLaser1 == HIGH && readingLaser2 == HIGH)
    {
        entryExitType = TypeSortie::InOut;
        return entryExitType;
    }
    else if(readingLaser1 == LOW && readingLaser2 == LOW)
    {
        entryExitType = TypeSortie::NoEntryExit;
    }
}

int Logique::peopleCounter(TypeSortie type)
{
    TypeSortie typeLaser = type;
    peopleCount = 0;

    if(typeLaser == TypeSortie::Enter)
    {
        peopleCount = 1;
        return peopleCount;
    }
    else if(typeLaser == TypeSortie::Exit)
    {
        peopleCount = -1;
        return peopleCount;
    }
    else if(typeLaser == TypeSortie::InOut || typeLaser == TypeSortie::NoEntryExit)
    {
        peopleCount = 0;
        return peopleCount;
    }
}