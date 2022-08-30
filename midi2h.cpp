#include <iostream>
#include <sstream>
#include <vector>

#include "MidiFile.h"
#include "midi.h"

using namespace smf;
using namespace std;

std::vector<NoteEvent> noteEvents;

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Wrong argument! Usage example:" << endl;
    cout << argv[0] << " midi.mid" << endl;
    return 1;
  }
  const char *midiPath = argv[1];
  cout << sizeof(NoteEvent);

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
  cout << eventCount << endl;

  for (int i = 0; i < eventCount; ++i) {
    MidiEvent event = midiFile.getEvent(0, i);
    int track = event.track;
    int tick = event.tick;
    int tickMs = (int)(midiFile.getTimeInSeconds(tick) * 1000);
    int key = event.getKeyNumber();
    int velocity = event.getVelocity();
    cout << "track:" << track << "\t"
         << "tick:" << tick << "\t"
         << "key:" << key << "\t"
         << "tickMs:" << tickMs << "\t"
         << "velocity:" << velocity << endl;
    if (key == -1) continue;
    if (track == 0) continue;
    NoteEvent e;
    e.track = track;
    e.isOn = event.isNoteOn();
    e.key = key;
    e.tickMs = tickMs;
    noteEvents.push_back(e);
  }

  std::stringstream output;
  output << R"(#pragma once
const NoteEvent music[] = {)";
  for (const auto &e : noteEvents) {
    output << "{" << (int)e.track << ", " << (e.isOn ? "true" : "false") << ", " << (int)e.key << ", " << e.tickMs << "}, ";
  }
  output << "};";

  printf("file: \n\n%s", output.str().c_str());

  return 0;
}
