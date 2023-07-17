#pragma once

#include <stdio.h>

#include <iostream>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
}

namespace H264 {

class LibavH264Decoder {
 public:
  bool decoderFlag_{false};
  uint8_t *decodedBuffer_{nullptr};

  LibavH264Decoder(const int width, const int height, const int fps);
  ~LibavH264Decoder();

  /**
   * The function decodes a H264 video frame using the libavcodec library and stores the decoded data in
   * a buffer.
   *
   * @param buffer A pointer to the buffer containing the encoded H.264 video data.
   * @param buffer_size The size of the input buffer containing the encoded H.264 video data.
   *
   * @return nothing (void).
   */
  void decode(uint8_t *buffer, const int buffer_size);

 private:
  /**
   * This function initializes a Libav H264 decoder with specified width, height, and fps.
   *
   * @param width The width of the video frame in pixels.
   * @param height The height of the video frame in pixels.
   * @param fps fps stands for frames per second.
   *
   */
  void init(const int width, const int height, const int fps);

  /**
   * This function frees allocated memory and prints a message indicating the destruction of a decoder
   * object.
   */
  void destroy();
  
  int size_{};
  int width_{};
  int height_{};
  AVCodecContext *pCodecCtx_{};
  AVCodec *pCodec_{};
  AVPacket *packet_{};
  static const int BITRATE{10000};
};

}  // namespace H264
