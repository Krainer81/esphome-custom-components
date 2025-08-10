#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/text_sensor/text_sensor.h"

namespace esphome {
namespace uart_listener {

class UARTListenerComponent : public Component, public uart::UARTDevice {
 public:
  void set_text_sensor(text_sensor::TextSensor *sensor) { this->sensor_ = sensor; }

  void loop() override {
    while (this->available()) {
      char c;
      this->read_byte(&c);
      if (c == '\n') {
        if (this->sensor_ != nullptr) {
          this->sensor_->publish_state(this->buffer_);
        }
        this->buffer_.clear();
      } else {
        this->buffer_ += c;
      }
    }
  }

 protected:
  text_sensor::TextSensor *sensor_{nullptr};
  std::string buffer_;
};

}  // namespace uart_listener
}  // namespace esphome
