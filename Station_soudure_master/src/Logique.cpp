#include "Logique.hpp"

Logique::Logique(struct_message payload) : dataPayload(payload) {}

TypeSortie Logique::entryExitDef()
{
    readingLaser1 = dataPayload.entryLaserData;
    readingLaser2 = dataPayload.exitLaserData;
    
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
            peopleCount = 1;
            break;
        case TypeSortie::Exit:
            peopleCount = -1;
            break;
        case TypeSortie::InOut:
            peopleCount = 0;
            break;
        case TypeSortie::NoEntryExit:
            peopleCount = 0;
            break;
    }
    return peopleCount;
}
