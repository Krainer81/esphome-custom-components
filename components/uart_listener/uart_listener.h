#include "esphome.h"

class UARTListenerComponent : public Component, public UARTDevice {
 public:
  UARTListenerComponent(UARTComponent *parent, TextSensor *text_sensor)
      : UARTDevice(parent), text_sensor_(text_sensor) {}

  void loop() override {
    while (available()) {
      char c = read();
      if (c == '\n' || c == '\r') {
        if (!buffer_.empty()) {
          text_sensor_->publish_state(buffer_);
          buffer_.clear();
        }
      } else {
        buffer_ += c;
      }
    }
  }

 protected:
  TextSensor *text_sensor_;
  std::string buffer_;
};
