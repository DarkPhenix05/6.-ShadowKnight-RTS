#pragma once
#pragma once
#include <vector>
#include "Character.h"

class TroopManager
{
private:
    std::vector<Character*> allCharacters = std::vector<Character*>();
    std::vector<GameObject*> allElements = std::vector<GameObject*>();

    Character* currentCharacter = nullptr;

public:
    TroopManager();
    ~TroopManager();

    void PushCharacter(Character* _character);
    void DeleteCharacters();
    void DeleteCharacter(int idx);
    std::vector<Character*> GetCharacters();

    void PushGameObject(GameObject* _gameobject);
    void DeleteGameObjects();
    void DrawAllElements();

    void UpdateAllElements(float dt);

    void SetCurrentCharacter(Character* _gameobject);
    Character* GetCurrentCharacter();
    Button* GetBT_MOVE();
    Button* GetBT_ATTACK();
    Button* GetBT_CANCEL();

    void UpdateButtons(Vector2 mousePos);
    void DrawAllButtons();

    void FindCharacterInPos(Vector2 mousePos, int size);
};
