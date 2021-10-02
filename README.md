# blackbox: Setec Astronomy

# SUMMARY

blackbox is a semiprime factoring machine.

# EXAMPLE

```console
$ time blackbox 18446744073709561
36473819
blackbox 18446744073709561  22.78s user 0.07s system 99% cpu 22.856 total
```

# ABOUT

Preconditions:

* n > 3
* odd(n)

When n is prime, blackbox reports `0`.

Otherwise, blackbox reports a prime factor.

Expect processing time to grow exponentially with the size of the semiprime.

# REQUIREMENTS

(N/A)

## Recommended

* [time](https://linux.die.net/man/1/time)

# CONTRIBUTING

For more information on developing blackbox itself, see [DEVELOPMENT.md](DEVELOPMENT.md).
