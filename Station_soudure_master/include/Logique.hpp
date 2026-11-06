#ifndef DEF_LOGIQUE
#define DEF_LOGIQUE

#include "CreateMaster.hpp"
#include "msgPayload.hpp"

enum class TypeSortie
{
    Enter, Exit, InOut, NoEntryExit
};

class Logique
{
    public:

        Logique(struct_message payload);

        int peopleCounter();
        
        private:
        
        struct_message dataPayload;
        
        bool readingLaser1;
        bool readingLaser2;
        int peopleCount;
        TypeSortie entryExitType;
        
        TypeSortie entryExitDef();
};
#endif