#pragma once

#include <giPrerequisitesUtilities.h>

#include <giMath.h>

#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x=nullptr;