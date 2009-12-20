/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Boss_Jedoga
SD%Complete: 20%
SDComment:
SDCategory: Ahn'kahet
EndScriptData */

#include "precompiled.h"

struct Locations
{
    float x, y, z, o;
    uint32 id;
};
enum
{
    SPELL_SPHERE_VISUAL                 = 56075,
    SPELL_GIFT_OF_THE_HERALD            = 56219,
    SPELL_CYCLONE_STRIKE                = 60030,
    SPELL_CYCLONE_STRIKE_H              = 56855,
    SPELL_LIGHTNING_BOLT                = 56891,
    SPELL_LIGHTNING_BOLT_H              = 60032,
    SPELL_THUNDERSHOCK                  = 56926,
    SPELL_THUNDERSHOCK_H                = 60029,

    SAY_AGGRO                           = -1619017,
    SAY_CALL_SACRIFICE_1                = -1619018,
    SAY_CALL_SACRIFICE_2                = -1619019,
    SAY_SACRIFICE_1                     = -1619020,
    SAY_SACRIFICE_2                     = -1619021,
    SAY_SLAY_1                          = -1619022,
    SAY_SLAY_2                          = -1619023,
    SAY_SLAY_3                          = -1619024,
    SAY_DEATH                           = -1619025,
    SAY_PREACHING_1                     = -1619026,
    SAY_PREACHING_2                     = -1619027,
    SAY_PREACHING_3                     = -1619028,
    SAY_PREACHING_4                     = -1619029,
    SAY_PREACHING_5                     = -1619030,

    SAY_VOLUNTEER_1                     = -1619031,         //said by the volunteer image
    SAY_VOLUNTEER_2                     = -1619032,

    NPC_TWILIGHT_INITIATE               = 30114,
    NPC_TWILIGHT_VOLUNTEER              = 30385,

    //Jedoga Shadowseeker's phases
    PHASE_NOSTART                       = 0,
    PHASE_PREACHING                     = 1,
    PHASE_DESCEND                       = 2,
        SUBPHASE_FLY_DESCEND            = 21,
    PHASE_FIGHT                         = 3,
    PHASE_SACRIFACE                     = 4,
        SUBPHASE_FLY_UP                 = 41,
        SUBPHASE_CALL_VOLUNTEER         = 42,
        SUBPHASE_WAIT_FOR_VOLUNTEER     = 43,
        SUBPHASE_SACRIFACE              = 44,

    //Twilight Volunteer's sacriface phases
    SACRIFACE_CHOOSEN                   = 1,
    SACRIFACE_DIE                       = 2,

    VOLUNTEER_COUNT                     = 29,
};
#define CENTER_X                        342.330
#define CENTER_Y                        -705.287
#define AIR_Z                           -0.624
#define GROUND_Z                        -16.17
static Locations VolunteerLoc[]=
{
    //29 Volunteers
    {365.68, -735.95, -16.17, 1.607}, // Right, first line
    {367.12, -736.13, -16.17, 1.607},
    {369.03, -736.06, -16.17, 1.607},
    {371.66, -735.97, -16.17, 1.607},
    {373.47, -735.63, -16.17, 1.607},
    
    {365.45, -739.03, -16.00, 1.607}, // Right, second line
    {367.56, -738.62, -16.00, 1.607},
    {369.62, -738.22, -16.17, 1.607},
    {371.66, -737.82, -16.06, 1.607},
    {373.75, -737.41, -16.00, 1.607},
    
    {400.99, -705.41, -16.00, 2.491}, // Center, from right
    {398.07, -710.02, -16.00, 2.491},
    {395.34, -713.76, -16.00, 2.491},
    {393.42, -716.39, -16.00, 2.491},
    {391.48, -718.94, -16.00, 2.491},
    {388.80, -722.46, -16.00, 2.491},
    {386.19, -725.89, -16.00, 2.491},
    {383.61, -729.29, -16.00, 2.491},
    {380.37, -733.55, -16.00, 2.491},
    
    {402.72, -700.79, -16.00, 3.046}, // Left, first line
    {402.63, -698.86, -16.18, 3.149},
    {402.62, -697.10, -16.17, 3.149},
    {402.61, -695.50, -16.17, 3.059},
    {402.20, -693.39, -16.17, 3.159},

    {405.31, -701.29, -16.00, 2.924}, // Left, second line
    {405.46, -699.25, -16.00, 3.198},
    {405.40, -697.19, -16.00, 3.150},
    {405.35, -695.30, -16.00, 3.150},
    {405.29, -693.26, -16.00, 3.150}
};

/*######
## npc_twilight_volunteer
######*/
struct MANGOS_DLL_DECL npc_twilight_volunteerAI : public ScriptedAI
{
    npc_twilight_volunteerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint8 m_uiPhase;
    bool m_bIsVulunteerNear;
    void Reset()
    {
        m_uiPhase = 0;
        m_bIsVulunteerNear = false;
    }
    void AttackStart(Unit* pWho)
    {
        return;
    }
    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if(uiType != POINT_MOTION_TYPE)
                return;

        switch(uiPointId)
        {
            case 0:
                m_bIsVulunteerNear = true;
                break;
        }
    }
    void Sacriface(uint8 phase)
    {
        phase = m_uiPhase;
        switch(m_uiPhase)
        {
            case SACRIFACE_CHOOSEN:
                switch(urand(0, 1))
                {
                    case 0: DoScriptText(SAY_VOLUNTEER_1, m_creature); break;
                    case 1: DoScriptText(SAY_VOLUNTEER_2, m_creature); break;
                }
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_creature->GetMotionMaster()->MovePoint(0, CENTER_X, CENTER_Y, GROUND_Z);
                break;
            case SACRIFACE_DIE:
                m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                break;
        }
    }
    void UpdateAI(const uint32 uiDiff)
    {}
};

/*######
## boss_jedoga
######*/

struct MANGOS_DLL_DECL boss_jedogaAI : public ScriptedAI
{
    boss_jedogaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bIsVulunteerNear;
    bool m_bVolunteerDied;
    uint8 m_uiPhase;
    uint8 m_uiSubPhase;
    uint8 m_uiPreachingText;
    Creature *pVolunteer;
    uint8 m_uiLastSacrifaceHP;

    uint32 m_uiPreachingTimer;
    uint32 m_uiCheckTimer;
    uint32 m_uiSacrifaceTimer;
    uint32 m_uiCycloneStrikeTimer;
    uint32 m_uiLightningBoltTimer;
    uint32 m_uiThundershockTimer;


    void Reset()
    {
        m_uiPhase = 0;
        m_uiSubPhase = 0;
        m_uiPreachingText = 0;
        m_bIsVulunteerNear = false;
        m_bVolunteerDied = false;
        m_uiLastSacrifaceHP = 0;

        m_uiCheckTimer = 1000;
        m_uiSacrifaceTimer = 2000;
        m_uiPreachingTimer = 0;
        m_uiCycloneStrikeTimer = 15000;
        m_uiLightningBoltTimer = 3000;
        m_uiThundershockTimer = 20000;

        m_creature->AddMonsterMoveFlag(MONSTER_MOVE_LEVITATING);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    void Aggro(Unit* pWho)
    {
        if(m_uiPhase != PHASE_FIGHT)
        {
            m_creature->CombatStop(true);
            return;
        }
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_SLAY_1, m_creature); break;
            case 1: DoScriptText(SAY_SLAY_2, m_creature); break;
            case 2: DoScriptText(SAY_SLAY_3, m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
    }

    void MoveInLineOfSight(Unit* who)
    {
        if (!who)
            return;

        if (who->isTargetableForAttack() && who->GetTypeId() == TYPEID_PLAYER)
            m_uiPhase = PHASE_PREACHING;
    }
    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if(uiType != POINT_MOTION_TYPE)
                return;

        switch(uiPointId)
        {
            case 0:
                m_creature->RemoveMonsterMoveFlag(MONSTER_MOVE_SPLINE_FLY);
                m_creature->AddMonsterMoveFlag(MONSTER_MOVE_LEVITATING);
                break;
            case 1:
                m_creature->RemoveMonsterMoveFlag(MONSTER_MOVE_SPLINE_FLY);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                m_uiPhase = PHASE_FIGHT;
                m_creature->RemoveAurasDueToSpell(SPELL_SPHERE_VISUAL);
                if(m_creature->getVictim())
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                break;
            case 2:
                m_uiSubPhase = SUBPHASE_CALL_VOLUNTEER;
                m_creature->RemoveMonsterMoveFlag(MONSTER_MOVE_SPLINE_FLY);
                m_creature->AddMonsterMoveFlag(MONSTER_MOVE_LEVITATING);
                m_uiSacrifaceTimer = 2000;
                switch(urand(0, 1))
                {
                    case 0: DoScriptText(SAY_CALL_SACRIFICE_1, m_creature); break;
                    case 1: DoScriptText(SAY_CALL_SACRIFICE_2, m_creature); break;
                }
                break;
        }
    }
    
    Creature* SelectRandomVolunteer(float fRange)
    {
        std::list<Creature* > lVolunteerList;
        GetCreatureListWithEntryInGrid(lVolunteerList, m_creature, NPC_TWILIGHT_VOLUNTEER, fRange);

        //This should not appear!
        if (lVolunteerList.empty()){
            EnterEvadeMode();
            debug_log("SD2: AhnKahet: No volunteer to sacriface!");
            return NULL;
        }
            

        std::list<Creature* >::iterator iter = lVolunteerList.begin();
        advance(iter, urand(0, lVolunteerList.size()-1));

        return *iter;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if(m_uiPhase == PHASE_NOSTART)
            return;
        else if(m_uiPhase == PHASE_PREACHING)
        {
            if(m_uiCheckTimer <= uiDiff)
            {
                if(Creature *pTemp = GetClosestCreatureWithEntry(m_creature, NPC_TWILIGHT_INITIATE, 150.0f))
                    m_uiCheckTimer = 2000;
                else
                {
                    m_uiPhase = PHASE_DESCEND;
                    m_uiSubPhase = SUBPHASE_FLY_DESCEND;
                    return;
                }
            }else m_uiCheckTimer -= uiDiff;

            if(m_uiPreachingTimer > uiDiff || m_uiPreachingTimer == 0)
            {
                m_uiPreachingTimer -= uiDiff;
                return;
            }

            switch(m_uiPreachingText)
            {
               case 0:
                   DoScriptText(SAY_PREACHING_1, m_creature);
                   m_uiPreachingText++;
                   m_uiPreachingTimer = 9500;
                   break;
               case 1:
                   DoScriptText(SAY_PREACHING_2, m_creature);
                   m_uiPreachingText++;
                   m_uiPreachingTimer = 6500;
                   break;
               case 2:
                   DoScriptText(SAY_PREACHING_3, m_creature);
                   m_uiPreachingText++;
                   m_uiPreachingTimer = 8500;
                   break;
               case 3:
                   DoScriptText(SAY_PREACHING_4, m_creature);
                   m_uiPreachingText++;
                   m_uiPreachingTimer = 7500;
                   break;
               case 4:
                   DoScriptText(SAY_PREACHING_5, m_creature);
                   m_uiPreachingText++;
                   m_uiPreachingTimer = 0;
                   break;
            }
            return;
        }
        else if(m_uiPhase == PHASE_DESCEND)
        {
            if(m_creature->GetMotionMaster()->empty() && m_uiSubPhase == SUBPHASE_FLY_DESCEND)
            {
                m_creature->RemoveMonsterMoveFlag(MONSTER_MOVE_LEVITATING);
                m_creature->GetMotionMaster()->MovePoint(1, m_creature->GetPositionX(),m_creature->GetPositionY(), GROUND_Z);
                m_creature->AddMonsterMoveFlag(MONSTER_MOVE_SPLINE_FLY);
                for(int i = 0; i <= VOLUNTEER_COUNT; i++)
                {
                    if(Creature *pTemp = m_creature->SummonCreature(NPC_TWILIGHT_VOLUNTEER, VolunteerLoc[i].x, VolunteerLoc[i].y, VolunteerLoc[i].z, VolunteerLoc[i].o, TEMPSUMMON_CORPSE_DESPAWN, 0))
                        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    
                }
                m_uiSubPhase = 0;
            }
            return;
        }
        else if(m_uiPhase == PHASE_FIGHT)
        {
            //Evade if no target in this phase
            if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            {
                m_uiPhase = PHASE_NOSTART;
                EnterEvadeMode();
                return;
            }
            //Health check
            if(m_uiCheckTimer <= uiDiff)
            {
                uint8 health = m_creature->GetHealth()*100 / m_creature->GetMaxHealth();                    
                if(m_uiLastSacrifaceHP == 0 && health <= 75)
                {
                    m_uiLastSacrifaceHP = 75;
                    m_uiPhase = PHASE_SACRIFACE;
                    return;
                }
                else if(m_uiLastSacrifaceHP == 75 && health <= 50)
                {
                    m_uiLastSacrifaceHP = 50;
                    m_uiPhase = PHASE_SACRIFACE;
                    return;
                }
                else if(m_uiLastSacrifaceHP == 50 && health <= 25)
                {
                    m_uiLastSacrifaceHP = 25;
                    m_uiPhase = PHASE_SACRIFACE;
                    return;
                }
                m_uiCheckTimer = 1000;
            }else m_uiCheckTimer -= uiDiff;

            //Spells
            //Cyclone Strike
            if(m_uiCycloneStrikeTimer <= uiDiff)
            {
                DoCast(m_creature, m_bIsRegularMode ? SPELL_CYCLONE_STRIKE : SPELL_CYCLONE_STRIKE_H);
                m_uiCycloneStrikeTimer = 10000 + rand()%10000;
            }else m_uiCycloneStrikeTimer -= uiDiff;

            //Lightning Bolt
            if(m_uiLightningBoltTimer <= uiDiff)
            {
                DoCast(m_creature, m_bIsRegularMode ? SPELL_LIGHTNING_BOLT : SPELL_LIGHTNING_BOLT_H);
                m_uiLightningBoltTimer = 3000 + rand()%2000;
            }else m_uiLightningBoltTimer -= uiDiff;

            //Thundershock
            if(m_uiThundershockTimer <= uiDiff)
            {
                if(Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                    DoCast(pTarget, m_bIsRegularMode ? SPELL_THUNDERSHOCK : SPELL_THUNDERSHOCK_H);
                m_uiThundershockTimer = 20000 + rand()%10000;
            }else m_uiThundershockTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }
        else if(m_uiPhase == PHASE_SACRIFACE)
        {
            if(m_uiSubPhase == SUBPHASE_FLY_UP)
            {
                SetCombatMovement(false);
                m_creature->GetMotionMaster()->MovementExpired();
                m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                 m_creature->InterruptNonMeleeSpells(true);
                DoCast(m_creature, SPELL_SPHERE_VISUAL);
                m_creature->GetMotionMaster()->MovePoint(0, CENTER_X, CENTER_Y, AIR_Z);
                m_creature->AddMonsterMoveFlag(MONSTER_MOVE_SPLINE_FLY);
                m_uiSubPhase = 0;
            }
            else if(m_uiSubPhase == SUBPHASE_CALL_VOLUNTEER)
            {
                if(m_uiSacrifaceTimer >= uiDiff)
                {
                    m_uiSacrifaceTimer -= uiDiff;
                    return;
                }
                pVolunteer = SelectRandomVolunteer(150.0f);
                if(pVolunteer)
                {
                    ((npc_twilight_volunteerAI*)pVolunteer->AI())->Sacriface(SACRIFACE_CHOOSEN);
                    m_uiSubPhase = 0;
                }
            }
            else if(m_uiSubPhase == SUBPHASE_WAIT_FOR_VOLUNTEER)
            {
                if(m_uiCheckTimer <= uiDiff)
                {
                    if(pVolunteer){
                        m_bVolunteerDied = false;
                        if(((npc_twilight_volunteerAI*)pVolunteer->AI())->m_bIsVulunteerNear)
                            m_uiSubPhase = SUBPHASE_SACRIFACE;
                    }else{
                        m_bIsVulunteerNear = true;
                        m_uiSubPhase = SUBPHASE_SACRIFACE;
                    }
                    
                    m_uiCheckTimer = 1000;
                }else m_uiCheckTimer -= uiDiff;
            }
            else if(m_uiSubPhase == SUBPHASE_SACRIFACE)
            {
                switch(urand(0, 1))
                {
                    case 0: DoScriptText(SAY_SACRIFICE_1, m_creature); break;
                    case 1: DoScriptText(SAY_SACRIFICE_2, m_creature); break;
                }
                
                if(pVolunteer)
                    ((npc_twilight_volunteerAI*)pVolunteer->AI())->Sacriface(SACRIFACE_DIE);
                
                if(!m_bVolunteerDied)
                    DoCast(m_creature, SPELL_GIFT_OF_THE_HERALD);
                m_creature->RemoveMonsterMoveFlag(MONSTER_MOVE_LEVITATING);
                m_creature->GetMotionMaster()->MovePoint(1, CENTER_X, CENTER_Y, GROUND_Z);
                m_creature->AddMonsterMoveFlag(MONSTER_MOVE_SPLINE_FLY);
            }
        }
    }
};
CreatureAI* GetAI_boss_jedoga(Creature* pCreature)
{
    return new boss_jedogaAI(pCreature);
}

CreatureAI* GetAI_npc_twilight_volunteer(Creature* pCreature)
{
    return new npc_twilight_volunteerAI(pCreature);
}

void AddSC_boss_jedoga()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_jedoga";
    newscript->GetAI = &GetAI_boss_jedoga;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_twilight_volunteer";
    newscript->GetAI = &GetAI_npc_twilight_volunteer;
    newscript->RegisterSelf();
}
/*
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `emote`, `moveflags`, `auras`) VALUES ('30385', '0', '8', '1', '0', '0', NULL);
UPDATE creature_template SET ScriptName="npc_twilight_volunteer" WHERE entry=30385;
*/