// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "u2f_ble_frames.h"
#include "u2f_command_type.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* raw_data, size_t size) {
  std::vector<uint8_t> data(raw_data, raw_data + size);

  {
    device::U2fBleFrameInitializationFragment fragment(
        device::U2fCommandType::CMD_MSG, 21123, raw_data, size);
    std::vector<uint8_t> buffer;
    fragment.Serialize(&buffer);

    device::U2fBleFrameInitializationFragment parsed_fragment;
    device::U2fBleFrameInitializationFragment::Parse(data, &parsed_fragment);
    device::U2fBleFrameInitializationFragment::Parse(buffer, &parsed_fragment);

    buffer.clear();
    parsed_fragment.Serialize(&buffer);
  }

  {
    device::U2fBleFrameContinuationFragment fragment(raw_data, size, 61);
    std::vector<uint8_t> buffer;
    fragment.Serialize(&buffer);

    device::U2fBleFrameContinuationFragment parsed_fragment;
    device::U2fBleFrameContinuationFragment::Parse(data, &parsed_fragment);
    device::U2fBleFrameContinuationFragment::Parse(buffer, &parsed_fragment);

    buffer.clear();
    parsed_fragment.Serialize(&buffer);
  }

  {
    device::U2fBleFrame frame(device::U2fCommandType::CMD_PING, data);
    auto fragments = frame.ToFragments(20);

    device::U2fBleFrameAssembler assembler(fragments.first);
    for (const auto& fragment : fragments.second) {
      assembler.AddFragment(fragment);
    }

    auto result_frame = std::move(*assembler.GetFrame());
    result_frame.command();
  }

  return 0;
}
