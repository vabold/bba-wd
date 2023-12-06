#pragma once

#include <Common.h>

extern "C" {
typedef struct {
} OSThread;

OSThread *OSGetCurrentThread();
}
