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
    SPELL_POTENT_PHEROMONES             = 64321,

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
    SPELL_BRIGHTLEAFS_ESSENCE           = 62385,
    SPELL_EFFECT_BRIGHTLEAF             = 63294,

    //abilities with Elder Ironbranch
    SPELL_IRON_ROOTS_FREYA              = 62283,
    H_SPELL_IRON_ROOTS_FREYA            = 62930,
    SPELL_IRONBRANCHS_ESSENCE           = 62387,
    SPELL_EFFECT_IRONBRANCH             = 63292,
    
    SPELL_STRENGTHENED_IRON_ROOTS_SUMM  = 63601,
    
    //abilities with Elder Stonebark 
    SPELL_GROUND_TREMOR_FREYA           = 62437,
    H_SPELL_GROUND_TREMOR_FREYA         = 62859,
    SPELL_STONEBARKS_ESSENCE            = 62386,
    SPELL_EFFECT_STONEBARK              = 63295,

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

    //Elder Stonebark
    SPELL_FIST_OF_STONE                 = 62344,
    SPELL_BROKEN_BONES                  = 62356,
    SPELL_GROUND_TREMOR                 = 62325,
    H_SPELL_GROUND_TREMOR               = 62932,
    SPELL_PETRIFIED_BARK                = 62337,
    H_SPELL_PETRIFIED_BARK              = 62933,

    SPELL_LIFEBINDERS_VISUAL            = 62579,
    SPELL_LIFEBINDER_GROW               = 44833,

    SPELL_SUMMON_CHEST_1                = 62950,
    SPELL_SUMMON_CHEST_2                = 62952,
    SPELL_SUMMON_CHEST_3                = 62953,
    SPELL_SUMMON_CHEST_4                = 62954,
    SPELL_SUMMON_CHEST_5                = 62955,
    SPELL_SUMMON_CHEST_6                = 62956,
    SPELL_SUMMON_CHEST_7                = 62957,
    SPELL_SUMMON_CHEST_8                = 62958,

    NPC_NATURE_BOMB                     = 34129,
    NPC_EONARS_GIFT                     = 33228,
    NPC_HEALTHY_SPORE                   = 33215,
    NPC_IRON_ROOTS                      = 33008,
    NPC_STRENGTHENED_IRON_ROOTS         = 33168,

    NPC_ELDER_BRIGHTLEAF                = 32915,
    NPC_ELDER_IRONBRANCH                = 32913,
    NPC_ELDER_STONEBARK                 = 32914,

    NPC_WAVE_1                          = 33203,
    NPC_WAVE_3_WATER                    = 33202,
    NPC_WAVE_3_SNAPLASHER               = 32916,
    NPC_WAVE_3_STORM                    = 32919,
    NPC_WAVE_10                         = 32918,

    ACHI_KNOCK_1_NORM                   = 3177,
    ACHI_KNOCK_2_NORM                   = 3178,
    ACHI_KNOCK_3_NORM                   = 3179,
    ACHI_KNOCK_1_HC                     = 3185,
    ACHI_KNOCK_2_HC                     = 3186,
    ACHI_KNOCK_3_HC                     = 3187,

};


Creature* GetFreya(Creature* pCreature, ScriptedInstance* instance){return (Creature*)Unit::GetUnit((*pCreature), instance->GetData64(DATA_FREYA));}

///////////////
//// Freya ////
///////////////
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
    uint32 ChangeFaction_Timer;
    uint32 EndPhaseDespawn_Timer;
    bool EndPhase;
    bool HardMode;
    bool Knock1;
    bool Knock2;
    bool FactionChanged;

    void Reset()
    {
        Wave_Timer = urand(9,12)*IN_MILISECONDS;
        LifebinderGift_Timer = urand(19,23)*IN_MILISECONDS;
        Sunbeam_Timer = urand(44,49)*IN_MILISECONDS;
        Wave_Count = 0;
        Berserk_Timer = 10*MINUTE*IN_MILISECONDS;
        ChangeFaction_Timer = 7*IN_MILISECONDS;
        EndPhaseDespawn_Timer = 10*IN_MILISECONDS;
        FactionChanged = false;
        HardMode = false;
        EndPhase = false;
        Knock1 = false;
        Knock2 = false;

        m_creature->setFaction(16);
    }

    void KilledUnit(Unit *victim)
    {
    }

    void Aggro(Unit* pWho)
    {
        //DoScriptText(SAY_AGGRO, m_creature); //The Conservatory must be protected
        m_creature->SetInCombatWithZone();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_FREYA, IN_PROGRESS);
        
        BuffOnAggro();
    }
    void AttackStart(Unit* pWho)
    {
        if (!pWho)
            return;

        if (EndPhase)
            return;
        
        if (m_creature->Attack(pWho, true))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);

            if (IsCombatMovement())
                m_creature->GetMotionMaster()->MoveChase(pWho);
        }
    }
    
    void CompleteAchievement(uint16 entry)
    {
        /*Map* pMap = m_creature->GetMap();
        AchievementEntry const *Achievement = GetAchievementStore()->LookupEntry(entry);
        if(Achievement && pMap)
        {
            Map::PlayerList const &lPlayers = pMap->GetPlayers();
            if (!lPlayers.isEmpty())
            {
                for(Map::PlayerList::const_iterator itr = lPlayers.begin(); itr != lPlayers.end(); ++itr)
                {
                    if (Player* pPlayer = itr->getSource())
                        pPlayer->GetAchievementMgr().CompletedAchievement(Achievement);
                }
            }
        }*/
    }
    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (damage > m_creature->GetHealth())
        {
            damage = 0;
            m_creature->SetHealth(1);
            EndPhase = true;
        }
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

        for(uint32 i = NPC_ELDER_IRONBRANCH; i <= NPC_ELDER_BRIGHTLEAF; i++)
            if(Creature* pTemp = GetClosestCreatureWithEntry(m_creature, i, 180.0f))
                pTemp->RemoveAllAuras();
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
        bool StonebarkAlive;
        bool IronbranchAlive;
        if(Creature* pBright = GetClosestCreatureWithEntry(m_creature, NPC_ELDER_BRIGHTLEAF, 180.0f))
        {
            m_creature->CastSpell(m_creature, SPELL_BRIGHTLEAFS_ESSENCE, true);
            pBright->CastSpell(m_creature, SPELL_EFFECT_BRIGHTLEAF, true);
            pBright->CastSpell(pBright, SPELL_DRAINED_OF_POWER, true);
            BrightleafAlive = true;
        }else BrightleafAlive = false;

        if(Creature* pIron = GetClosestCreatureWithEntry(m_creature, NPC_ELDER_IRONBRANCH, 180.0f))
        {
            m_creature->CastSpell(m_creature, SPELL_IRONBRANCHS_ESSENCE, true);
            pIron->CastSpell(m_creature, SPELL_EFFECT_IRONBRANCH, true);
            pIron->CastSpell(pIron, SPELL_DRAINED_OF_POWER, true);
            IronbranchAlive = true;
        }else IronbranchAlive = false;

        if(Creature* pStone = GetClosestCreatureWithEntry(m_creature, NPC_ELDER_STONEBARK, 180.0f))
        {
            m_creature->CastSpell(m_creature, SPELL_STONEBARKS_ESSENCE, true);
            pStone->CastSpell(m_creature, SPELL_EFFECT_STONEBARK, true);
            pStone->CastSpell(pStone, SPELL_DRAINED_OF_POWER, true);
            StonebarkAlive = true;
        }else StonebarkAlive = false;

        if(BrightleafAlive && IronbranchAlive && StonebarkAlive)
            HardMode = true;
        if(BrightleafAlive || IronbranchAlive || StonebarkAlive)
            Knock1 = true;
        if((BrightleafAlive && IronbranchAlive) || 
            (BrightleafAlive && StonebarkAlive) || 
            (IronbranchAlive && StonebarkAlive))
            Knock2 = true;

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
        if(EndPhase)
        {
            if(ChangeFaction_Timer < diff && !FactionChanged)
            {
                m_creature->RemoveAllAuras();
                m_creature->CastSpell(SelectUnit(SELECT_TARGET_RANDOM,0), m_bIsRegularMode ? (HardMode ? SPELL_SUMMON_CHEST_2 : SPELL_SUMMON_CHEST_1) : (HardMode ? SPELL_SUMMON_CHEST_4 : SPELL_SUMMON_CHEST_3), true);
                
                if(HardMode)
                    CompleteAchievement(m_bIsRegularMode ? ACHI_KNOCK_3_NORM : ACHI_KNOCK_3_HC);
                else if(Knock2)
                    CompleteAchievement(m_bIsRegularMode ? ACHI_KNOCK_2_NORM : ACHI_KNOCK_2_HC);
                else if(Knock1)
                    CompleteAchievement(m_bIsRegularMode ? ACHI_KNOCK_1_NORM : ACHI_KNOCK_1_HC);				
                m_creature->ClearInCombat();
                m_creature->setFaction(m_creature->getVictim()->getFaction());
                FactionChanged = true;
            }else ChangeFaction_Timer -= diff;

            if(EndPhaseDespawn_Timer < diff)
            {
                m_creature->ForcedDespawn();
            }else EndPhaseDespawn_Timer -= diff;
            return;
        }
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
        

        if(Wave_Count == 6 /*something like phase2 check*/)
        {
        }

        if(Berserk_Timer < diff)
        {
            DoCast(SelectUnit(SELECT_TARGET_RANDOM,0), m_bIsRegularMode ? SPELL_SUNBEAM : H_SPELL_SUNBEAM);
            Berserk_Timer = IN_MILISECONDS;		
        }else Berserk_Timer -= diff;
        DoMeleeAttackIfReady();

    }

};

/////////////////////////////////////////////////
/// nature bomb / eonar's gift / healthy spore///
/////////////////////////////////////////////////
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
    uint32 NonSelectable_Timer;
    uint32 Grow_Timer;
    uint32 Grow_Count;

    bool NpcNatureBomb;
    bool NpcEonarsGift;
    bool NpcHealthySpore;

    bool Start;
    bool MaxSize;

    void Reset()
    {
        NatureBomb_Timer = urand(9,11)*IN_MILISECONDS;
        EonarsGift_Timer = urand(11,13)*IN_MILISECONDS;
        NonSelectable_Timer = 5*IN_MILISECONDS;
        Grow_Timer = 8*IN_MILISECONDS;
        Grow_Count = 1;
        Start = true;
        MaxSize = false;
        NpcNatureBomb = false;
        NpcEonarsGift = false;
        NpcHealthySpore = false;
        if(m_creature->GetEntry() == NPC_NATURE_BOMB)
            NpcNatureBomb = true;
        if(m_creature->GetEntry() == NPC_EONARS_GIFT)
            NpcEonarsGift = true;
        if(m_creature->GetEntry() == NPC_HEALTHY_SPORE)
            NpcHealthySpore = true;

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        if(NpcEonarsGift)
            m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.1);
    }
    void AttackStart(Unit* pWho){return;}
    void UpdateAI(const uint32 diff)
    {
        if(!m_creature->isAlive())
            return;

        if (Start)
        {
            if(NpcEonarsGift)
            {
                m_creature->CastSpell(m_creature, SPELL_LIFEBINDERS_VISUAL, true);
                m_creature->CastSpell(m_creature, 62559, true);
            }
            if(NpcHealthySpore)
                m_creature->CastSpell(m_creature, SPELL_POTENT_PHEROMONES, true);
            Start = false;
        }
        if(NpcNatureBomb)
            if(NatureBomb_Timer < diff)
            {
                m_creature->CastSpell(m_creature, m_bIsRegularMode ? SPELL_NATURE_BOMB : H_SPELL_NATURE_BOMB, true);
                m_creature->ForcedDespawn();
            }else NatureBomb_Timer -= diff;

        if(NpcEonarsGift)
        {
            if (Grow_Timer < diff && Grow_Count <= 10)
            {
                m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.1*Grow_Count);
                Grow_Timer = 700;
                Grow_Count ++;
            }else Grow_Timer -= diff;

            if(EonarsGift_Timer < diff)
            {
                m_creature->CastSpell(GetFreya(m_creature, m_pInstance), m_bIsRegularMode ? SPELL_LIFEBINDER_GIFT : H_SPELL_LIFEBINDER_GIFT, true);
                EonarsGift_Timer = IN_MILISECONDS;
            }else EonarsGift_Timer -= diff;

            if(NonSelectable_Timer < diff && m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
            {
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                m_creature->CastSpell(m_creature, SPELL_PHEROMONES_LG, true);
            }else NonSelectable_Timer -= diff;
        }
    }
};
///////////////////////////////////////////
/// iron roots / strenghtend iron roots ///
///////////////////////////////////////////
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
    bool NpcIronRoots;
    bool NpcStrengthenedIronRoots;

    uint64 m_uiVictimGUID;

    void Reset()
    {
        m_uiVictimGUID = 0;
        NpcStrengthenedIronRoots = false;
        NpcIronRoots = false;
        if (m_creature->GetEntry() == NPC_STRENGTHENED_IRON_ROOTS)
            NpcStrengthenedIronRoots = true;
        if (m_creature->GetEntry() == NPC_IRON_ROOTS)
            NpcIronRoots = true;
    }
    void SetVictim(uint64 victim)
    {
        if (victim)
        {
            m_uiVictimGUID = victim;
            if (Unit* pVictim = Unit::GetUnit((*m_creature), m_uiVictimGUID))
            {
                if (NpcStrengthenedIronRoots)
                    pVictim->CastSpell(pVictim, m_bIsRegularMode ? SPELL_IRON_ROOTS_FREYA : H_SPELL_IRON_ROOTS_FREYA, true);
                if (NpcIronRoots)
                    pVictim->CastSpell(pVictim, m_bIsRegularMode ? SPELL_IRON_ROOTS : H_SPELL_IRON_ROOTS, true);
            }
        }
    }

    void JustDied(Unit* Killer)
    {
        if (Unit* pVictim = Unit::GetUnit((*m_creature), m_uiVictimGUID))
        {
            if (NpcStrengthenedIronRoots)
                pVictim->RemoveAurasDueToSpell(m_bIsRegularMode ? SPELL_IRON_ROOTS_FREYA : H_SPELL_IRON_ROOTS_FREYA);
            if (NpcIronRoots)
                pVictim->RemoveAurasDueToSpell(m_bIsRegularMode ? SPELL_IRON_ROOTS : H_SPELL_IRON_ROOTS);
        }
    }

    void MoveInLineOfSight(Unit* pWho) { }
    void UpdateAI(const uint32 uiDiff) { }
};

///////////////////
/// spawned adds///
///////////////////
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

        if (!m_creature->getVictim())
            AttackStart(SelectUnit(SELECT_TARGET_RANDOM,0));
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

/*
UPDATE creature_template SET ScriptName = 'boss_freya' WHERE entry = 32906;
UPDATE creature_template SET ScriptName = 'mob_freya_ground' WHERE entry IN (34129,33228, 33215);
UPDATE creature_template SET ScriptName = 'mob_iron_roots' WHERE entry IN (33008,33168);
UPDATE creature_template SET ScriptName = 'mob_freya_spawned' WHERE entry IN (33203, 33202, 32916, 32919, 32918);
INSERT IGNORE INTO spell_script_target VALUES (62385, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (62387, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (62386, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (62584, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (62619, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (63294, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (63295, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (63292, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (62584, 1, 32906);
INSERT IGNORE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES('194324','3','8628','Freya\'s Gift','','','','0','0','1','0','0','0','0','0','0','1634','0','0','1','0','0','0','0','0','0','0','1','0','1','0','1','0','0','0','0','0','0','0','0','');
INSERT IGNORE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES('194325','3','8628','Freya\'s Gift','','','','0','0','1','0','0','0','0','0','0','1634','0','0','1','0','0','0','0','0','0','0','1','0','1','0','1','0','0','0','0','0','0','0','0','');
INSERT IGNORE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES('194326','3','8628','Freya\'s Gift','','','','0','0','1','0','0','0','0','0','0','1634','0','0','1','0','0','0','0','0','0','0','1','0','1','0','1','0','0','0','0','0','0','0','0','');
INSERT IGNORE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES('194327','3','8628','Freya\'s Gift','','','','0','0','1','0','0','0','0','0','0','1634','0','0','1','0','0','0','0','0','0','0','1','0','1','0','1','0','0','0','0','0','0','0','0','');
UPDATE creature_template SET scale = 0.1 WHERE entry = 33228;
// 194324 - normal, 194325 - normal hard, 194326 - hc, 194327 - hc hard
*/