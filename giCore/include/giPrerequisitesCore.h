#pragma once

#include <giPrerequisitesUtilities.h>

#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x=nullptr;