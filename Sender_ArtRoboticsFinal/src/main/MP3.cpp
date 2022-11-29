#include "mp3.h"

MP3* MP3::gInstance = nullptr;

MP3::MP3()
:Device("MP3"),
mySerial(1),
potentiometer("MP3Potentiometer", SPEAKER_POT_PIN, 0, 30),
currentTrackPlaying(NO_TRACK)
{
    mySerial.begin(9600, SERIAL_8N1, mp3RXPort, mp3TXPort); //BaudRate, SerialMode, RX_pin, TX_pin
}

MP3& MP3::instance()
{
    if (gInstance == nullptr)
    {
        gInstance = new MP3();
    }

    return *gInstance;
}

void MP3::Play(int audio_file_number)
{
    ExecuteCMD(0x03, highByte(audio_file_number), lowByte(audio_file_number)); 
    //Specifies the track number
    //highByte grabs the top 8 bits and lowByte grabs the bottom 8 bits

    ExecuteCMD(0x0D,0,1); //Plays the currently selected track

    currentTrackPlaying = audio_file_number;
    timeCurrentTrackStartedPlaying = timer.getTimeSinceStartOfStageInMilliseconds();
}

void MP3::PlayBackgroundMusicIfIdle()
{
    unsigned long timeTrackHasBeenPlaying = timer.getTimeSinceStartOfStageInMilliseconds() - timeCurrentTrackStartedPlaying;
    if (currentTrackPlaying == SPOKEN_TRACK_NUM)
    {
        if (timeTrackHasBeenPlaying >= MILLISECONDS_IN_SPOKEN_TRACK)
        {
            Play(BACKGROUND_TRACK_NUM);
        }
    }
    else if (currentTrackPlaying == BACKGROUND_TRACK_NUM)
    {
        if (timeTrackHasBeenPlaying >= MILLISECONDS_IN_BACKGROUND_TRACK)
        {
            Play(BACKGROUND_TRACK_NUM);
        }
    }
    else if (currentTrackPlaying == NO_TRACK)
    {
        Play(BACKGROUND_TRACK_NUM);
    }
}

void MP3::SetVolume(int volume)
{
    ExecuteCMD(0x06, 0, volume); // Set the volume (0x00~0x30)
}

void MP3::AdjustVolumeAsRequested()
{
    int new_volume = potentiometer.ReadPotentiometerAndConvertToOutputValues();
    if(new_volume != current_volume)
    {
        if (abs(new_volume - current_volume) >= 4)
        {
            Serial.print("VolumeChangeTo: ");
            Serial.println(new_volume);
        } 
        SetVolume(new_volume);
        current_volume = new_volume;
    }
}

void MP3::ExecuteCMD(byte CMD, byte Par1, byte Par2)
// Execute the command and parameters
{
    // Calculate the checksum (2 bytes)
    word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
    // Build the command line
    byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
    Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
    //Send the command line to the module
    for (byte k=0; k<10; k++)
    {
        mySerial.write( Command_line[k]);
    }
}