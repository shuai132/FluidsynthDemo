#include "fluidsynth.h"
#include "MidiFile.h"

#include <iostream>
#include <thread>

using namespace smf;
using namespace std;

int main(int argc, char **argv)
{
    if (argc < 3) {
        cout << "Wrong argument! Usage example:" << endl;
        cout << argv[0] << " sf.sf2 midi.mid" << endl;
        return 1;
    }
    const char *sfPath = argv[1];
    const char *midiPath = argv[2];

    fluid_settings_t *settings = new_fluid_settings();
#ifdef __linux__
    fluid_settings_setstr(settings, "audio.driver", "alsa");
#endif
    fluid_synth_t *synth = new_fluid_synth(settings);
    fluid_audio_driver_t *adriver = new_fluid_audio_driver(settings, synth);
    fluid_synth_sfload(synth, sfPath, 1);
    fluid_synth_set_gain(synth, 1.0);

    MidiFile midiFile;
    auto state = midiFile.read(midiPath);
    if (state == 0) {
        cout << "bad midi file!" << endl;
        return 1;
    }

    int tpq = midiFile.getTicksPerQuarterNote();
    cout << "tpq = " << tpq << endl;

    int trackCount = midiFile.getTrackCount();
    cout << "trackCount = " << trackCount << endl;
    if (trackCount <= 1) {
        cout << "music track not found!" << endl;
        return 1;
    }

    midiFile.joinTracks();
    midiFile.deltaTicks();
    int eventCount = midiFile.getEventCount(0);

    for (int i = 0; i < eventCount; ++i) {
        MidiEvent event = midiFile.getEvent(0, i);
        int track = event.track;
        int tick = event.tick;
        int key = event.getKeyNumber();
        int velocity = event.getVelocity();
        cout << "track:" << track << "\t" << "tick:" << tick << "\t" << "key:" << key << "\t" << "velocity:" << velocity << endl;
        if (key == -1) continue;
        if (track == 0) continue;
        if (event.isNoteOn()) {
            fluid_synth_noteon(synth, 0, key, velocity);
        }
        else if (event.isNoteOff()) {
            fluid_synth_noteoff(synth, 0, key);
        }
        else {
            cout << "other event" << endl;
        }
        this_thread::sleep_for(std::chrono::milliseconds(int(midiFile.getTimeInSeconds(tick) * 1000)));
    }

    /* Clean up */
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
    return 0;
}
