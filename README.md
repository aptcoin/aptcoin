Aptcoin integration/staging tree
================================

http://www.aptcoin.org

Copyright (c) 2009-2014 Bitcoin Developers
Copyright (c) 2014-2014 Aptcoin Developers

What is Aptcoin?
----------------

Aptcoin is an advanced version of Bitcoin using a modified scrypt
algorithm known as Scrypt-iN-Motion, or Scrypt-NM as a proof-of-work
algorithm.
 - 5 minute block targets
 - subsidy halves in 420k blocks (~4 years)
 - ~42 million total coins
 - 20 blocks to retarget difficulty

Main Network Port: 12945, RPC Port 12946
Testnet Network Port: 22945, RPC Port 22946

For more information, as well as an immediately useable, binary version of
the Aptcoin client sofware, see http://www.aptcoin.org.

License
-------

Aptcoin is released under the terms of the MIT license. See `COPYING` for more
information or see http://opensource.org/licenses/MIT.

Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the Aptcoin
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then the patch
submitter will be asked to start a discussion (if they haven't already) on the
[mailing list](http://sourceforge.net/mailarchive/forum.php?forum_name=bitcoin-development).

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see `doc/coding.txt`) or are
controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/aptcoin/aptcoin/tags) are created
regularly to indicate new official, stable release versions of Aptcoin.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test. Please be patient and help out, and
remember this is a security-critical project where any mistake might cost people
lots of money.
