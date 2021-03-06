cpmf: Collection of Parallel Matrix Factorization
====

This Library is still under construction ...

# Prerequisite

## must

*cpmf* needs picojson as a JSON parser.

```
$ git clone https://github.com/kazuho/picojson.git vendor/picojson
```

## optional

If you want to use MassiveThreads as a task parallel library,
install it by the following command.

```sh
$ git clone https://github.com/massivethreads/massivethreads.git vendor/massivethreads
$ cd vendor/massivethreads
$ ./configure --prefix=/usr/local
$ make && make install
```

When you change PREFIX from `/usr/local`, be sure to also change `MYTH_PATH` in Makefile.

# How to parallelize

Users can designate the parallel method by `PARALLEL_FLAGS` in Makefile.

* **FPSGD**

  FPSGD is our prior research by researchers at National Taiwan University.
  In this method, the rating matrix is divided into many blocks
  and multiple threads work on blocks not to share the same row or column.
  Our *cpmf* was developed to overcome the scalability problem of FPSGD.

  If you want to use *fpsgd* method,
  specify `DPARALLEL = -DFPSGD`.

    + Reference

        Y.Zhuang, W-S.Chin and Y-C.Juan and C-J.Lin},
        "A fast parallel SGD for matrix factorization in shared memory systems",
        RecSys'13, [[paper](http://dl.acm.org/citation.cfm?id=2507164)]

* **task parallel based** (by *Intel Cilk* or *MassiveThreads*)

  This method is our proposing way to parallelize matrix factorization
  by recursively dividing the rating matrix into 4 smaller blocks
  and dynamically assigning the created tasks (blocks) to threads.

  If you want to use *task parallel based* method,
  specify `DPARALLEL = -DTP_BASED`.

  To decide which task parallel library to use, you should set as follows:
  `DTP = -DTP_CILK` for *Intel Cilk*
  or
  `DTP = -DTP_MYTH` for *MassiveThreads*.


# How to use

Just make and run!

```
$ make
$ ./mf train config.json
```
