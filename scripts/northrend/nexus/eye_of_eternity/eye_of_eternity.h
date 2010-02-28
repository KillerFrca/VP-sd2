#ifndef DEF_EYE_OF_ETERNITY_H
#define DEF_EYE_OF_ETERNITY_H

enum
{
    MAX_ENCOUNTER                = 1,

    TYPE_MALYGOS                 = 2,
    TYPE_INSTANCE_ENTER_RULES    = 3,
    
    //Data for instance control
    DATA_ALLOW_ENTER             = 4,  // Normal enter to instance
    DATA_ALLOW_ENTER_VEHICLE     = 5,  // Mount to vehicle after instance enter
    DATA_DISABLE_ENTER           = 6,  // Players will be ported back when they enter instance

    NPC_WYRMREST_SKYTALON        = 30161, // Dragon Vehicle in Third Phase
};
#endif