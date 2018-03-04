#include "fluidsynth.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    if(argc < 3){
        cout<<"Wrong argument! Usage example:"<<endl;
        cout<<argv[0]<<" sf.sf2 midi.mid"<<endl;
        return 1;
    }
    const char* sfPath   = argv[1];
    const char* midiPath = argv[2];

    fluid_settings_t* settings = new_fluid_settings();
#ifdef __linux__
    fluid_settings_setstr(settings, "audio.driver", "alsa");
#endif
    fluid_synth_t* synth = new_fluid_synth(settings);
    fluid_audio_driver_t* adriver = new_fluid_audio_driver(settings, synth);
    fluid_synth_sfload(synth, sfPath, 1);
    fluid_synth_set_gain(synth, 1.0);

    fluid_player_t* player = new_fluid_player(synth);

    fluid_player_add(player, midiPath);
    fluid_player_play(player);
    fluid_player_join(player);

    /* Clean up */
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
    return 0;
}
