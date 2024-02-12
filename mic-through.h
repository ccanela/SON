#ifndef FXLMS_FILTER_H
#define FXLMS_FILTER_H

#include <Audio.h>

class FxLMSFilter : public AudioStream {
public:
    FxLMSFilter();
    virtual void update();
private:
    audio_block_t *inputQueueArray[1];
    float mu; // Tasa de aprendizaje
    float w[512]; // Coeficientes del filtro adaptativo
    float x[512]; // Buffer para la señal de entrada
};

#endif
