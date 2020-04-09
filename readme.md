Vista
=====

Vista is a header-only C++11 library that contains various span classes.

The span classes acts like fixed-capacity in-place containers operating on contiguous memory provided by the user.

The span classes do not take ownership of the user-provided memory. User must ensure the life-time of the memory until the span has been destroyed.

* vista::span is an extension of std::span.
* vista::circular::span is a circular buffer.
* vista::map::span is an associative array.
