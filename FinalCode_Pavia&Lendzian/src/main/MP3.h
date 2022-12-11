//Code inspired by https://www.electronics-lab.com/project/mp3-player-using-arduino-dfplayer-mini/
//Using the MP3-TF-16P DFPlayer Module (https://usermanual.wiki/Manual/DFPlayerMiniManual.234442183/pdf)

#ifndef MP3_h
#define MP3_h

#include "Devices.h"

#include "HardwareSerial.h"
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]
# define ACTIVATED LOW

#define MILLISECONDS_IN_BACKGROUND_TRACK 112000
#define MILLISECONDS_IN_SPOKEN_TRACK 6000
#define BACKGROUND_TRACK_NUM 2
#define SPOKEN_TRACK_NUM 1
#define NO_TRACK -1

//This class handles the mp3 player module commands.
class MP3 : public Device
{
    HardwareSerial mySerial;
    Potentiometer potentiometer;
    Timer timer;
    int current_volume = -1;

    int currentTrackPlaying;
    unsigned long timeCurrentTrackStartedPlaying;

    static MP3* gInstance;

    void ExecuteCMD(byte CMD, byte Par1, byte Par2);

    MP3();

    public:

    static MP3& instance();

    void SetVolume(int volume);
    void Play(int audio_file_number);
    void PlayBackgroundMusicIfIdle();
    void AdjustVolumeAsRequested(); //uses the potentiometer
};

#endif