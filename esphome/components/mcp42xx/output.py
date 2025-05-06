import esphome.codegen as cg
from esphome.components import output
import esphome.config_validation as cv
from esphome.const import CONF_CHANNEL, CONF_ID

from . import MCP42XXComponent, mcp42xx_ns

DEPENDENCIES = ["mcp42xx"]

MCP42XXChannel = mcp42xx_ns.class_("MCP42XXChannel", output.FloatOutput)
CONF_MCP42XX_ID = "mcp42xx_id"

MCP42XXChannelIdx = mcp42xx_ns.enum("MCP42XXChannelIdx")
CHANNEL_OPTIONS = {
    "A": MCP42XXChannelIdx.MCP42XX_CHANNEL_A,
    "B": MCP42XXChannelIdx.MCP42XX_CHANNEL_B,
}

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend(
    {
        cv.Required(CONF_ID): cv.declare_id(MCP42XXChannel),
        cv.GenerateID(CONF_MCP42XX_ID): cv.use_id(MCP42XXComponent),
        cv.Required(CONF_CHANNEL): cv.enum(CHANNEL_OPTIONS, upper=True),
    }
)


async def to_code(config):
    paren = await cg.get_variable(config[CONF_MCP42XX_ID])
    var = cg.new_Pvariable(
        config[CONF_ID],
        paren,
        config[CONF_CHANNEL],
    )
    await output.register_output(var, config)
