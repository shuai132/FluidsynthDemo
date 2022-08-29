#include "fluidsynth.h"
#include "midi.h"
#include "music.h"

#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2) {
        cout << "Wrong argument! Usage example:" << endl;
        cout << argv[0] << " sf.sf2" << endl;
        return 1;
    }
    const char *sfPath = argv[1];

    fluid_settings_t *settings = new_fluid_settings();
#ifdef __linux__
    fluid_settings_setstr(settings, "audio.driver", "alsa");
#endif
    fluid_synth_t *synth = new_fluid_synth(settings);
    fluid_audio_driver_t *adriver = new_fluid_audio_driver(settings, synth);
    fluid_synth_sfload(synth, sfPath, 1);
    fluid_synth_set_gain(synth, 1.0);

    playMusic(SuperMario, sizeof SuperMario, [&](NoteEvent e)
    {
        float speed = 1;
//        if (e.track != 3) {
//            this_thread::sleep_for(std::chrono::milliseconds((uint16_t) ((float) e.tickMs / speed)));
//            return;
//        }
        cout << "track:" << (int)e.track
             << "\t" << "on:" << (int)e.isOn
             << "\t" << "key:" << (int)e.key
             << "\t" << "tickMs:" << e.tickMs << endl;
        if (e.isOn) {
            fluid_synth_noteon(synth, 0, e.key, 127);
        }
        else {
            fluid_synth_noteoff(synth, 0, e.key);
        }
        this_thread::sleep_for(std::chrono::milliseconds((uint16_t) ((float) e.tickMs / speed)));
    });

    /* Clean up */
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
    return 0;
}
