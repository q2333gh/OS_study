// TODO.  simulate C++ callback.
// simulate Rust clousure or JS clousere.
// Is clousure and callback actually a kind of Functional Programming?

#include <stdio.h>

typedef struct {
  // Define the struct for WalletState
  // ...
} WalletState;

WalletState STATE = {0};  // Define the variable STATE

// Function to retrieve the wallet state
void with_wallet(void (*callback)(const WalletState*)) { callback(&STATE); }

// Callback function
void print_wallet_state(const WalletState* state) {
  // Print or manipulate the wallet state
  // ...
}

int main() {
  with_wallet(print_wallet_state);

  return 0;
}