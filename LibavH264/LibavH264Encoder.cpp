#include "LibavH264Encoder.hpp"

namespace H264 {

void LibavH264Encoder::init(const int width, const int height) {
  if (width % 2 != 0 || height % 2 != 0) {
    std::cerr << "[LibavH264Encoder] Failed to initialize LibavH264Encoder, width and height should be a multiple of 2!" << std::endl;
    return;
  }
  int ret;
  width_ = width;
  height_ = height;
  size_ = width * height * 3 / 2;  // YUV size

  avcodec_register_all();

  codec_ = avcodec_find_encoder(AV_CODEC_ID_H264);  // soft encoding
  if (!codec_) {
    std::cerr << "[LibavH264Encoder] Codec not found!" << std::endl;
    return;
  }

  pCodecCtx_ = avcodec_alloc_context3(codec_);
  if (!pCodecCtx_) {
    std::cerr << "[LibavH264Encoder] Could not allocate video codec_ context!" << std::endl;
    return;
  }

  pCodecCtx_->bit_rate = BITRATE;
  pCodecCtx_->width = width;
  pCodecCtx_->height = height;
  pCodecCtx_->time_base = (AVRational){1, FPS};
  pCodecCtx_->framerate = (AVRational){FPS, 1};
  pCodecCtx_->gop_size = GOP;
  pCodecCtx_->max_b_frames = 0;
  pCodecCtx_->pix_fmt = AV_PIX_FMT_YUV420P;
  pCodecCtx_->slices = 1;
  pCodecCtx_->thread_type = FF_THREAD_FRAME;
  pCodecCtx_->thread_count = 6;

  if (codec_->id == AV_CODEC_ID_H264) {
    ret = av_opt_set(pCodecCtx_->priv_data, "tune", "zerolatency", 0);
    if (ret != 0) {
      std::cerr << "[LibavH264Encoder] Could not set av_opt_set()!" << std::endl;
    }
  }

  av_log_set_level(AV_LOG_FATAL);

  ret = avcodec_open2(pCodecCtx_, codec_, NULL);
  if (ret < 0) {
    std::cerr << "[LibavH264Encoder] Could not set open codec_, ret = " << ret << "!" << std::endl;
    return;
  }

  pFrame_ = av_frame_alloc();
  if (!pFrame_) {
    std::cerr << "[LibavH264Encoder] Could not set allocate video frame" << std::endl;
    return;
  }

  pFrame_->format = pCodecCtx_->pix_fmt;
  pFrame_->width = pCodecCtx_->width;
  pFrame_->height = pCodecCtx_->height;

  ret = av_frame_get_buffer(pFrame_, 0);
  if (ret < 0) {
    std::cerr << "[LibavH264Encoder] Could not allocate video frame data" << std::endl;
    return;
  }

  encodedBuffer_ = static_cast<uint8_t *>(malloc(size_ * sizeof(uint8_t)));

  std::cout << "[LibavH264Encoder] Initialized" << std::endl;
}

void LibavH264Encoder::destroy() {
  if (pCodecCtx_ != nullptr)
    avcodec_free_context(&pCodecCtx_);
  if (pFrame_ != nullptr)
    av_frame_free(&pFrame_);
  if (encodedBuffer_ != nullptr)
    free(encodedBuffer_);
  std::cerr << "[LibavH264Encoder] Encoder destroyed" << std::endl;
}

LibavH264Encoder::LibavH264Encoder(const int width, const int height) {
  std::cout << "[LibavH264Encoder] Initializing encoder" << std::endl;
  init(width, height);
}

void LibavH264Encoder::encode(uint8_t *buffer, const int keyFrame) {
  int ret;

  ret = av_frame_make_writable(pFrame_);
  if (ret < 0) {
    std::cerr << "[LibavH264Encoder] Error during av_frame_make_writable(), error: " << ret << "!" << std::endl;
    return;
  }

  memcpy(pFrame_->data[0], buffer, pCodecCtx_->width * pCodecCtx_->height);
  memcpy(pFrame_->data[1], buffer + pCodecCtx_->width * pCodecCtx_->height, pCodecCtx_->width * pCodecCtx_->height / 4);
  memcpy(pFrame_->data[2], buffer + pCodecCtx_->width * pCodecCtx_->height + pCodecCtx_->width * pCodecCtx_->height / 4, pCodecCtx_->width * pCodecCtx_->height / 4);
  pFrame_->pict_type = (AVPictureType)keyFrame;  // make key frame
  ret = avcodec_send_frame(pCodecCtx_, pFrame_);
  if (ret == 0) {
    AVPacket *packet = av_packet_alloc();
    ret = avcodec_receive_packet(pCodecCtx_, packet);
    if (ret == 0) {
      size_ = packet->size;
      memcpy(encodedBuffer_, packet->data, size_);
      encoderFlag_ = true;
    } else if (ret < 0) {
      std::cerr << "[LibavH264Encoder] Error during encoding, error: " << ret << "!" << std::endl;
      encoderFlag_ = 0;
      av_packet_free(&packet);
      return;
    }
    av_packet_free(&packet);
  } else {
    std::cerr << "[LibavH264Encoder] Error sending a frame for encoding with error: " << ret << "!" << std::endl;
    encoderFlag_ = 0;
    return;
  }
  return;
}

LibavH264Encoder::~LibavH264Encoder() {
  std::cout << "[LibavH264Encoder] Destroying encoder..." << std::endl;
  destroy();
}

}  // namespace H264
