#pragma once
#include <amethyst/Memory.hpp>

void InitializeCtorImpl(void*& ctorPtr, std::string signature, std::string ctorName);
void InitializeVtblImpl(void*& vtablePtr, std::string signature, std::string vtableName);

#define InitializeCtor(ctorPtr, signature) \
    InitializeCtorImpl(ctorPtr, signature, #ctorPtr)

#define InitializeVtbl(vtablePtr, signature) \
    InitializeVtblImpl(vtablePtr, signature, #vtablePtr)

void InitializeVtablePtrs();