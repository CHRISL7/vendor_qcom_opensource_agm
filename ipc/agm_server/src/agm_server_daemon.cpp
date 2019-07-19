/*
** Copyright (c) 2019, The Linux Foundation. All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above
**     copyright notice, this list of conditions and the following
**     disclaimer in the documentation and/or other materials provided
**     with the distribution.
**   * Neither the name of The Linux Foundation nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
** WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
** ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
** BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
** BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
** OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
** IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#define LOG_TAG "agm_server_daemon"

#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include "ipc_interface.h"
#include "agm_server_wrapper.h"
#include <signal.h>

static class AgmService *agmServiceInstance = new AgmService();

static void sigint_handler(int sig)
{
    ALOGE("AgmService received signal\n");
    agmServiceInstance->~AgmService();
    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler);
    ALOGE("AgmService initialized \n");
    android::defaultServiceManager()->addService(android::String16("AgmService"), agmServiceInstance);
    android::ProcessState::self()->startThreadPool();
    ALOGE("AGM service is now ready\n");
    android::IPCThreadState::self()->joinThreadPool();
    ALOGE("AGM service thread joined\n");
    return 0;
}
