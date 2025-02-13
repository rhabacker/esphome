#include "raw_protocol.h"
#include "esphome/core/log.h"

namespace esphome {
namespace remote_base {

static const char *const TAG = "remote.raw";

bool RawDumper::dump(RemoteReceiveData src) {
  char buffer[256];
  uint32_t buffer_offset = 0;
  buffer_offset += sprintf(buffer, "Received Raw: ");

  for (int32_t i = 0; i < src.size() - 1; i++) {
    const int32_t value = src[i];
    const uint32_t remaining_length = sizeof(buffer) - buffer_offset;
    int written;

    if (i + 1 < src.size() - 1) {
      written = snprintf(buffer + buffer_offset, remaining_length, "%" PRId32 ", ", value);
    } else {
      written = snprintf(buffer + buffer_offset, remaining_length, "%" PRId32, value);
    }

    if (written < 0 || written >= int(remaining_length)) {
      // write failed, flush...
      buffer[buffer_offset] = '\0';
      ESP_LOGI(TAG, "%s", buffer);
      buffer_offset = 0;
      written = sprintf(buffer, "  ");
      if (i + 1 < src.size() - 1) {
        written += sprintf(buffer + written, "%" PRId32 ", ", value);
      } else {
        written += sprintf(buffer + written, "%" PRId32, value);
      }
    }

    buffer_offset += written;
  }
  if (buffer_offset != 0) {
    ESP_LOGI(TAG, "%s", buffer);
  }
  return true;
}

}  // namespace remote_base
}  // namespace esphome
