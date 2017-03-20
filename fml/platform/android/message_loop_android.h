// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_FML_PLATFORM_ANDROID_MESSAGE_LOOP_ANDROID_H_
#define FLUTTER_FML_PLATFORM_ANDROID_MESSAGE_LOOP_ANDROID_H_

#include <android/looper.h>

#include <atomic>

#include "flutter/fml/message_loop_impl.h"
#include "lib/ftl/files/unique_fd.h"
#include "lib/ftl/macros.h"
#include "lib/ftl/memory/unique_object.h"

namespace fml {

struct UniqueLooperTraits {
  static ALooper* InvalidValue() { return nullptr; }
  static bool IsValid(ALooper* value) { return value != nullptr; }
  static void Free(ALooper* value) { ::ALooper_release(value); }
};

class MessageLoopAndroid : public MessageLoopImpl {
 private:
  ftl::UniqueObject<ALooper*, UniqueLooperTraits> looper_;
  ftl::UniqueFD timer_fd_;
  bool running_;

  MessageLoopAndroid();

  ~MessageLoopAndroid() override;

  void Run() override;

  void Terminate() override;

  void WakeUp(ftl::TimePoint time_point) override;

  void OnEventFired();

  FRIEND_MAKE_REF_COUNTED(MessageLoopAndroid);
  FRIEND_REF_COUNTED_THREAD_SAFE(MessageLoopAndroid);
  FTL_DISALLOW_COPY_AND_ASSIGN(MessageLoopAndroid);
};

}  // namespace fml

#endif  // FLUTTER_FML_PLATFORM_ANDROID_MESSAGE_LOOP_ANDROID_H_
