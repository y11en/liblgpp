#ifndef LGPP_OPS_RESUME_HPP
#define LGPP_OPS_RESUME_HPP

#include "../op.hpp"
#include "../val.hpp"
#include "../vm.hpp"

namespace lgpp::ops {

  struct Resume {};

  template <>
  inline const Op* eval(const Op& op, const Resume& imp, lgpp::Thread& thread, lgpp::Stack& stack) {
    auto c = pop(stack, lgpp::types::Coro);
    if (c.done) { throw runtime_error("Coro is done"); }
    thread.push_coro(c);
    thread.push_ret(op.pc+1, lgpp::Ret::Opts::CORO);
    return &op - op.pc + c.pc;
  }

}

#endif
