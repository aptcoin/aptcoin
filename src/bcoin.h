#ifndef __BCOIN_H__
#define __BCOIN_H__

#define B_NORM_DIFF 0
#define B_STEP_DIFF 5

#define BD(x) ((float)(x - 8))
#define BX(x) ((float)(0x1F * x))
#define GET_SUBSIDY(x) (int64)((nHeight < ONE_YEAR_BLOCK_HEIGHT) ? ((nHeight < BURN_IN_BLOCK_HEIGHT) ? BX(x) : BD(x)) : x)

/** A burn-in period that tests various aspects of the system */
static const int BURN_IN_BLOCK_HEIGHT = 576;
/** Approximately one year worth of blocks, given the block time */
static const int ONE_YEAR_BLOCK_HEIGHT = 105120;
/** Approximately two years worth of blocks, given the block time */
static const unsigned int TWO_YEAR_BLOCK_HEIGHT = (2 * ONE_YEAR_BLOCK_HEIGHT);
/** Approximately four years worth of blocks, given the block time */
static const unsigned int FOUR_YEAR_BLOCK_HEIGHT = (4 * ONE_YEAR_BLOCK_HEIGHT);

/** Approximately one year worth of blocks, given the number of seconds */
static const int64 ONE_YEAR_IN_SECONDS = 31536000;
/** Approximately two years worth of blocks, given the number of seconds */
static const int64 TWO_YEARS_IN_SECONDS = (2 * ONE_YEAR_IN_SECONDS);
/** A burn-in period that tests various aspects of the system */
static const int64 BURN_IN_PERIOD_SECONDS = 176400;

#endif /* __BCOIN_H__ */
