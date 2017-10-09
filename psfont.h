/* Copyright (C) 2000-2004 by George Williams */
/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.

 * The name of the author may not be used to endorse or promote products
 * derived from this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _PSFONT_H_
#define _PSFONT_H_

/* pfb section headers.
  There seem to be three and a half of them. the first is a the start of the
   file and is 6 bytes long "\200\001x\005\000\000", the second is right after
   the newline after eexec and is 6 bytes "\200\002I\224\000\000", the third
   is right before the zeros (after the encoded data) and is "\200\001\024\002\000\000"
   the last is at the end of file and is only two bytes "\200\003"
  I think that the \200 byte indicates a header, the next byte is 1 for ascii,
   2 for binary and 3 for eof, then next 4 bytes are the length (not present
   for eof headers) with the first byte the least significant.
*/

struct charprocs {
    int cnt, next;
    char **keys;
    void **values;
};

struct psdict {
    int cnt, next;
    char **keys;
    char **values;
};

struct pschars {
    int cnt, next;
    char **keys;
    unsigned char **values;
    int *lens;
    int bias;		/* for type2 strings */
};

struct fontinfo {
    char *familyname;
    char *fullname;
    char *notice;
    char *weight;
    char *version;
    double italicangle;
    unsigned int isfixedpitch:1;
    double underlineposition;
    double underlinethickness;
    int em, ascent, descent;	/* Generated by Fontographer (and us) */
    int fstype;			/* 2=>no embedding, 4=>print, 8=>edit */
    /* Multiple master */
    char *blenddesignpositions;
    char *blenddesignmap;
    char *blendaxistypes;
};

struct private {
    struct psdict *private;
    struct pschars *subrs;	/* (optional, required if othersubrs is present) */
			/* 0-2 part of Flex, 3 hint replacement, 4 and up for charstrings */
    int leniv;			/* (optional) must be 4 for old interpreters (number of rand chars at start of charstrings entries) */
#if 0
    int bluefuzz;		/* (optional) (expand bluezones by this much, def=1) */
    double bluescale;		/* (optional) if the current pointsize in pixels is less than this value then do overshoot hinting */
    int blueshift;		/* (optional) */
    double bluevalues[14];	/* <=7 pairs of integers, first less than second, (may be empty) */
			/* first pair is baseline overshoots, other pairs above baseline */
    double expansionfactor;	/* (optional) only for languagegroup==1 (CJK) */
    double familyblues[14];	/* (optional) bluevalues for family, can override local entry at small pointsizes */
    double familyotherblues[10];/* (optional) otherblues for family */
    unsigned int forcebold:1;	/* (optional) */
    int languagegroup;		/* (optional) (0=>latin, greek, cyril, etc.), (1=>CJK)*/
    int leniv;			/* (optional) must be 4 for old interpreters (number of rand chars at start of charstrings entries) */
    char *minfeature;		/* obsolete, required must be {16 16} */
    char *nd;			/* "noaccess def" (may also be named "|-") */
    char *np;			/* "noaccess put" (may also be named "|") */
    double otherblues[10];	/* (optional) descender blue zones */
    struct pschars *othersubrs;	/* (optional) shouldn't contain user defined subs */
    int password;		/* obsolete, required must be 5839 */
    char *rd;			/* "{string currentfile exch readstring pop}" (may also be named "-|") */
    unsigned int rndstemup:1;	/* (optional) obsolete, false if languagegroud==1 */
    double stdhw[1];		/* (optional) dominant horizontal stem width */
    double stdvw[1];		/* (optional) dominant vert */
    double stemsnaph[12];	/* (optional) common h stem widths (at most 12, includes stdhw, sorted by increasing size) */
    double stemsnapv[12];	/* (optional) common v stem widths*/
    struct pschars *subrs;	/* (optional, required if othersubrs is present) */
			/* 0-2 part of Flex, 3 hint replacement, 4 and up for charstrings */
    int uniqueid;		/* (optional) seems same as fontdict entry. why's it here too? what of XUID? */
/* CID entries */
    int subrmapoffset;		/* Offset to the start of this font's subr strings map */
    int sdbytes;		/* bytes in each pointer in the map */
    int subrcnt;		/* number of subroutines, number of pointers-1 in the map */
#endif
};

typedef struct fontdict {
    int fonttype;
    double fontmatrix[6];
    char *fontname;		/* (optional) */
    struct fontinfo *fontinfo;
    int languagelevel;		/* (optional) */
    int wmode;			/* (optional) chooses between alternate metric sets */
/* non-type0 entries */
    int isadobestd;
    char *encoding[256];
    double fontbb[4];
    int uniqueid;		/* (optional) open range between 4,000,000 and 4,999,999 */
    int xuid[20];		/* (optional) */
/* Type1 specific values */
    int painttype;		/* 0 (filled) 2 (stroked) */
    double strokewidth;		/* (optional) only if painttype==2 */
    struct psdict *metrics;	/* (optional) */
    struct psdict *metrics2;	/* (optional) */
    struct pschars *chars;
    struct charprocs *charprocs;
    struct private *private;
    unsigned int wasbinary: 1;
    unsigned int wascff: 1;
/* CID stuff */
    int fdcnt;			/* For the underlying dictionaries */
    struct fontdict **fds;
    char *cidfontname;
    int cidfonttype;
    double cidversion;
    char *registry;
    char *ordering;
    int supplement;
    int mapoffset;
    int fdbytes;
    int gdbytes;
    int cidcnt;
    unsigned char **cidstrs;
    short *cidlens;
    short *cidfds;
/* CFF stuff */
    struct splinefont *sf;
/* MM stuff */
    char *blendfunc;
    char *weightvector;
    char *cdv;
    char *ndv;
    struct psdict *blendprivate;
    struct psdict *blendfontinfo;
} FontDict;

struct cidbytes {
    int fdbytes, gdbytes, cidcnt;
    int cidmapoffset;
    int fdcnt;
    struct fddata {
	int leniv;
	int subrmapoff, sdbytes, subrcnt;
	int flexmax;
	unsigned int iscjk:1;
	struct pschars *subrs;
    } *fds;
    int *fdind;
    int errors;
};

struct fd2data {
    int defwid, nomwid;		/* For Type2 charstrings */
    struct pschars *subrs;
    FILE *private;		/* Subroutines get stored in the private file immediately after the private dict */
    int eodictmark, fillindictmark;
    int privatelen;
};

extern char *AdobeStandardEncoding[256];
#endif