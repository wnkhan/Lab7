#ifndef CACHEBLK_INCLUDED_
#define CACHEBLK_INCLUDED_



typedef struct cacheblk
{
	int blknum;
	int dbit;
	int vbit;
	int tag;
	int mmblk;

}cacheblk;

#endif