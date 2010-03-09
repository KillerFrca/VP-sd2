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
SDName: Freya
SD%Complete: 0
SDComment: PH.
SDCategory: Ulduar
EndScriptData */

#include "precompiled.h"
#include "ulduar.h"

/*
#define SAY_AGGRO -1
#define SAY_SLAY -1


*/
enum
{
    //general abilities
    SPELL_SUNBEAM                       = 62623,
    H_SPELL_SUNBEAM                     = 62872,
    SPELL_ATTUNED_TO_NATURE             = 62519,
    SPELL_TOUCH_OF_EONAR                = 62528,
    H_SPELL_TOUCH_OF_EONAR              = 62892,
    SPELL_NATURE_BOMB                   = 64587,
    H_SPELL_NATURE_BOMB                 = 64650,

    SPELL_LIFEBINDERS_GIFT_SUMMON       = 62869,
    SPELL_SUMMON_ALLIES_OF_NATURE       = 62678,
    SPELL_NATURE_BOMB_SUMMON            = 64606,

    //abilities with Elder Brightleaf
    SPELL_UNSTABLE_ENERGY               = 62451,
    H_SPELL_UNSTABLE_ENERGY             = 62865,
    SPELL_BRIGHTLEAFS_ESSENCE           = 62385,

    //abilities with Elder Ironbranch
    SPELL_IRON_ROOTS                    = 62283,
    H_SPELL_IRON_ROOTS                  = 62930,
    SPELL_IRONBRANCHS_ESSENCE           = 62387,
    
    SPELL_STRENGTHENED_IRON_ROOTS_SUMM  = 63601,
    
    NPC_STRENGTHENED_IRON_ROOTS         = 33168,

    //abilities with Elder Stonebark 
    SPELL_GROUND_TREMOR                 = 62437,
    H_SPELL_GROUND_TREMOR               = 62859,
    SPELL_STONEBARKS_ESSENCE            = 62386,

    NPC_NATURE_BOMB                     = 34129,

    NPC_ELDER_BRIGHTLEAF                = 32915,
    NPC_ELDER_IRONBRANCH                = 32913,
    NPC_ELDER_STONEBARK                 = 32914,
};

struct MANGOS_DLL_DECL boss_freyaAI : public ScriptedAI
{
    boss_freyaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
    }

    void KilledUnit(Unit *victim)
    {
    }

    void JustDied(Unit *victim)
    {
    }

    bool IsCreatureAlive(Creature *pCreature)
    {
        if(GetClosestCreatureWithEntry(m_creature, pCreature, 150.0f)
            return true;
        
        return false;
    }

    void Aggro(Unit* pWho)
    {
//        DoScriptText(SAY_AGGRO, m_creature);
        m_creature->SetInCombatWithZone();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_FREYA, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
//SPELLS TODO:

//
        DoMeleeAttackIfReady();

        EnterEvadeIfOutOfCombatArea(diff);

    }

};

CreatureAI* GetAI_boss_freya(Creature* pCreature)
{
    return new boss_freyaAI(pCreature);
}

void AddSC_boss_freya()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_freya";
    newscript->GetAI = &GetAI_boss_freya;
    newscript->RegisterSelf();

}

