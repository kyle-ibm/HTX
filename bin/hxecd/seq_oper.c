
/* @(#)37	1.4  src/htx/usr/lpp/htx/bin/hxecd/seq_oper.c, exer_cd, htxubuntu 5/24/04 17:25:32 */

/******************************************************************************
 *   COMPONENT_NAME: exer_cd
 * 
 *   MODULE NAME: seq_oper.c
 *
 *   FUNCTIONS: init_blkno
 *              set_blkno
 *              set_first_blk
 *              wrap
 *
 *   DESCRIPTION: Functions used in sequential operations.
 ******************************************************************************/
#include <string.h>
#include "hxecd.h"

/**************************************************************************/
/* initialize block number                                                */
/**************************************************************************/
init_blkno(pr,blkno)
struct ruleinfo *pr;
int *blkno;
{
  int blk, over;

  pr->first_block = set_first_blk(pr);
  over = pr->first_block + pr->num_blks - pr->max_blkno;
  if ( over > 0 )
     blk = pr->first_block - over;
  else
     blk = pr->first_block;
  if ( strcmp(pr->direction, "UP") == 0 ) 
     blkno[0] = blkno[1] = blk;
  else if ( strcmp(pr->direction, "DOWN") == 0 ) 
     blkno[0] = blkno[2] = blk;
  else if ( strcmp(pr->direction, "IN") == 0 ) {
     if ( blk > (pr->min_blkno + (pr->max_blkno - pr->min_blkno) / 2) ) {
        blkno[0] = blkno[2] = blk;
        blkno[1] = pr->max_blkno + pr->min_blkno - blk -1 - pr->num_blks ;
     } else {
        blkno[0] = blkno[1] = blk;
        blkno[2] = pr->max_blkno + pr->min_blkno - blk -1 + pr->num_blks ;
     } 
  } else 
     blkno[0] = blkno[1] = blkno[2] = blk;
  return;
} 

/*************************************************************************/
/* set first_block number for sequential operations                      */
/*************************************************************************/
set_first_blk(pr)
struct ruleinfo *pr;
{
  int   blk; 

  if ( (strcmp(pr->starting_block, "BOT")) == 0 )
     blk = pr->min_blkno;
  else if ( (strcmp(pr->starting_block, "MID")) == 0 )
     blk = pr->min_blkno + (pr->max_blkno - pr->min_blkno) / 2;
  else if ( (strcmp(pr->starting_block, "TOP")) == 0 )
     blk = pr->max_blkno - 1;
  else {
     blk = atoi(pr->starting_block);
     blk = blk + pr->min_blkno;
  }
  return(blk);
} 

/**************************************************************************/
/* set next block number                                                  */
/**************************************************************************/
set_blkno(blkno,direction,increment,num_blks)
int *blkno;
char *direction;
int  increment;
int  num_blks;
{
  if ( strcmp(direction, "UP") == 0 ) 
     blkno[0] = blkno[1] = blkno[1] + num_blks + increment;
  else if ( strcmp(direction, "DOWN") == 0 ) 
     blkno[0] = blkno[2] = blkno[2] - num_blks - increment;
  else if ( blkno[0] == blkno[1] )
     blkno[0] = blkno[2] = blkno[2] - num_blks - increment;
  else
     blkno[0] = blkno[1] = blkno[1] + num_blks + increment;
} 

/**************************************************************************/
/* check for file wrap around on sequential operations                    */
/**************************************************************************/
wrap(pr,blkno)
struct ruleinfo *pr;
int *blkno;
{
  int rc;

  if ( strcmp(pr->direction, "UP") == 0 ) {
     if ( (blkno[1] + pr->num_blks + pr->increment) > pr->max_blkno )
        rc = 1;
     else
        rc = 0;
  } else if ( strcmp(pr->direction, "DOWN") == 0 ) {
     if ( blkno[2] < pr->min_blkno )
        rc = 1;
     else
        rc = 0;
  } else if ( strcmp(pr->direction, "IN") == 0 ) {
     if ( blkno[1] > (pr->min_blkno + (pr->max_blkno - pr->min_blkno) / 2) ||
          blkno[2] < (pr->min_blkno + (pr->max_blkno - pr->min_blkno) / 2) )
        rc = 1;
     else
        rc = 0;
  } else {
    if ( ((blkno[1] + pr->num_blks + pr->increment) > pr->max_blkno) ||
         (blkno[2] < pr->min_blkno) )
       rc = 1;
    else
       rc = 0;
  }
  return(rc);
} 
