
#pragma once
#include <stdexcept>
#include "CommonInc.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h> // For HRESULT


inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        throw std::exception();
    }
}