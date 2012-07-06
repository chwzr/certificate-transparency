#include <openssl/sha.h>
#include <stddef.h>

#include "../include/ct.h"
#include "SerialHasher.h"

const size_t Sha256Hasher::kDigestSize = SHA256_DIGEST_LENGTH;

Sha256Hasher::Sha256Hasher() : initialized_(false) {}

void Sha256Hasher::Reset() {
  SHA256_Init(&ctx_);
  initialized_ = true;
}

void Sha256Hasher::Update(const bstring &data) {
  if (!initialized_)
    Reset();

  SHA256_Update(&ctx_, data.data(), data.size());
}

bstring Sha256Hasher::Final() {
  if (!initialized_)
    Reset();

  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_Final(hash, &ctx_);
  return bstring(hash, SHA256_DIGEST_LENGTH);
  initialized_ = false;
}