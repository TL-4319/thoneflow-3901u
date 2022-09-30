/*
* Tuan Luong
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#ifndef THONEFLOW_3901U_SRC_THONEFLOW_3901U_H_  // NOLINT
#define THONEFLOW_3901U_SRC_THONEFLOW_3901U_H_

#if defined(ARDUINO)
#include "Arduino.h"
#else
#include "core/core.h"
#endif

namespace bfs {

class Thoneflow3910 {
 public:
  Thoneflow3910() {}
  explicit Thoneflow3910(HardwareSerial *bus) : bus_(bus) {}
  void Config(HardwareSerial *bus) {bus_ = bus;}
  bool Begin();
  bool Read();
  inline float x_mot() const {return x_mot_;}
  inline float y_mot() const {return y_mot_;}
  inline uint8_t sur_qual() const {return sur_qual_;}

 private:
  /* Communication */
  static constexpr int16_t COMM_TIMEOUT_MS_ = 5000;
  static constexpr int32_t BAUD_ = 19200;
  HardwareSerial *bus_;
  elapsedMillis t_ms_;
  /* Data */
  uint8_t sur_qual_;
  int16_t x_mot_;
  int16_t y_mot_;
  /* Parser */
  static constexpr uint8_t HEADER_ = 0xFE;
  static constexpr uint8_t NUM_ = 0x04;
  static constexpr uint8_t HEADER_POS_ = 0;
  static constexpr uint8_t NUM_POS_ = 1;
  static constexpr uint8_t X_MOT_LSB_POS_ = 2;
  static constexpr uint8_t X_MOT_MSB_POS_ = 3;
  static constexpr uint8_t Y_MOT_LSB_POS_ = 4;
  static constexpr uint8_t Y_MOT_MSB_POS_ = 5;
  static constexpr uint8_t SUR_QUAL_POS_ = 7;
  static constexpr uint8_t CHK_POS_ = 6;
  uint8_t c_;
  uint8_t state_ = 0;
  uint8_t x_mot_lsb_, x_mot_msb_, y_mot_lsb_, y_mot_msb_, sur_qual_, chk_;
  uint8_t buf_[9];
};

}  // namespace bfs

#endif  // THONEFLOW_3910U_SRC_THONEFLOW_3901U_H_ NOLINT

