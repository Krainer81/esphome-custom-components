import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, text_sensor
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]
CODEOWNERS = [""]

uart_listener_ns = cg.esphome_ns.namespace("uart_listener")
UARTListenerComponent = uart_listener_ns.class_(
    "UARTListenerComponent",
    cg.Component,
    uart.UARTDevice
)

CONF_TEXT_SENSOR_ID = "text_sensor_id"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(UARTListenerComponent),
    cv.Required(uart.CONF_UART_ID): cv.use_id(uart.UARTComponent),
    cv.Required(CONF_TEXT_SENSOR_ID): cv.use_id(text_sensor.TextSensor),
}).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    parent = await cg.get_variable(config[uart.CONF_UART_ID])
    var = cg.new_Pvariable(config[CONF_ID])
    var.set_uart_parent(parent)
    await cg.register_component(var, config)

    ts = await cg.get_variable(config[CONF_TEXT_SENSOR_ID])
    cg.add(var.set_text_sensor(ts))
