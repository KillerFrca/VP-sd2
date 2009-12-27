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
SDName: Boss_Volazj
SD%Complete: 20%
SDComment:
SDCategory: Ahn'kahet
EndScriptData */

#include "precompiled.h"

//TODO: fill in texts in database. Also need to add text for whisper.
enum
{
    SPELL_MIND_FLAY                 = 57941,
    SPELL_MIND_FLAY_H               = 59974,
    SPELL_SHADOW_BOLT               = 57942,
    SPELL_SHADOW_BOLT_H             = 59975,

    //Shiver - horrible ability
    SPELL_SHIVER                    = 57949, //Jump Aura
    SPELL_SHIVER_H                  = 59978,
    SPELL_SHIVER_DMG                = 57952, //Damage
    SPELL_SHIVER_DMG_H              = 59979,
    SPELL_SHIVER_DUMMY              = 57951, //What is this? 

    //This is little complicated:
    //When volajz cast this, on every player is cast different invisibility spell,
    //so they dont see together, but they see four Twisted Visages - images of other
    //four party members, which cast spell like their class.
    SPELL_INSANITY                  = 57496, //This is what volajz casts, it should spawn all Twisted Visage in all phases(see below)
    SPELL_INSANITY_PHASE_1          = 57508, //invis spells
    SPELL_INSANITY_PHASE_2          = 57509,
    SPELL_INSANITY_PHASE_3          = 57510,
    SPELL_INSANITY_PHASE_4          = 57511,
    SPELL_INSANITY_PHASE_5          = 57512,

    SPELL_TWISTED_VISAGE_MIRROR     = 57507, //Not implented in mangos, but I have patch :)

    /*
    http://www.wowhead.com/?spell=57507 Twisted visage visual
    http://www.wowhead.com/?spells=0&filter=na=twisted+visage so many spells?!
    */

    NPC_TWISTED_VISAGE              = 30625,
    

    SAY_AGGRO                       = -1619033,
    SAY_INSANITY                    = -1619034,
    SAY_SLAY_1                      = -1619035,
    SAY_SLAY_2                      = -1619036,
    SAY_SLAY_3                      = -1619037,
    SAY_DEATH_1                     = -1619038,
    SAY_DEATH_2                     = -1619039,

    PHASE_NOSTART                   = 0,
    PHASE_FIGHT                     = 1,
    PHASE_INSANITY                  = 2,
};

/*######
## boss_volazj
######*/

struct MANGOS_DLL_DECL boss_volazjAI : public ScriptedAI
{
    boss_volazjAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiMindFlayTimer;
    uint32 m_uiShadowBoltTimer;
    uint32 m_uiShiverTimer;
    void Reset()
    {
    }

    void Aggro(Unit* pWho)
    {
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
        DoScriptText(urand(0, 1) ? SAY_DEATH_1 : SAY_DEATH_2, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_volazj(Creature* pCreature)
{
    return new boss_volazjAI(pCreature);
}

void AddSC_boss_volazj()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_volazj";
    newscript->GetAI = &GetAI_boss_volazj;
    newscript->RegisterSelf();
}
