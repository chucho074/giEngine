#pragma once
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x=nullptr;