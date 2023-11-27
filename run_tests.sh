#!/usr/bin/env bash

set -e
set -x

package/bin/authV2 \
  testdata/authV2_input.json \
  temp/authV2_witness.wtns
snarkjs groth16 prove \
  circuits/authV2/circuit_final.zkey \
  temp/authV2_witness.wtns \
  temp/authV2_proof.json \
  temp/authV2_public.json
snarkjs groth16 verify \
  circuits/authV2/verification_key.json \
  temp/authV2_public.json \
  temp/authV2_proof.json

package/bin/credentialAtomicQuerySigV2 \
  testdata/credentialAtomicQuerySigV2_input.json \
  temp/credentialAtomicQuerySigV2_witness.wtns
snarkjs groth16 prove \
  circuits/credentialAtomicQuerySigV2/circuit_final.zkey \
  temp/credentialAtomicQuerySigV2_witness.wtns \
  temp/credentialAtomicQuerySigV2_proof.json \
  temp/credentialAtomicQuerySigV2_public.json
snarkjs groth16 verify \
  circuits/credentialAtomicQuerySigV2/verification_key.json \
  temp/credentialAtomicQuerySigV2_public.json \
  temp/credentialAtomicQuerySigV2_proof.json

package/bin/credentialAtomicQuerySigV2OnChain \
  testdata/credentialAtomicQuerySigV2OnChain_input.json \
  temp/credentialAtomicQuerySigV2OnChain_witness.wtns
snarkjs groth16 prove \
  circuits/credentialAtomicQuerySigV2OnChain/circuit_final.zkey \
  temp/credentialAtomicQuerySigV2OnChain_witness.wtns \
  temp/credentialAtomicQuerySigV2OnChain_proof.json \
  temp/credentialAtomicQuerySigV2OnChain_public.json
snarkjs groth16 verify \
  circuits/credentialAtomicQuerySigV2OnChain/verification_key.json \
  temp/credentialAtomicQuerySigV2OnChain_public.json \
  temp/credentialAtomicQuerySigV2OnChain_proof.json

package/bin/credentialAtomicQueryMTPV2 \
  testdata/credentialAtomicQueryMTPV2_input.json \
  temp/credentialAtomicQueryMTPV2_witness.wtns
snarkjs groth16 prove \
  circuits/credentialAtomicQueryMTPV2/circuit_final.zkey \
  temp/credentialAtomicQueryMTPV2_witness.wtns \
  temp/credentialAtomicQueryMTPV2_proof.json \
  temp/credentialAtomicQueryMTPV2_public.json
snarkjs groth16 verify \
  circuits/credentialAtomicQueryMTPV2/verification_key.json \
  temp/credentialAtomicQueryMTPV2_public.json \
  temp/credentialAtomicQueryMTPV2_proof.json

package/bin/credentialAtomicQueryMTPV2OnChain \
  testdata/credentialAtomicQueryMTPV2OnChain_input.json \
  temp/credentialAtomicQueryMTPV2OnChain_witness.wtns
snarkjs groth16 prove \
  circuits/credentialAtomicQueryMTPV2OnChain/circuit_final.zkey \
  temp/credentialAtomicQueryMTPV2OnChain_witness.wtns \
  temp/credentialAtomicQueryMTPV2OnChain_proof.json \
  temp/credentialAtomicQueryMTPV2OnChain_public.json
snarkjs groth16 verify \
  circuits/credentialAtomicQueryMTPV2OnChain/verification_key.json \
  temp/credentialAtomicQueryMTPV2OnChain_public.json \
  temp/credentialAtomicQueryMTPV2OnChain_proof.json
