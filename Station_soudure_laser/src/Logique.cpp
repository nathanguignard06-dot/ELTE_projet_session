#include "Logique.hpp"

Logique::Logique(CreateSlave& slave) : slaveLaser(slave) {}

TypeSortie Logique::entryExitDef()
{
    readingLaser1 = slaveLaser.readLaserEntry();
    readingLaser2 = slaveLaser.readLaserExit();
    
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
        return entryExitType;
    }
}

int Logique::peopleCounter()
{
    peopleCount = 0;

    if(entryExitType == TypeSortie::Enter)
    {
        peopleCount = 1;
        return peopleCount;
    }
    else if(entryExitType == TypeSortie::Exit)
    {
        peopleCount = -1;
        return peopleCount;
    }
    else if(entryExitType == TypeSortie::InOut || entryExitType == TypeSortie::NoEntryExit)
    {
        peopleCount = 0;
        return peopleCount;
    }
}