// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "precomp.h"
#include "Handle.h"

#include "Implementation.h"

using namespace Microsoft::Console::TSF;

Handle Handle::Create()
{
    Handle handle;
    handle._impl = new Implementation();
    handle._impl->Initialize();
    return handle;
}

Handle::~Handle()
{
    if (_impl)
    {
        _impl->Uninitialize();
        _impl->Release();
    }
}

Handle::Handle(Handle&& other) noexcept :
    _impl{ other._impl }
{
    other._impl = nullptr;
}

Handle& Handle::operator=(Handle&& other) noexcept
{
    if (this != &other)
    {
        this->~Handle();
        _impl = other._impl;
        other._impl = nullptr;
    }
    return *this;
}

Handle::operator bool() const noexcept
{
    return _impl != nullptr;
}

HWND Handle::FindWindowOfActiveTSF() const
{
    return _impl ? _impl->FindWindowOfActiveTSF() : nullptr;
}

void Handle::AssociateFocus(IDataProvider* provider) const
{
    if (_impl)
    {
        _impl->AssociateFocus(provider);
    }
}

void Handle::Focus(IDataProvider* provider) const
{
    if (_impl)
    {
        _impl->Focus(provider);
    }
}

void Handle::Unfocus(IDataProvider* provider) const
{
    if (_impl)
    {
        _impl->Unfocus(provider);
    }
}

bool Handle::HasActivateComposition() const noexcept
{
    return _impl ? _impl->HasActivateComposition() : false;
}
