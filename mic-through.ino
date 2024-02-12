#include <Audio.h>
#include "mic-through.h"

AudioInputI2S in; // Entrada de audio (micrófono)
AudioOutputI2S out; // Salida de audio (altavoz)
AudioControlSGTL5000 audioShield;

FxLMSFilter fxLMSFilter;
AudioConnection patchCord1(in, fxLMSFilter);
AudioConnection patchCord2(fxLMSFilter, out);

void setup() {
  Serial.begin(9600);
  AudioMemory(12);
  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  audioShield.micGain(10); // in dB
  audioShield.volume(1);
}

void loop() {
  // No hay nada que hacer en el bucle principal
}
