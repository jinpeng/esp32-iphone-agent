// Mirrored H.264 from AirPlay to BLE: keeps the current GOP in PSRAM and sends it on `snap`,
// or every access unit while `stream on`. Also runs `bench` and computes the video stats.
#pragma once
#include <Arduino.h>

bool video_begin();
void video_on_config(const uint8_t *sps_pps, size_t len);  // AirPlay callbacks (mirror task)
void video_on_au(const uint8_t *au, size_t len, bool idr);
void video_stream(bool on);
void video_snap(const String &id);               // replies "<id> ok" when the GOP is sent
void video_bench(const String &id, uint32_t kb);  // replies "<id> ok <ms>"

struct VideoStats {
  uint32_t kbps, idr_ms, gop_bytes;
  uint32_t overflows;  // times a cap was hit; the buffer then freezes until the next IDR
  bool wait_idr;       // no IDR yet (nothing decodable)
  bool frozen;         // serving a stale window until an IDR restarts the buffer
  float fps;
};
VideoStats video_stats();
