#include "Logique.hpp"

Logique::Logique(CreateSlave& slave) : slaveLaser(slave) {}

TypeSortie Logique::entryExitDef()
{
    readingLaser1 = slaveLaser.readLaserEntry();
    readingLaser2 = slaveLaser.readLaserExit();
    unsigned long int timestamp = millis();
    
    if(readingLaser1 == LOW && readingLaser2 == HIGH && timestamp < 500)
    {
        entryExitType = TypeSortie::Enter;
        return entryExitType;
    }
    else if(readingLaser1 == HIGH && readingLaser2 == LOW && timestamp < 500)
    {
        entryExitType = TypeSortie::Exit;
        return entryExitType;
    }
    else if(readingLaser1 == LOW && readingLaser2 == LOW)
    {
        entryExitType = TypeSortie::InOut;
        return entryExitType;
    }
    else if(readingLaser1 == HIGH && readingLaser2 == HIGH)
    {
        entryExitType = TypeSortie::NoEntryExit;
        return entryExitType;
    }
}

int32_t Logique::peopleCounter()
{
    TypeSortie type = entryExitDef();
    peopleCount = 0;

    if(type == TypeSortie::Enter)
    {
        peopleCount = 1;
        return peopleCount;
    }
    else if(type == TypeSortie::Exit)
    {
        peopleCount = -1;
        return peopleCount;
    }
    else if(type == TypeSortie::InOut || type == TypeSortie::NoEntryExit)
    {
        peopleCount = 0;
        return peopleCount;
    }
}