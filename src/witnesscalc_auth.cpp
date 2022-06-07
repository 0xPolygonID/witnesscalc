#include "witnesscalc_auth.h"
#include "witnesscalc.h"
#include "circom.hpp"
#include "auth.cpp"

int
witnesscalc_auth(
    const char *circuit_buffer,  unsigned long  circuit_size,
    const char *json_buffer,     unsigned long  json_size,
    char       *wtns_buffer,     unsigned long *wtns_size,
    char       *error_msg,       unsigned long  error_msg_maxsize)
{
    Auth *code;
    code = new Auth;
    return witnesscalc(code,
                       circuit_buffer, circuit_size,
                       json_buffer,   json_size,
                       wtns_buffer,   wtns_size,
                       error_msg,     error_msg_maxsize);
}
