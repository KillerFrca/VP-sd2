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
SDName: mob_dragons
SDAuthor: ckegg, Tassadar
SD%Complete: 0
SDComment: 
SDCategory: The Violet Hold
EndScriptData */

#include "precompiled.h"
#include "def_violet_hold.h"

struct Locations
{
    float x, y, z;
    uint32 id;
};

static Locations BossLoc[]=
{
    {1857.125, 763.295, 38.654}, // Lavanthor
    {1925.480, 849.981, 47.174}, // Zuramat
    {1892.737, 744.589, 47.666}, // Moragg
    {1876.100, 857.079, 43.333}, // Erekem
    {1908.863, 785.647, 37.435}, // Ichoron
    {1905.364, 840.607, 38.670}, // Xevozz
};
enum
{
    SPELL_SHIELD_DISRUPTION               = 58291,

    //DRAGONS SPELLS
    //Azure Captain
    SPELL_MORTAL_STRIKE                   = 32736,
    SPELL_WHIRLWIND                        = 41057,
};

/*######
## npc_azure_saboteur
######*/
struct MANGOS_DLL_DECL npc_azure_saboteurAI : public ScriptedAI
{
    npc_azure_saboteurAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        Reset();
    }
    ScriptedInstance *m_pInstance;

    bool m_bIsActiving;

    uint32 m_uiDisruption_Timer;
    uint32 m_uiDisruptionCounter;

    uint8 m_uiBossID;
    uint32 m_uiBossType;
    uint64 m_uiBossGUID;
    uint64 m_uiDoorGUID;

    void AttackStart(Unit* pWho)
    {
        return;
    }

    void Reset()
    {
        m_bIsActiving = false;

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->RemoveMonsterMoveFlag(MONSTER_MOVE_WALK);
        m_uiDisruptionCounter = 0;
        m_uiDisruption_Timer = 1000;

        if (m_pInstance)
        {
            m_uiBossID = m_pInstance->GetData(TYPE_LASTBOSS);

            switch (m_uiBossID)
            {
                case 0: // Lavanthor
                    m_uiBossType = TYPE_LAVANTHOR;
                    m_uiBossGUID = m_pInstance->GetData64(DATA_LAVANTHOR);
                    m_uiDoorGUID = m_pInstance->GetData64(DATA_LAVANTHOR_DOOR);
                    break;
                case 1: // Zuramat
                    m_uiBossType = TYPE_ZURAMAT;
                    m_uiBossGUID = m_pInstance->GetData64(DATA_ZURAMAT);
                    m_uiDoorGUID = m_pInstance->GetData64(DATA_ZURAMAT_DOOR);
                    break;
                case 2: // Moragg
                    m_uiBossType = TYPE_MORAGG;
                    m_uiBossGUID = m_pInstance->GetData64(DATA_MORAGG);
                    m_uiDoorGUID = m_pInstance->GetData64(DATA_MORAGG_DOOR);
                    break;
                case 3: // Erekem
                    m_uiBossType = TYPE_EREKEM;
                    m_uiBossGUID = m_pInstance->GetData64(DATA_EREKEM);
                    m_uiDoorGUID = m_pInstance->GetData64(DATA_EREKEM_DOOR);
                    break;
                case 4: // Ichoron
                    m_uiBossType = TYPE_ICHORON;
                    m_uiBossGUID = m_pInstance->GetData64(DATA_ICHORON);
                    m_uiDoorGUID = m_pInstance->GetData64(DATA_ICHORON_DOOR);
                    break;
                case 5: // Xevozz
                    m_uiBossType = TYPE_XEVOZZ;
                    m_uiBossGUID = m_pInstance->GetData64(DATA_XEVOZZ);
                    m_uiDoorGUID = m_pInstance->GetData64(DATA_XEVOZZ_DOOR);
                    break;
            }
            m_creature->GetMotionMaster()->MovePoint(0, BossLoc[m_uiBossID].x,  BossLoc[m_uiBossID].y,  BossLoc[m_uiBossID].z);
        }
    }

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if(uiType != POINT_MOTION_TYPE)
                return;

        switch(uiPointId)
        {
            case 0:
                m_bIsActiving = true;
                break;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bIsActiving)
            if (m_uiDisruption_Timer < uiDiff)
            {
                if (m_uiDisruptionCounter < 3)
                    DoCast(m_creature, SPELL_SHIELD_DISRUPTION);
                else if (m_uiDisruptionCounter == 3)
                {
                    m_pInstance->DoUseDoorOrButton(m_uiDoorGUID);
                    m_pInstance->SetData(m_uiBossType, SPECIAL);
                }
                else
                    m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);

                ++m_uiDisruptionCounter;
                m_uiDisruption_Timer = 1000;
            }
            else m_uiDisruption_Timer -= uiDiff;
    }
};

/*######
## mob_vh_dragons
## This script is for ALL mobs which are spawned from portals,
## they have to be scripted in SD2 because in EventAI you cant
## check for distance from door seal :/
## (Intro not implented yet)
######*/
struct MANGOS_DLL_DECL mob_vh_dragonsAI : public ScriptedAI
{
    mob_vh_dragonsAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    uint32 creatureEntry;

    //Azure Captain
    uint32 m_uiMortalStrike_Timer;
    uint32 m_uiWhirlwind_Timer;

    void Reset(){
        creatureEntry = m_creature->GetEntry();

        //Azure Captain
        m_uiMortalStrike_Timer = 3000;
        m_uiWhirlwind_Timer = 5000;
    }

    void UpdateAI(const uint32 uiDiff){
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            if(Unit* pDoorSeal	= Unit::GetUnit((*m_creature), m_pInstance->GetData64(DATA_NPC_SEAL_DOOR)))
            {
                m_creature->AddThreat(pDoorSeal);
                m_creature->AI()->AttackStart(pDoorSeal);
            }else return;
        }

        //Corrupt seal door
        if(m_creature->getVictim()->GetEntry() == NPC_DOOR_SEAL && creatureEntry != NPC_GUARDIAN && creatureEntry != NPC_KEEPER)
        {
            if(m_creature->IsWithinDist(m_creature->getVictim(), 20.0f, false) && !m_creature->IsNonMeleeSpellCasted(false))
            {
                m_creature->StopMoving();
                DoCast(m_creature->getVictim(), SPELL_CORRUPT);
            }
            return;
        }
        switch(creatureEntry)
        {
            case NPC_AZURE_CAPTAIN:
                AzureCaptain_UpdateAI(uiDiff);
                break;
            case NPC_AZURE_RAIDER:
            case NPC_AZURE_SORCEROR:
            case NPC_AZURE_STALKER:
            case NPC_GUARDIAN:
            case NPC_KEEPER:
            case NPC_AZURE_BINDER:
            case NPC_AZURE_INVADER:
            case NPC_AZURE_MAGE_SLAYER:
            case NPC_AZURE_SPELLBREAKER:
                break;
            default:
                debug_log("SD2: The Violet Hold: Unhandled dragon entry %u!", m_creature->GetEntry());
                break;
        }
        DoMeleeAttackIfReady();
    }
    //Azure Captain
    void AzureCaptain_UpdateAI(const uint32 uiDiff)
    {
        //Mortal Strike
        if (m_uiMortalStrike_Timer <= uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_MORTAL_STRIKE);
            m_uiMortalStrike_Timer = 6000;
        }else m_uiMortalStrike_Timer -= uiDiff;

        //Whirlwind
        if (m_uiWhirlwind_Timer <= uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_WHIRLWIND);
            m_uiWhirlwind_Timer = 15000;
        }else m_uiWhirlwind_Timer -= uiDiff;
    }

};

CreatureAI* GetAI_npc_azure_saboteur(Creature* pCreature)
{
    return new npc_azure_saboteurAI (pCreature);
}
CreatureAI* GetAI_mob_vh_dragons(Creature* pCreature)
{
    return new mob_vh_dragonsAI(pCreature);
}
void AddSC_mob_vh_dragons()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_azure_saboteur";
    newscript->GetAI = &GetAI_npc_azure_saboteur;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_vh_dragons";
    newscript->GetAI = &GetAI_mob_vh_dragons;
    newscript->RegisterSelf();
}