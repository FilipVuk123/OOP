#include "LibavH264Decoder.hpp"

namespace H264 {

void LibavH264Decoder::init(const int width, const int height, const int fps) {
  width_ = width;
  height_ = height;
  size_ = width * height * 3 / 2;  // yuv size

  avcodec_register_all();

  pCodec_ = avcodec_find_decoder(AV_CODEC_ID_H264);
  if (pCodec_ == NULL) {
    std::cerr << "[LibavH264Decoder] Error Codec not found." << std::endl;
    return;
  }

  pCodecCtx_ = avcodec_alloc_context3(pCodec_);
  if (!pCodecCtx_) {
    std::cerr << "[LibavH264Decoder] Error Could not allocate video codec context." << std::endl;
    return;
  }

  av_log_set_level(AV_LOG_FATAL);

  pCodecCtx_->bit_rate = BITRATE;
  pCodecCtx_->width = width;
  pCodecCtx_->height = height;
  pCodecCtx_->framerate = (AVRational){fps, 1};

  if (avcodec_open2(pCodecCtx_, pCodec_, NULL) < 0) {
    std::cerr << "[LibavH264Decoder] Error Could not open codec." << std::endl;
    return;
  }

  packet_ = av_packet_alloc();
  if (!packet_) {
    std::cerr << "[LibavH264Decoder] Error Could not alloc packet." << std::endl;
    return;
  }

  decodedBuffer_ = static_cast<uint8_t *>(malloc(size_ * sizeof(uint8_t)));

  std::cout << "[LibavH264Decoder] Decoder initialized!" << std::endl;
  return;
}

void LibavH264Decoder::decode(uint8_t *buffer, const int bufferSize) {
  const int ySize = pCodecCtx_->width * pCodecCtx_->height;

  packet_->data = static_cast<uint8_t *>(buffer);
  packet_->size = bufferSize;

  int ret = avcodec_send_packet(pCodecCtx_, packet_);
  if (ret == 0) {
    AVFrame *pFrame_ = av_frame_alloc();
    ret = avcodec_receive_frame(pCodecCtx_, pFrame_);
    if (ret == 0) {
      memcpy(decodedBuffer_, pFrame_->data[0], ySize);
      memcpy(decodedBuffer_ + ySize, pFrame_->data[1], ySize / 4);
      memcpy(decodedBuffer_ + ySize + ySize / 4, pFrame_->data[2], ySize / 4);
      decoderFlag_ = true;
    } else {
      std::cerr << "[LibavH264Decoder] Error Decoding frame error." << std::endl;

      decoderFlag_ = 0;
      av_frame_free(&pFrame_);
      return;
    }
    av_frame_free(&pFrame_);
  } else {
    std::cerr << "[LibavH264Decoder] Error sending packet to decoder!" << std::endl;

    decoderFlag_ = 0;
    return;
  }
  return;
}

void LibavH264Decoder::destroy() {
  if (pCodecCtx_ != nullptr)
    avcodec_free_context(&pCodecCtx_);
  if (packet_ != nullptr)
    av_packet_free(&packet_);
  if (decodedBuffer_ != nullptr)
    free(decodedBuffer_);
  std::cout << "[LibavH264Decoder] Decoder destroyed" << std::endl;
}

LibavH264Decoder::~LibavH264Decoder() {
  std::cout << "[LibavH264Decoder] Destroying Decoder..." << std::endl;
  destroy();
}

LibavH264Decoder::LibavH264Decoder(const int width, const int height, const int fps) {
  std::cout << "[LibavH264Decoder] Initializing Decoder!" << std::endl;
  init(width, height, fps);
}

}  // namespace H264
