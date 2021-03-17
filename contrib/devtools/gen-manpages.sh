#!/bin/bash

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

BIXBCOIND=${BIXBCOIND:-$SRCDIR/bixbcoind}
BIXBCOINCLI=${BIXBCOINCLI:-$SRCDIR/bixbcoin-cli}
BIXBCOINTX=${BIXBCOINTX:-$SRCDIR/bixbcoin-tx}
BIXBCOINQT=${BIXBCOINQT:-$SRCDIR/qt/bixbcoin-qt}

[ ! -x $BIXBCOIND ] && echo "$BIXBCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
BXBVER=($($BIXBCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for bitcoind if --version-string is not set,
# but has different outcomes for bitcoin-qt and bitcoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$BIXBCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $BIXBCOIND $BIXBCOINCLI $BIXBCOINTX $BIXBCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BXBVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BXBVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m