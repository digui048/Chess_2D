#pragma once

#include "Utils/Vector2D.h"
#include <SDL3/SDL_events.h>
#include <bitset>
#include <vector>
#include <array>
#include <unordered_map>

enum class KeyState
{
    IDLE,
    UP,
    DOWN,
    REPEAT
};

class InputEventManager
{
public:
    InputEventManager();
    ~InputEventManager();

    void Update();
    bool HasEvent(SDL_EventType eventType) const { return m_events[eventType]; }

    KeyState GetKeyStatus(SDL_Scancode keycode) const;
    KeyState GetMouseButtonStatus(int mouseIndex) const;

    Vector2D GetMousePosition() const { return mousePos; }

private:
    template <size_t N>
    void AdvanceKeyStates(std::array<KeyState, N> &arr)
    {
        for (auto &state : arr)
        {
            switch (state)
            {
            case KeyState::DOWN:
                state = KeyState::REPEAT;
                break;

            case KeyState::UP:
                state = KeyState::IDLE;
                break;

            default:
                break;
            }
        }
    }

    std::bitset<SDL_EVENT_LAST> m_events;
    std::vector<Uint32> m_touchedEvents;
    std::array<KeyState, SDL_SCANCODE_COUNT> m_keyboard;
    std::array<KeyState, 5> m_mouse;
    std::unordered_map<std::string, bool> m_actions;

    Vector2D mousePos = {0.0f, 0.0f};
};