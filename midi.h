#pragma once

#include <cstdint>
#include <vector>

struct NoteEvent
{
    NoteEvent() = default;
    NoteEvent(bool isOn, uint8_t key, uint16_t tickMs)
        : isOn(isOn), key(key), tickMs(tickMs)
    {
    }
    bool isOn = false;
    uint8_t key = 0;
    uint16_t tickMs = 0;
};

using Music = NoteEvent[];
using NoteHandle = std::function<void(NoteEvent)>;

inline void playMusic(const NoteEvent* music, uint16_t len, const NoteHandle& handle) {
    for (int i = 0; i < len; ++i) {
        handle(music[i]);
    }
}
