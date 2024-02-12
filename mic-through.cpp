#include "mic-through.h"
#include <arm_math.h>
#include <cstdint>

FxLMSFilter::FxLMSFilter() : AudioStream(1, inputQueueArray) {
    // Inicializa el filtro aquí
    mu = 0.01; // Tasa de convergencia
    for (int i = 0; i < 512; i++) {
        w[i] = 0; // Inicializa los coeficientes del filtro a 0
        x[i] = 0; // Inicializa el buffer de entrada a 0
    }
}

void FxLMSFilter::update() {
    audio_block_t *block = receiveReadOnly();
    if (!block) return;

    // Implementar el algoritmo fxLMS aquí
    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        // Calcula la salida del filtro adaptativo
        float y = 0;
        for (int j = 0; j < 512; j++) {
            y += w[j] * x[(i - j + 512) % 512];
        }

        // Calcula el error entre la señal de entrada y la salida del filtro
        float e = block->data[i] - y;

        // Actualiza los coeficientes del filtro adaptativo
        for (int j = 0; j < 512; j++) {
            w[j] += mu * e * x[(i - j + 512) % 512];
        }

        // Almacena la señal de entrada en el buffer
        x[i] = block->data[i];

        // Almacena la salida del filtro en el bloque de audio
        block->data[i] = y;
    }

    transmit(block);
    release(block);
}
