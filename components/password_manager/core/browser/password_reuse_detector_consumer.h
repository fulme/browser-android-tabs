// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_REUSE_DETECTOR_CONSUMER_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_REUSE_DETECTOR_CONSUMER_H_

#include <string>
#include <vector>

#include "base/macros.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"

namespace password_manager {

// Callback interface for receiving a password reuse event.
class PasswordReuseDetectorConsumer
    : public base::SupportsWeakPtr<PasswordReuseDetectorConsumer> {
 public:
  PasswordReuseDetectorConsumer();
  virtual ~PasswordReuseDetectorConsumer();

  // Called when a password reuse is found.
  // |password_length| is the length of the re-used password, or the max length
  // if multiple passwords were matched. |matching_domains| is the list of
  // domains for which |password| is saved (may be empty if
  // |matches_sync_password| == true),  |saved_passwords| is the total number
  // of passwords (with unique domains) stored in Password Manager.
  virtual void OnReuseFound(size_t password_length,
                            bool matches_sync_password,
                            const std::vector<std::string>& matching_domains,
                            int saved_passwords) = 0;
};

}  // namespace password_manager
#endif  // COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_REUSE_DETECTOR_CONSUMER_H_
