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

enum
{
    //freya
    //general abilities
    SPELL_SUNBEAM                       = 62623,
    H_SPELL_SUNBEAM                     = 62872,
    SPELL_ATTUNED_TO_NATURE             = 62519,
    SPELL_TOUCH_OF_EONAR                = 62528,
    H_SPELL_TOUCH_OF_EONAR              = 62892,
    SPELL_LIFEBINDER_GIFT               = 62584,
    H_SPELL_LIFEBINDER_GIFT             = 62619,
    SPELL_NATURE_BOMB                   = 64587,
    H_SPELL_NATURE_BOMB                 = 64650,
    SPELL_BERSERK                       = 47008,

    SPELL_PHEROMONES_LG                 = 62619,

    //SPELL_SUMMON_ALLIES_OF_NATURE     = 62678, //better do that in sd2
    SPELL_SUMMON_WAVE_10                = 62688,
    SPELL_SUMMON_WAVE_3                 = 62686,
    SPELL_SUMMON_WAVE_1                 = 62685,
    SPELL_LIFEBINDERS_GIFT_SUMMON       = 62869,
    SPELL_NATURE_BOMB_SUMMON            = 64606,
    SPELL_HEALTHY_SPORES_SUMMON         = 62593,

    //abilities with Elder Brightleaf
    SPELL_UNSTABLE_ENERGY_FREYA         = 62451,
    H_SPELL_UNSTABLE_ENERGY_FREYA       = 62865,
    SPELL_BRIGHTLEAFS_ESSENCE           = 62385, // insert into spell_script_target values (62385, 1, 32906);

    //abilities with Elder Ironbranch
    SPELL_IRON_ROOTS_FREYA              = 62283,
    H_SPELL_IRON_ROOTS_FREYA            = 62930,
    SPELL_IRONBRANCHS_ESSENCE           = 62387, // insert into spell_script_target values (62387, 1, 32906);
    
    SPELL_STRENGTHENED_IRON_ROOTS_SUMM  = 63601,
    
    NPC_STRENGTHENED_IRON_ROOTS         = 33168,

    //abilities with Elder Stonebark 
    SPELL_GROUND_TREMOR_FREYA           = 62437,
    H_SPELL_GROUND_TREMOR_FREYA         = 62859,
    SPELL_STONEBARKS_ESSENCE            = 62386, // insert into spell_script_target values (62386, 1, 32906);

    //elders
    SPELL_DRAINED_OF_POWER              = 62467,
    
    //Elder Brightleaf
    SPELL_BRIGHTLEAFS_FLUX              = 62262,
    SPELL_SOLAR_FLARE                   = 62240,
    H_SPELL_SOLAR_FLARE                 = 62920,
    SPELL_UNSTABLE_SOLAR_BEAM           = 62243,
    SPELL_UNSTABLE_ENERGY               = 62217,
    H_SPELL_UNSTABLE_ENERGY             = 62922,
    SPELL_PHOTOSYNTHESIS                = 62209,

    //Elder Ironbranch
    SPELL_IMPALE                        = 62310,
    H_SPELL_IMPALE                      = 62928,
    SPELL_IRON_ROOTS                    = 62438,
    H_SPELL_IRON_ROOTS                  = 62861,
    SPELL_THORN_SWARM                   = 62285,
    H_SPELL_THORN_SWARM                 = 62931,
    
    SPELL_IRON_ROOTS_SUMM               = 65160,

    NPC_IRON_ROOTS                      = 33008,
    
    //Elder Stonebark
    SPELL_FIST_OF_STONE                 = 62344,
    SPELL_BROKEN_BONES                  = 62356,
    SPELL_GROUND_TREMOR                 = 62325,
    H_SPELL_GROUND_TREMOR               = 62932,
    SPELL_PETRIFIED_BARK                = 62337,
    H_SPELL_PETRIFIED_BARK              = 62933,

    NPC_NATURE_BOMB                     = 34129,
    NPC_EONARS_GIFT                     = 33228,
    NPC_HEALTHY_SPORE                   = 33215,

    NPC_ELDER_BRIGHTLEAF                = 32915, 
    NPC_ELDER_IRONBRANCH                = 32913,
    NPC_ELDER_STONEBARK                 = 32914,

    NPC_WAVE_1                          = 33203,
    NPC_WAVE_3_WATER                    = 33202,
    NPC_WAVE_3_SNAPLASHER               = 32916,
    NPC_WAVE_3_STORM                    = 32919,
    NPC_WAVE_10                         = 32918,

};

//if (Creature* pFreya = (Creature*)Unit::GetUnit((*m_creature), m_pInstance->GetData64(DATA_FREYA)))
/*void ReduceStack(Creature* pCreature, ScriptedInstance* instance, uint8 count)
{
    if(Aura *pAura = Unit::GetUnit((*pCreature), instance->GetData64(DATA_FREYA))->GetAura(SPELL_ATTUNED_TO_NATURE, EFFECT_INDEX_0))
        pAura->SetStackAmount(pAura->GetStackAmount() - count);
}*/

Creature* GetFreya(Creature* pCreature, ScriptedInstance* instance){return (Creature*)Unit::GetUnit((*pCreature), instance->GetData64(DATA_FREYA));}

///////////////
//// Freya ////
///////////////
// update creature_template set ScriptName = 'boss_freya' WHERE entry = 32906;
struct MANGOS_DLL_DECL boss_freyaAI : public ScriptedAI
{
    boss_freyaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 Wave_Timer;
    uint32 LifebinderGift_Timer;
    uint32 Sunbeam_Timer;
    uint32 Wave_Count;
    uint32 spellId1;
    uint32 spellId2;
    uint32 spellId3;
    uint32 spellIdCast;
    uint32 yell;
    uint32 Berserk_Timer;
    bool HardMode;


    void Reset()
    {
        Wave_Timer = urand(9,12)*IN_MILISECONDS;
        LifebinderGift_Timer = urand(19,23)*IN_MILISECONDS;
        Sunbeam_Timer = urand(44,49)*IN_MILISECONDS;
        Wave_Count = 0;
        Berserk_Timer = 10*MINUTE*IN_MILISECONDS;
        HardMode = false;
    }

    void KilledUnit(Unit *victim)
    {
    }

    void JustDied(Unit *victim)
    {
        if(HardMode)
            ;//TODO: GO spawn
    }

    void Aggro(Unit* pWho)
    {
    //  DoScriptText(SAY_AGGRO, m_creature); //The Conservatory must be protected
        m_creature->SetInCombatWithZone();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_FREYA, IN_PROGRESS);
        
        BuffOnAggro();
    }
    void JustReachedHome()
    {
        DespawnAllCreaturesWithEntry(NPC_NATURE_BOMB);
        DespawnAllCreaturesWithEntry(NPC_IRON_ROOTS);
        DespawnAllCreaturesWithEntry(NPC_STRENGTHENED_IRON_ROOTS);
        DespawnAllCreaturesWithEntry(NPC_WAVE_1);
        DespawnAllCreaturesWithEntry(NPC_WAVE_3_WATER);
        DespawnAllCreaturesWithEntry(NPC_WAVE_3_SNAPLASHER);
        DespawnAllCreaturesWithEntry(NPC_WAVE_3_STORM);
        DespawnAllCreaturesWithEntry(NPC_WAVE_10);
        DespawnAllCreaturesWithEntry(NPC_EONARS_GIFT);
    }

    bool IsCreatureAlive(Creature *pCreature)
    {
        if(GetClosestCreatureWithEntry(m_creature, pCreature->GetEntry(), 150.0f))
            return true;
        
        return false;
    }

    void BuffOnAggro()
    {
        //buff on start
        m_creature->CastSpell(m_creature, SPELL_ATTUNED_TO_NATURE, true);
        if(Aura *pAura = m_creature->GetAura(SPELL_ATTUNED_TO_NATURE, EFFECT_INDEX_0))
            pAura->SetStackAmount(150);
        m_creature->CastSpell(m_creature, m_bIsRegularMode ? SPELL_TOUCH_OF_EONAR : H_SPELL_TOUCH_OF_EONAR, true);

        //chek hard mode and additional buffs
        bool BrightleafAlive;
        if(Creature* pBright = GetClosestCreatureWithEntry(m_creature, NPC_ELDER_BRIGHTLEAF, 180.0f))
        {
            m_creature->CastSpell(m_creature, SPELL_BRIGHTLEAFS_ESSENCE, true);
            pBright->CastSpell(pBright, SPELL_DRAINED_OF_POWER, true);
            BrightleafAlive = true;
        }else BrightleafAlive = false;

        bool IronbranchAlive;
        if(Creature* pIron = GetClosestCreatureWithEntry(m_creature, NPC_ELDER_IRONBRANCH, 180.0f))
        {
            m_creature->CastSpell(m_creature, SPELL_IRONBRANCHS_ESSENCE, true);
            pIron->CastSpell(pIron, SPELL_DRAINED_OF_POWER, true);
            IronbranchAlive = true;
        }else IronbranchAlive = false;

        bool StonebarkAlive;
        if(Creature* pStone = GetClosestCreatureWithEntry(m_creature, NPC_ELDER_STONEBARK, 180.0f))
        {
            m_creature->CastSpell(m_creature, SPELL_STONEBARKS_ESSENCE, true);
            pStone->CastSpell(pStone, SPELL_DRAINED_OF_POWER, true);
            StonebarkAlive = true;
        }else StonebarkAlive = false;

        if(BrightleafAlive && IronbranchAlive && StonebarkAlive)
            HardMode = true;

        m_creature->SetHealth(m_creature->GetMaxHealth());
    }

    void DespawnAllCreaturesWithEntry(uint32 entry)
    {
        std::list<Creature*> m_pCreatures;
        GetCreatureListWithEntryInGrid(m_pCreatures, m_creature, entry, 150.0f);
 
        if (m_pCreatures.empty())
            return;
 
        for(std::list<Creature*>::iterator iter = m_pCreatures.begin(); iter != m_pCreatures.end(); ++iter)
            (*iter)->ForcedDespawn();
    } 

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(Wave_Timer < diff && Wave_Count < 6)
        {
            //spell cast
            if (Wave_Count == 0 || Wave_Count == 3)
            {
                switch(urand(0,5))
                {
                    case 0: spellId1 = 62685; spellId2 = 62686; spellId3 = 62688; break;
                    case 1: spellId1 = 62685; spellId2 = 62688; spellId3 = 62686; break;
                    case 2: spellId1 = 62686; spellId2 = 62685; spellId3 = 62688; break;
                    case 3: spellId1 = 62686; spellId2 = 62688; spellId3 = 62685; break;
                    case 4: spellId1 = 62688; spellId2 = 62685; spellId3 = 62686; break;
                    case 5: spellId1 = 62688; spellId2 = 62686; spellId3 = 62685; break;
                }
            }
            error_log("spellId1 = %u, spellId2 = %u, spellId3 = %u", spellId1, spellId2, spellId3);
            if(Wave_Count == 0 || Wave_Count == 3)
                spellIdCast = spellId1;
            if(Wave_Count == 1 || Wave_Count == 4)
                spellIdCast = spellId2;
            if(Wave_Count == 2 || Wave_Count == 5)
                spellIdCast = spellId3;
            error_log("spellIdCast is %u", spellIdCast);
            m_creature->CastSpell(m_creature, spellIdCast, true);
            
            //yell
            // emote: Allies Of Nature appeared.
            // YELL_ADD_MUTIPLE The swarm of the elements shall overtake you. (malí hajzlíci) 62688
            // YELL_ADD_THREE Eonar, your servant request aid! (stromek) 62685
            // YELL_ADD_SINGLE Children, assist me! (3 cipové)62686
            if(spellIdCast = 62685)
            //	yell = YELL_ADD_SINGLE;
            if(spellIdCast = 62686)
            //	yell = YELL_ADD_THREE;
            if(spellIdCast = 62688)
            //	yell = YELL_ADD_MULTIPLE;
            //DoScriptText(yell, m_creature);

            //emote
            //DoScriptText(EMOTE_SPAWN_ADD, m_creature);

            Wave_Timer = MINUTE*IN_MILISECONDS;
            Wave_Count++;
        }else Wave_Timer -= diff;

        if (LifebinderGift_Timer < diff)
        {
            DoCast(SelectUnit(SELECT_TARGET_RANDOM,0), SPELL_LIFEBINDERS_GIFT_SUMMON);
            // emote: A Lifebinder's Gift begins to grow!
            LifebinderGift_Timer = urand(38, 42)*1000;
        }else LifebinderGift_Timer -= diff;

        if(Sunbeam_Timer < diff)
        {
            DoCast(SelectUnit(SELECT_TARGET_RANDOM,0), m_bIsRegularMode ? SPELL_SUNBEAM : H_SPELL_SUNBEAM);
            Sunbeam_Timer = urand(15,20)*IN_MILISECONDS;		
        }else Sunbeam_Timer -= diff;
        

        if(Wave_Count == 6 /*samethink like phase2 check*/)
        {
        }

        if(Berserk_Timer < diff)
        {
            DoCast(SelectUnit(SELECT_TARGET_RANDOM,0), m_bIsRegularMode ? SPELL_SUNBEAM : H_SPELL_SUNBEAM);
            Berserk_Timer = IN_MILISECONDS;		
        }else SBerserk_Timer -= diff;
        DoMeleeAttackIfReady();

        EnterEvadeIfOutOfCombatArea(diff);

    }

};

/////////////////////////////////////////////////
/// nature bomb / eonar's gift / healthy spore///
/////////////////////////////////////////////////
// update creature_template set ScriptName = 'mob_freya_ground' WHERE entry IN (34129,33228);
struct MANGOS_DLL_DECL mob_freya_groundAI : public ScriptedAI
{
     mob_freya_groundAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 NatureBomb_Timer;
    uint32 EonarsGift_Timer;
    bool EonarsGift_Pheromones;
    void Reset()
    {
        NatureBomb_Timer = urand(9,11)*IN_MILISECONDS;
        EonarsGift_Timer = urand(11,13)*IN_MILISECONDS;
        EonarsGift_Pheromones = true;
    }
    void AttackStart(Unit* pWho){return;}
    void UpdateAI(const uint32 diff)
    {
        if(!m_creature->isAlive())
            return;

        if(m_creature->GetEntry() == NPC_NATURE_BOMB)
            if(NatureBomb_Timer < diff)
            {
                m_creature->CastSpell(m_creature, m_bIsRegularMode ? SPELL_NATURE_BOMB : H_SPELL_NATURE_BOMB, true);
                m_creature->ForcedDespawn();
            }else NatureBomb_Timer -= diff;

        if(m_creature->GetEntry() == NPC_EONARS_GIFT)
        {
            if(EonarsGift_Timer < diff)
            {
                m_creature->CastSpell(GetFreya(m_creature, m_pInstance), m_bIsRegularMode ? SPELL_LIFEBINDER_GIFT : H_SPELL_LIFEBINDER_GIFT, true);
                // insert into spell_script_target values (62584, 1, 32906);
                EonarsGift_Timer = IN_MILISECONDS;
            }else EonarsGift_Timer -= diff;
            if(EonarsGift_Pheromones)
            {
                m_creature->CastSpell(m_creature, SPELL_PHEROMONES_LG, true);
                EonarsGift_Pheromones = false;
            }
        }
    }
};
///////////////////////////////////////////
/// iron roots / strenghtend iron roots ///
///////////////////////////////////////////
// update creature_template set ScriptName = 'mob_iron_roots' WHERE entry IN (33008,33168);
struct MANGOS_DLL_DECL mob_iron_rootsAI : public ScriptedAI
{
    mob_iron_rootsAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }
    
    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint64 m_uiVictimGUID;

    void Reset()
    {
        m_uiVictimGUID = 0;
    }
    void SetVictim(uint64 victim)
    {
        if (victim)
        {
            m_uiVictimGUID = victim;
            if (Unit* pVictim = Unit::GetUnit((*m_creature), m_uiVictimGUID))
            {
                if (m_creature->GetEntry() == NPC_STRENGTHENED_IRON_ROOTS)
                    pVictim->CastSpell(pVictim, m_bIsRegularMode ? SPELL_IRON_ROOTS_FREYA : H_SPELL_IRON_ROOTS_FREYA, true);
                if (m_creature->GetEntry() == NPC_IRON_ROOTS)
                    pVictim->CastSpell(pVictim, m_bIsRegularMode ? SPELL_IRON_ROOTS : H_SPELL_IRON_ROOTS, true);
            }
        }
    }

    void JustDied(Unit* Killer)
    {
        if (Unit* pVictim = Unit::GetUnit((*m_creature), m_uiVictimGUID))
        {
            if (m_creature->GetEntry() == NPC_STRENGTHENED_IRON_ROOTS)
                pVictim->RemoveAurasDueToSpell(m_bIsRegularMode ? SPELL_IRON_ROOTS_FREYA : H_SPELL_IRON_ROOTS_FREYA);
            if (m_creature->GetEntry() == NPC_IRON_ROOTS)
                pVictim->RemoveAurasDueToSpell(m_bIsRegularMode ? SPELL_IRON_ROOTS : H_SPELL_IRON_ROOTS);
        }
    }

    void MoveInLineOfSight(Unit* pWho) { }
    void UpdateAI(const uint32 uiDiff) { }
};

///////////////////
/// spawned adds///
///////////////////
// update creature_template set ScriptName = 'mob_freya_spawned' WHERE entry IN (33203, 33202, 32916, 32919, 32918);
struct MANGOS_DLL_DECL mob_freya_spawnedAI : public ScriptedAI
{
    mob_freya_spawnedAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }
    /*NPC_WAVE_1                        = 33203,
    NPC_WAVE_3_WATER                    = 33202,
    NPC_WAVE_3_SNAPLASHER               = 32916,
    NPC_WAVE_3_STORM                    = 32919,
    NPC_WAVE_10                         = 32918,*/

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    void Reset()
    {

    }
    void JustDied(Unit* Killer)
    {
        if (m_creature->GetEntry() == NPC_WAVE_1)
            ReduceStack(30);
        if (m_creature->GetEntry() == NPC_WAVE_3_WATER ||
            m_creature->GetEntry() == NPC_WAVE_3_SNAPLASHER ||
            m_creature->GetEntry() == NPC_WAVE_3_STORM)
            ReduceStack(10);
        if (m_creature->GetEntry() == 32918)
            ReduceStack(2);
    }
    void ReduceStack(uint8 count)
    {
        if(Aura *pAura = Unit::GetUnit((*m_creature), m_pInstance->GetData64(DATA_FREYA))->GetAura(SPELL_ATTUNED_TO_NATURE, EFFECT_INDEX_0))
        {
            if(count > pAura->GetStackAmount())
                count = pAura->GetStackAmount();
            pAura->SetStackAmount(pAura->GetStackAmount()-count);
            if(pAura->GetStackAmount() == 0)
                m_creature->RemoveAura(SPELL_ATTUNED_TO_NATURE, EFFECT_INDEX_0);

        }
    }
    void UpdateAI(const uint32 diff)
    {
        if(!m_creature->isAlive())
            return;
    }
};
CreatureAI* GetAI_boss_freya(Creature* pCreature)
{
    return new boss_freyaAI(pCreature);
}
CreatureAI* GetAI_mob_freya_ground(Creature* pCreature)
{
    return new mob_freya_groundAI(pCreature);
}
CreatureAI* GetAI_mob_iron_roots(Creature* pCreature)
{
    return new mob_iron_rootsAI(pCreature);
}
CreatureAI* GetAI_mob_freya_spawned(Creature* pCreature)
{
    return new mob_freya_spawnedAI(pCreature);
}

void AddSC_boss_freya()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_freya";
    newscript->GetAI = &GetAI_boss_freya;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_freya_ground";
    newscript->GetAI = &GetAI_mob_freya_ground;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_iron_roots";
    newscript->GetAI = &GetAI_mob_iron_roots;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_freya_spawned";
    newscript->GetAI = &GetAI_mob_freya_spawned;
    newscript->RegisterSelf();
}