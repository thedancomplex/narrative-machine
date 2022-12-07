g++ -Wall -D__LINUX_ALSA__ -o midiprobe src/midiprobe.cpp src/RtMidi.cpp -I./include -lasound -lpthread
