#include "CombatSystem.h"
#include "HitResult.h"
#include "Items.h"
#include "Ui.h"
#include "PlayerChoice.h"
#include <iostream>
#include <cstdlib>
#include <limits>      
#include <vector>      

float GetElementMultiplier(Elements attacker, Elements defender)
{
    if (attacker == Elements::WATER && defender == Elements::FIRE)
        return 2.0f;
    if (attacker == Elements::WATER && defender == Elements::GRASS)
        return 0.5f;

    if (attacker == Elements::FIRE && defender == Elements::GRASS)
        return 2.0f;
    if (attacker == Elements::FIRE && defender == Elements::WATER)
        return 0.5f;

    if (attacker == Elements::GRASS && defender == Elements::WATER)
        return 2.0f;
    if (attacker == Elements::GRASS && defender == Elements::FIRE)
        return 0.5f;

    return 1.0f;
}

void CombatSystem::StartCombat(PlayerParty& party, Enemy& enemy, Inventory& inventory)
{

	Ui::PrintCombatVisual();

    std::cout << "\n  Combat started between your party and " << enemy.GetName() << "!\n\n";

    std::cout << "Choose your starting unit:\n";
	//todo: print party members with their index using ui
    Unit* currentUnit = ChoosePartyUnit(party);

    while (!party.IsDefeated() && enemy.GetHp() > 0)
    {
		system("cls");
        Ui::PrintCombatVisual();

        if (currentUnit->GetHp() <= 0)
        {
            std::cout << currentUnit->GetName() << " is down. Please switch to another unit.\n";
            currentUnit = ChoosePartyUnit(party);
            continue;
        }

        std::cout << "\n " << currentUnit->GetName() << "'s turn:\n";
        std::cout << "Choose action:\n1. Attack\n2. Use Item\n3. Switch Unit\nChoice: ";
        int choice;
        std::cin >> choice;

        switch (static_cast<PlayerChoice>(choice))
        {
        case PlayerChoice::ATTACK:
        {
            std::cout << "Choose attack type:\n1. Normal Attack\n2. Elemental Attack\nChoice: ";
            int attackType;
            std::cin >> attackType;

            HitResult result = currentUnit->HitOrMiss();

            int baseDamage = (attackType == 1) ? currentUnit->GetNormalDmg() : static_cast<int>(currentUnit->GetElementalDmg() * GetElementMultiplier(currentUnit->GetElement(), enemy.GetElement()));

            switch (result)
            {
            case HitResult::CRIT:
                std::cout << "[CRIT] ";
                enemy.TakeDamage(baseDamage * 2);
                break;
            case HitResult::HIT:
                std::cout << "[HIT] ";
                enemy.TakeDamage(baseDamage);
                break;
            case HitResult::MISS:
                std::cout << "[MISS] Attack missed!\n";
                break;
            }
            std::cout << "Enemy HP: " << enemy.GetHp() << "\n";

            if (enemy.GetHp() <= 0)
            {
                std::cout << "\n Enemy defeated!\n";
                int expReward = 10 + enemy.GetLevel() * 5;
                std::cout << currentUnit->GetName() << " gains " << expReward << " EXP!\n";
                currentUnit->AddExp(expReward);

                if (currentUnit->GetLevel() * 10 <= currentUnit->GetExp())
                {
                    currentUnit->PlayerLevelUp();
                    std::cout << currentUnit->GetName() << " leveled up to level " << currentUnit->GetLevel() << "!\n";
                }
                return;
            }
            break;
        }
        case PlayerChoice::USE_ITEM:
            UseItemMenu(inventory, currentUnit);
            break;
        case PlayerChoice::SWITCH_UNIT:
            currentUnit = ChoosePartyUnit(party);
            break;
        default:
            std::cout << "Invalid choice, turn skipped.\n";
            break;
        }

        std::cout << "\nEnemy's turn:\n";
        for (Unit& member : party.GetAll())
        {
            if (member.GetHp() <= 0) continue;

            HitResult result = enemy.HitOrMiss();
            std::cout << enemy.GetName() << " attacks " << member.GetName() << "! ";

            int totalDamage = enemy.GetNormalDmg() + static_cast<int>(enemy.GetElementalDmg() * GetElementMultiplier(enemy.GetElement(), member.GetElement()));
            switch (result)
            {
            case HitResult::CRIT:
                std::cout << "[CRIT] ";
                member.TakeDamage(totalDamage * 2);
                break;
            case HitResult::HIT:
                std::cout << "[HIT] ";
                member.TakeDamage(totalDamage);
                break;
            case HitResult::MISS:
                std::cout << "[MISS] Attack missed!\n";
                continue;
            }
            std::cout << member.GetName() << " HP: " << member.GetHp() << "\n";
            if (party.IsDefeated())
            {
                std::cout << "\n Your party was defeated!\n";
                return;
            }
        }
    }
}

Unit* CombatSystem::ChoosePartyUnit(PlayerParty& party)
{
    std::cout << "\nAvailable Units:\n";
    auto& members = party.GetAll();

    int choice;
    bool validChoice = false;  // fixed typo here

    do
    {
        char ch;
        std::cout << "Choose unit index: ";
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > static_cast<int>(members.size()))
        {
            std::cin.clear();
            while (std::cin.get(ch) && ch != '\n');
            std::cout << "Invalid choice. Please try again.\n";
        }
        else if (members[choice - 1].GetHp() <= 0)
        {
            std::cout << "This unit is down. Please choose another unit.\n";
        }
        else
        {
            validChoice = true;
            while (std::cin.get(ch) && ch != '\n');
        }
    } while (!validChoice);

    return &members[choice - 1];
}

void CombatSystem::UseItemMenu(Inventory& inventory, Unit* target)
{
    std::cout << "\nChoose item to use:\n";
    std::cout << static_cast<int>(Items::HP_POTION) << ". Heal (HP_POTION)\n"
        << static_cast<int>(Items::NORMAL_ATTACK_POTION) << ". Power Boost (NORMAL_ATTACK_POTION)\n"
        << static_cast<int>(Items::SMOKE_BOMB) << ". Smoke Bomb (SMOKE_BOMB)\n"
        << "Choice: ";

    int itemChoiceInt;
    std::cin >> itemChoiceInt;
    Items itemChoice = static_cast<Items>(itemChoiceInt);

    switch (itemChoice)
    {
    case Items::HP_POTION:
        if (inventory.IsInInventory(Items::HP_POTION))
        {
            target->Heal(25);
            inventory.UseItem(Items::HP_POTION);
            std::cout << "Healed 25 HP. Current HP: " << target->GetHp() << "\n";
        }
        else
            std::cout << "No health potions left!\n";
        break;

    case Items::NORMAL_ATTACK_POTION:
        if (inventory.IsInInventory(Items::NORMAL_ATTACK_POTION))
        {
            target->IncreaseNormalDmg(5);
            inventory.UseItem(Items::NORMAL_ATTACK_POTION);
            std::cout << "Increased normal damage by 5.\n";
        }
        else
            std::cout << "No power potions left!\n";
        break;

    case Items::ELEMENTAL_ATTACK_POTION:
        if (inventory.IsInInventory(Items::ELEMENTAL_ATTACK_POTION))
        {
            target->IncreaseElementalDmg(5);
            inventory.UseItem(Items::ELEMENTAL_ATTACK_POTION);
            std::cout << "Increased elemental damage by 5.\n";
        }
        else
            std::cout << "No power potions left!\n";
        break;

    case Items::SMOKE_BOMB:
        if (inventory.IsInInventory(Items::SMOKE_BOMB))
        {
            inventory.UseItem(Items::SMOKE_BOMB);
            std::cout << "You escaped using a smoke bomb!\n";
            std::exit(0);
        }
        else
            std::cout << "No smoke bombs left!\n";
        break;

    default:
        std::cout << "Invalid item choice.\n";
        break;
    }
}
