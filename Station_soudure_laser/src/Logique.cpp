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
    else
    {
        entryExitType = TypeSortie::NoEntryExit;
        return entryExitType;
    }
}

int Logique::peopleCounter()
{
    TypeSortie type = entryExitDef();
    
    switch(type)
    {
        case TypeSortie::Enter:
            return 1;
        case TypeSortie::Exit:
            return -1;
        case TypeSortie::InOut:
            return 0;
        case TypeSortie::NoEntryExit:
            return 0;
    }
}