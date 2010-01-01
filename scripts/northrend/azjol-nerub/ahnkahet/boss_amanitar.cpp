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
SDName: Boss_Amanitar
SD%Complete: 80%
SDComment: Timers 
SDAuthor: Tassadar
SDCategory: Ahn'kahet
EndScriptData */

#include "precompiled.h"
#include "ahnkahet.h"

enum
{
    //Amanitar spells
    SPELL_BASH               = 57094,
    SPELL_VENOM_BOLT         = 57088,
    SPELL_ENTANGLING_ROOTS   = 57095,
    SPELL_MINI               = 57055, // this one and SPELL_POTENT_FUNGUS MUST stack!

    //Mushroom spells
    SPELL_POISON_CLOUD       = 57061,
    SPELL_POISONOUS_MUSHROOM_VISUAL = 61566,
    SPELL_POTENT_FUNGUS      = 56648, // this one and SPELL_MINI MUST stack!
    SPELL_INVISIBILITY       = 49414, // I really dont wanna spawn all mushrooms by script, so make them invisible until fight begins
    SPELL_PUTRID_MUSHROOM    = 31690, // They should look like mushroom

    //Script thinks that all mushrooms which are spawned are only healthy, so change entry only for poisinous
    NPC_HEALTHY_MUSHROOM     = 30391,
    NPC_POISONOUS_MUSHROOM   = 30435,
};
/*######
## boss_amanitar
######*/

struct MANGOS_DLL_DECL boss_amanitarAI : public ScriptedAI
{
    boss_amanitarAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiBashTimer;
    uint32 m_uiVenomBoltTimer;
    uint32 m_uiRootsTimer;
    uint32 m_uiMiniTimer;


    void Reset()
    {
        m_uiBashTimer = 8000;
        m_uiVenomBoltTimer = 12000;
        m_uiRootsTimer = 19000;
        m_uiMiniTimer = 30000;

        if (m_pInstance)
            m_pInstance->SetData(TYPE_AMANITAR, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_AMANITAR, IN_PROGRESS);
    }
    void EnterEvadeMode()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_AMANITAR, FAIL);
    }
    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_AMANITAR, DONE);
    }
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
        
        //Bash
        if(m_uiBashTimer <= uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_BASH);
            m_uiBashTimer = 8000 + rand()%5000;
        }else m_uiBashTimer -= uiDiff;

        //Venom bolt volley
        if(m_uiVenomBoltTimer <= uiDiff)
        {
            DoCast(SelectUnit(SELECT_TARGET_RANDOM,0), SPELL_VENOM_BOLT);
            m_uiVenomBoltTimer = 15000 + rand()%5000;
        }else m_uiVenomBoltTimer -= uiDiff;

        //Entangling Roots
        if(m_uiRootsTimer <= uiDiff)
        {
            DoCast(SelectUnit(SELECT_TARGET_RANDOM,0), SPELL_ENTANGLING_ROOTS);
            m_uiRootsTimer = 18000 + rand()%5000;
        }else m_uiRootsTimer -= uiDiff;

        //Mini
        if(m_uiMiniTimer <= uiDiff)
        {
            DoCast(SelectUnit(SELECT_TARGET_RANDOM,0), SPELL_MINI);
            m_uiMiniTimer = 30000;
        }else m_uiMiniTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_amanitar(Creature* pCreature)
{
    return new boss_amanitarAI(pCreature);
}
/*######
## npc_amanitar_mushroom
######*/

struct MANGOS_DLL_DECL npc_amanitar_mushroomAI : public ScriptedAI
{
    npc_amanitar_mushroomAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint8 m_uiMushroomType; //0 = healthy, 1 = poisinous
    bool m_bHasFightBegun;
    uint32 m_uiCheckTimer;

    void Reset()
    {
        m_bHasFightBegun = false;
        m_uiMushroomType = rand()%1;

        m_uiCheckTimer = 1000;

        DoCast(m_creature,SPELL_PUTRID_MUSHROOM,true);

        if(m_pInstance->GetData(TYPE_AMANITAR) != IN_PROGRESS)
            m_creature->CastSpell(m_creature, SPELL_INVISIBILITY, false);
        
        if(m_uiMushroomType == 1)
        {
            m_creature->UpdateEntry(NPC_POISONOUS_MUSHROOM);
            m_creature->CastSpell(m_creature, SPELL_POISONOUS_MUSHROOM_VISUAL, false);
        }
    }
    void AttackStart(Unit *pWho)
    {
        return;
    }
    void JustDied(Unit* pKiller)
    {
        if(m_uiMushroomType == 0)
            m_creature->CastSpell(m_creature, SPELL_POTENT_FUNGUS, true);
        else
            m_creature->CastSpell(m_creature, SPELL_POISON_CLOUD, true);
    }
    void UpdateAI(const uint32 uiDiff)
    {
        if(m_uiCheckTimer <= uiDiff)
        {
            if(m_bHasFightBegun)
            {
                if(m_pInstance->GetData(TYPE_AMANITAR) != IN_PROGRESS)
                {
                    m_bHasFightBegun = false;
                    m_creature->CastSpell(m_creature, SPELL_INVISIBILITY, false);
                    m_creature->CombatStop();
                }
                m_uiCheckTimer = 15000;
            }else{
                if(m_pInstance->GetData(TYPE_AMANITAR) == IN_PROGRESS)
                {
                    m_bHasFightBegun = true;
                    m_creature->RemoveAurasDueToSpell(SPELL_INVISIBILITY);
                }
                m_uiCheckTimer = 5000;
            }
        }else m_uiCheckTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_amanitar_mushroom(Creature* pCreature)
{
    return new npc_amanitar_mushroomAI(pCreature);
}
void AddSC_boss_amanitar()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "boss_amanitar";
    newscript->GetAI = &GetAI_boss_amanitar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_amanitar_mushroom";
    newscript->GetAI = &GetAI_npc_amanitar_mushroom;
    newscript->RegisterSelf();
}