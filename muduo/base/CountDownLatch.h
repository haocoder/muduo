// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_COUNTDOWNLATCH_H
#define MUDUO_BASE_COUNTDOWNLATCH_H

#include "muduo/base/Condition.h"
#include "muduo/base/Mutex.h"

namespace muduo
{
/* countDownLatch这个类使一个线程等待其他线程各自执行完毕后再执行。
 * 是通过一个计数器来实现的，计数器的初始值是线程的数量。每当一个线
 * 程执行完毕后，计数器的值就-1，当计数器的值为0时，表示所有线程都
 * 执行完毕，然后在闭锁上等待的线程就可以恢复工作了。
 * 例如它的两个主要用途：
 * 1. 主线程发起多个子线程，等待这些子线程各自完成一定的任务后，
 * 主线程才继续执行。通常用于主线程等待多个子线程完成初始化。
 * 2. 主线程发起多个子线程，子线程都等待主线程，主线程完成其他一
 * 些任务之后，通知所有子线程开始执行。通常用于多个子线程等待主线程
 * 发出“起跑”的命令。
 * */
class CountDownLatch : noncopyable
{
 public:

  explicit CountDownLatch(int count);

  void wait();

  void countDown();

  int getCount() const;

 private:
  // 先mutex_后condition_的顺序
  mutable MutexLock mutex_;
  Condition condition_ GUARDED_BY(mutex_);
  int count_ GUARDED_BY(mutex_);        // 共享资源
};

}  // namespace muduo
#endif  // MUDUO_BASE_COUNTDOWNLATCH_H
