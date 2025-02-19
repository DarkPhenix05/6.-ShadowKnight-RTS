#include "TroopManager.h"

TroopManager::TroopManager()
{
    allCharacters.clear();
    allElements.clear();
}

TroopManager::~TroopManager()
{
}

void TroopManager::PushCharacter(Character* _character)
{
    allCharacters.push_back(_character);
    allElements.push_back(_character);
}

void TroopManager::DeleteCharacters()
{
    allCharacters.clear();
}

void TroopManager::DeleteCharacter(int idx)
{
    allCharacters.erase(allCharacters.begin() + idx);
}

std::vector<Character*> TroopManager::GetCharacters()
{
    return allCharacters;
}

void TroopManager::PushGameObject(GameObject* _gameobject)
{
    allElements.push_back(_gameobject);
}

void TroopManager::DeleteGameObjects()
{
    allElements.clear();
}

void TroopManager::DrawAllElements()
{
    for (int i = 0; i < allCharacters.size(); i++)
    {
        allCharacters[i]->Draw(false);
    }
    if (currentCharacter != nullptr)
    {
        currentCharacter->Draw(true);
    }
}

void TroopManager::UpdateAllElements(float dt)
{
    for (int i = 0; i < allElements.size(); i++)
    {
        allElements[i]->Update(dt);
    } 
}

void TroopManager::SetCurrentCharacter(Character* _gameobject)
{
    currentCharacter = _gameobject;
}

Character* TroopManager::GetCurrentCharacter()
{
    return currentCharacter;
}

Button* TroopManager::GetBT_MOVE()
{
    return  currentCharacter->BT_MOVE;
}

Button* TroopManager::GetBT_ATTACK()
{
    return  currentCharacter->BT_ATTACK;
}

Button* TroopManager::GetBT_CANCEL()
{
    return currentCharacter->BT_CANCEL;
}

void TroopManager::UpdateButtons(Vector2 mousePos)
{
    currentCharacter->BT_MOVE->Update(mousePos);
    currentCharacter->BT_ATTACK->Update(mousePos);
    currentCharacter->BT_CANCEL->Update(mousePos);
}

void TroopManager::DrawAllButtons()
{
    currentCharacter->BT_MOVE->Draw();
    currentCharacter->BT_ATTACK->Draw();
    currentCharacter->BT_CANCEL->Draw();
}

void TroopManager::FindCharacterInPos(Vector2 mousePos, int _size)
{
    std:: cout << '\n';
    currentCharacter = nullptr;
    for (int i= 0; i < allElements.size(); i++)
    {
        float character_x = allCharacters[i]->_pos.x;
        float character_y = allCharacters[i]->_pos.y;
        
        std::cout <<"CHARACTER: " <<character_x << ", " << character_y << '\n';
        std:: cout <<"MOUSE: " << mousePos.x << " ; " << mousePos.y << '\n';
        std:: cout << '\n';
        
        if (character_x >= (mousePos.x - _size /2.0f) * 2.0f &&
            character_x < (mousePos.x + _size/2.0f) * 2)
        {
            if (character_y >= (mousePos.y - _size/2.0f) * 2.0f &&
                character_y < (mousePos.y + _size /2.0f) * 2.0f)
            {
                SetCurrentCharacter(allCharacters[i]);
                std::cout << "SELECTED: " << currentCharacter << '\n';
            }
        }
    }
}
