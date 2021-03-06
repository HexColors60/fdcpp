/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Steffen Nuessle
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _FDCPP_EPOLL_HPP_
#define _FDCPP_EPOLL_HPP_

#include <sys/epoll.h>

#include <fds/base/descriptor.hpp>

namespace fd {

class epoll : public descriptor {
public:
    explicit epoll(int flags = 0);
    explicit epoll(descriptor &&other);
    epoll(epoll &&other) = default;
    
    virtual ~epoll() = default;
    
    epoll &operator=(epoll &&other) = default;
    
    epoll dup() const;
    void dup2(const epoll &other) const;
    
    void ctl(int op, int fd, struct epoll_event *ev = nullptr) const;
    void ctl(int op, int fd, struct epoll_event &ev) const;
    void ctl(int op, int fd, uint32_t event_mask, int data) const;
    void ctl(int op, int fd, uint32_t event_mask, uint32_t data) const;
    void ctl(int op, int fd, uint32_t event_mask, uint64_t data) const;
    void ctl(int op, int fd, uint32_t event_mask, void *data) const;
    
    void add(int fd, uint32_t event_mask, int data) const;
    void add(int fd, uint32_t event_mask, uint32_t data) const;
    void add(int fd, uint32_t event_mask, uint64_t data) const;
    void add(int fd, uint32_t event_mask, void *data) const;
    
    void mod(int fd, uint32_t event_mask, int data) const;
    void mod(int fd, uint32_t event_mask, uint32_t data) const;
    void mod(int fd, uint32_t event_mask, uint64_t data) const;
    void mod(int fd, uint32_t event_mask, void *data) const;
    
    void del(int fd) const;
    
    int wait(struct epoll_event *events, int size, int timeout_ms = -1) const;
    int pwait(struct epoll_event *events, 
              int size, 
              const sigset_t &sigmask, 
              int timeout_ms = -1) const;
    
private:
    epoll(const epoll &other);
    const epoll &operator=(const epoll &other) const;
};

}

#endif /* _FDCPP_EPOLL_HPP_ */