# blackbox: Setec Astronomy

# EXAMPLE

```console
$ time blackbox 18446744073709551577
139646831
blackbox 18446744073709551577  26.68s user 0.04s system 99% cpu 26.738 total
```

# ABOUT

blackbox factors semiprimes.

## Caveats

blackbox is intended for non-trivial semiprimes. For performance reasons, certain trivial cases (n < 4, even n, square n, prime n) may produce strange results.

Expect processing time to grow exponentially with the size of the semiprime.

# REQUIREMENTS

(N/A)

## Recommended

* [time](https://linux.die.net/man/1/time)

# CONTRIBUTING

For more information on developing blackbox itself, see [DEVELOPMENT.md](DEVELOPMENT.md).
