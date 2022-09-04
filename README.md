# AsyncTracer
## Short description
This library provides simple way of reporting logs (traces) to files and other services without blocking application's execution.

## Features
- Non-blocking logging functionality.
- Asynchronous access to multiple outputs.

The library is capable of writing to multiple destinations at once, but will not write to same destination asynchronously due to data race hazard.

## How to use it?
First a destination stream must be selected using `at::select_tracer(const std::string& destination)` function, then you can proceed by sending any string data with `at::trace(const std::string& message)` function.

## TODOs
- Implement error handling system.
- Implement feature to allow sending and handling of custom data, other than standard strings.
- Improve extendability of the library, so user can create own service implementations.
- Implement worker-wrapper traits to select in which way log data should be handled:
  - async-ordered - logs data in ordered manner without blocking.
  - async-unordered - logs data in unordered manner without blocking. Potentially improves performance.
  - sync - synchronous data logging in ordered manner, but blocks caller's execution.