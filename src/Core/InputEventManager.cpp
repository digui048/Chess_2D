#include "InputEventManager.h"

InputEventManager::InputEventManager()
{
    m_keyboard.fill(KeyState::IDLE);
    m_mouse.fill(KeyState::IDLE);

    m_touchedEvents.reserve(15);
}

InputEventManager::~InputEventManager()
{
}

void InputEventManager::Update()
{
    for (Uint32 t : m_touchedEvents)
    {
        m_events[t] = false;
    }

    m_touchedEvents.clear();

    AdvanceKeyStates(m_keyboard);
    AdvanceKeyStates(m_mouse);

    m_actions["anyKey"] = false;
    m_actions["anyMouseButton"] = false;
    m_actions["any"] = false;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (!m_events[event.type])
        {
            m_events.set(event.type, true);
            m_touchedEvents.push_back(event.type);
        }

        switch (event.type)
        {
        case SDL_EVENT_KEY_DOWN:

            if (!event.key.repeat)
            {
                m_keyboard[event.key.scancode] = KeyState::DOWN;
                m_actions["any"] = true;
                m_actions["anyKey"] = true;
            }
            break;

        case SDL_EVENT_KEY_UP:
            m_keyboard[event.key.scancode] = KeyState::UP;
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event.button.button <= m_mouse.size())
            {
                m_mouse[event.button.button - 1] = KeyState::DOWN;
                m_actions["any"] = true;
                m_actions["anyMouseButton"] = true;
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (event.button.button <= m_mouse.size())
                m_mouse[event.button.button - 1] = KeyState::UP;
            break;

        case SDL_EVENT_MOUSE_MOTION:
            mousePos = {event.motion.x, event.motion.y};
            break;
        }
    }
}

KeyState InputEventManager::GetKeyStatus(SDL_Scancode keycode) const
{
    return m_keyboard[keycode];
}

KeyState InputEventManager::GetMouseButtonStatus(int mouseIndex) const
{
    return m_mouse[mouseIndex];
}
