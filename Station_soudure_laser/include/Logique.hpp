#ifndef DEF_LOGIQUE
#define DEF_LOGIQUE

#include "CreateSlave.hpp"

enum class TypeSortie
{
    Enter, Exit, InOut, NoEntryExit
};

class Logique
{
    public:

        Logique(CreateSlave slave);

        TypeSortie entryExitDef(int entryData, int exitData);
        int peopleCounter(TypeSortie type);

    private:

        CreateSlave& slaveLaser;

        bool readingLaser1;
        bool readingLaser2;
        int peopleCount;
        TypeSortie entryExitType;
        
};
#endif