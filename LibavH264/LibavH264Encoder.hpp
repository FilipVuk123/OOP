#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
}

namespace H264 {

class LibavH264Encoder {
 public:
  bool encoderFlag_{false};
  uint8_t *encodedBuffer_{nullptr};

  LibavH264Encoder(const int width, const int height);
  ~LibavH264Encoder();

  /**
   * This function encodes a given buffer into H264 format using the Libav library.
   *
   * @param buffer A pointer to the input buffer containing the raw video frame data to be encoded.
   * @param keyFrame The keyFrame parameter is an integer value that determines whether the current
   * frame being encoded is a key frame or not. A key frame is a frame that is fully encoded and can be
   * used as a reference for other frames in the video stream. If keyFrame is set to 1, then the current
   *
   * @return nothing (void).
   */
  void encode(uint8_t *buffer, const int keyFrame);

 private:
  /**
   * This function initializes a Libav H.264 encoder with specified width and height.
   *
   * @param width The width of the video frame in pixels.
   * @param height The height parameter is the height of the video frame in pixels.
   *
   * @return nothing (void).
   */
  void init(const int width, const int height);

  /**
   * This function frees allocated memory and prints a message indicating the destruction of an encoder
   * object.
   */
  void destroy();

  int size_{};
  int width_{};
  int height_{};
  AVCodec *codec_{};
  AVCodecContext *pCodecCtx_{};
  AVFrame *pFrame_{};
  static const int BITRATE{650000};
  static const int GOP{30};
  static const int FPS{60};
};

}  // namespace H264