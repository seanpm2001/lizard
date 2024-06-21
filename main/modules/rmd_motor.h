#pragma once

#include "can.h"
#include "module.h"
#include <memory>

class RmdMotor;
using RmdMotor_ptr = std::shared_ptr<RmdMotor>;
using ConstRmdMotor_ptr = std::shared_ptr<const RmdMotor>;

class RmdMotor : public Module, public std::enable_shared_from_this<RmdMotor> {
private:
    const uint32_t motor_id;
    const Can_ptr can;
    uint8_t last_msg_id = 0;
    int ratio;
    const double encoder_range;
    int32_t last_encoder_position;
    bool has_last_encoder_position = false;
    unsigned long int last_msg_millis = 0;
    bool is_part_of_pair = false;
    uint32_t can_age_limit;

    void send(const uint8_t d0, const uint8_t d1, const uint8_t d2, const uint8_t d3,
              const uint8_t d4, const uint8_t d5, const uint8_t d6, const uint8_t d7,
              const unsigned long int timeout_ms = 3);

public:
    RmdMotor(const std::string name, const Can_ptr can, const uint8_t motor_id, const int ratio);
    void subscribe_to_can();
    void step() override;
    void call(const std::string method_name, const std::vector<ConstExpression_ptr> arguments) override;
    void handle_can_msg(const uint32_t id, const int count, const uint8_t *const data) override;

    void power(double target_power);
    void speed(double target_speed);
    void position(double target_position, double target_speed = 0.0);
    void stop();
    void off();
    void hold();
    void clear_errors();
    void set_is_part_of_pair(bool is_part_of_pair);
    bool get_is_part_of_pair() const;
    void set_can_age_limit(const uint32_t age_limit);

    double get_position() const;
    double get_speed() const;
    void set_acceleration(const uint8_t index, const uint32_t acceleration);
};