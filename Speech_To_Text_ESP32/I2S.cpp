#include "I2S.h"
#include <driver/i2s.h>

#define SAMPLE_RATE (16000)
#define I2S_SAMPLE_BITS   (16)
#define PIN_I2S_BCLK 11
#define PIN_I2S_LRC 10
#define PIN_I2S_DIN 4

I2S::I2S(MicType micType) {
  BITS_PER_SAMPLE = I2S_BITS_PER_SAMPLE_32BIT;
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = i2s_bits_per_sample_t(I2S_SAMPLE_BITS),
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = 0,
    .dma_buf_count = 64,
    .dma_buf_len = 1024,
    .use_apll = 1
  };
  i2s_pin_config_t pin_config;
  pin_config.bck_io_num = PIN_I2S_BCLK;
  pin_config.ws_io_num = PIN_I2S_LRC;
  pin_config.data_out_num = I2S_PIN_NO_CHANGE;
  pin_config.data_in_num = PIN_I2S_DIN;
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
  // i2s_set_clk(I2S_NUM_0, SAMPLE_RATE, BITS_PER_SAMPLE, I2S_CHANNEL_STEREO);
}

int I2S::Read(char* data, int numData) {
  size_t bytes_read;
  return i2s_read(I2S_NUM_0, (char *)data, numData, &bytes_read, portMAX_DELAY);
}

int I2S::GetBitPerSample() {
  return (int)BITS_PER_SAMPLE;
}
