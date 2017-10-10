# fondu

## Preface

Note: <em>This is a clone of the official CVS repo at http://sourceforge.net/cvs/?group_id=39411 , since it seems like it may be inactive and I wanted to add some updates.  The original developer is George Williams, the creator of FontForge.  The following information is taken from the original SourceForge project page at http://sourceforge.net/projects/fondu and was written by him as well (with some small updates by Zoltan Hawryluk).  All instances of "I", "me", "myself" and "my", therefore, refer to George Williams
</em>.


If you want changes to the code, please feel free to send Pull Requests or post an issue at https://github.com/zoltan-dulac/fondu .


## What is Fondu?

Fondu is a set of programs to interconvert between mac font formats and pfb, ttf, otf and bdf files on unix.

Dealing with mac fonts is hard on other operating systems because mac fonts are stored in the resource fork, and other operating systems do not support this concept. Fondu will extract the resource fork from either a macbinary file or a binhex file. Ufond will create a resource fork inside a macbinary file.

*   [Original Project page (sourceforge)](http://sourceforge.net/projects/fondu)
*   [Original cvs repository](http://sourceforge.net/cvs/?group_id=39411)
*   [These programs are available subject to the constraints of the bsd license](license.html)
*   [Builing This Package](#BuildingFondu)
*   [Fondu](#Fondu)
*   [Ufond](#Ufond)
*   [Dfont2Res](#Dfont2Res)
*   [Lumper](#lumper)
*   [Showfond](#Showfond)
*   [Tobin](#tobin)
*   [Frombin](#frombin)
*   [Rational](#Rational)
*   [Standards](#Standards)
*   [Bugs](index.html#Bugs)
*   [Downloads](index.html#Downloads)
*   [License](#License)
*   [Changelog](#Changelog)

### <a name="BuildingFondu">Building This Package</a>

Do the following commands:

```
$ configure
$ make
# make install
```

If you want this to run under Windows, I suggest compiling using [Cygwin](http://cygwin.org).

If you are running OSX, you may just want to use [Macports] or [Homebrew] to install using the commands `port install fondu` or `brew install fondu`, respectively.

### <a name="Fondu">Fondu</a>

```
fondu [-force] [-inquire] [-show] [-latin1] [-afm] [-trackps] macfile(s)
```

Fondu will read a series of mac files, check their resource forks and extract all font related items into seperate files.

The input files may be either macbinary files (.bin), binhex files (.hqx), bare mac resource forks or data fork resource files (.dfont, used by Mac OS/X). A bare resource fork may be generated easily be copying a file with a resource fork onto a floppy (or zip) with a DOS format. The mac will create an (invisible on the mac) folder called resource.frk in which the resource fork will reside as a bare file.

When run on Mac OS/X itself fondu will also be able to open the resource fork of a file directly.

Fondu will look through the resource fork for the following resources

*   POST -- postscript fonts  
    At most one postscript font may be stored in a file because all the POST resources are concatenated together to make the font.  
    Fondu will extract the font from the file, alter its format slightly and name it <fontname>.pfb in the current directory
*   sfnt -- truetype/opentype fonts  
    Fondu will extract each sfnt resource, find the fontname, and place each in a file called <fontname>.ttf (or <fontname>.otf)
*   NFNT/FONT -- bitmap fonts  
    Fondu will extract each resource, and convert it into a bdf font file. If a matching FOND is available some information will be gleaned from the FOND and placed in the bdf file as well.  
    Fondu assumes the fonts have the MacRoman encoding, and produces bdf files also with MacRoman, but if you specify -latin1 Fondu will attempt to change the encoding to iso latin1 (8859-1).
*   FOND -- family information  
    Normally fondu will used the FOND as a helper in creating the above files, but if you specify -trackps on the command line, and if the FOND contains the names of PostScript resource files, then fondu will recursively open those resource files (and convert the PS fonts contained in them). If -afm is given fondu will merge kerning data from the FOND and with bounding box and advance width data from the postscript resource files to produce an afm file.

If a file already exists then Fondu will ask you before saving on top of it.  
      if you specify -force then it will not ask you  
      if you specify -inquire it will ask you even if the file does not exist.  
You may answer with either 'y', 'n', or '=newfilename' (or 'q' for quit, or 'a' for all)

### <a name="Ufond">Ufond</a>

```
ufond [-dfont] [-macbin] [-res] [-script name] fontfiles ...
```

Ufond is the reverse of Fondu, it takes unix font files and wraps them up into a mac resource and creates a family for them which in turn get wrapped up in a macbinary or binhex file.

Ufond will read a series of .bdf, .ttf, .otf and .pfb files from the command line. All fonts with the same font family name will be placed in the same FOND. Ufond should handle associating a postscript font with a bitmap font properly. Ufond should handle bold, italic, etc. properly.

The generated macintosh files will be in one of three formats:

*   MacBinary (default)
*   dfont (data fork resource file format used by Mac OS/X)
*   resource (a bare resource fork. You have to figure out how to get this into the real resource fork)

Ufond normally assumes that your fonts are in the roman script system. If this is not true you may specify a script directly. Ufond knows the names of a few scripts (greek, cyrillic, hebrew, arabic) and you may enter these directly, otherwise you must know the macintosh script number.

Caveat: Mac OS/X no longer supports NFNT resources, if you want a usable bitmap font you must wrap it up inside a truetype wrapper, and ufond can't do that, try [fontforge](http://fontforge.sf.net/) instead.

According to Apple's docs OS/X does not support the FOND resource either, this should imply that Type1 resource fonts don't work either. They do however, but presumably that support will fade away.

### <a name="lumper">Lumper</a>

```
lumper font1.dfont font2.dfont font3.dfont
```

Merges any font resources ('NFNT', 'sfnt', 'FOND') from font2 (and font3 and ...) into font1.dfont.

### <a name="Dfont2Res">Dfont2Res</a>

```
dfont2res font.dfont
```

Will convert a font from the new macintosh dfont format to the old resource fork format.

### <a name="tobin">Tobin</a>

```
tobin [-creator 4char-string] [-type 4char-string] [-res rfork] dfork-filename
```

Will wrap up a series of files into a macbinary wrapper. On the mac it will read the resource fork and create/type info from the dfork-filename. On non-mac systems these must all be specified seperately.

### <a name="frombin">Frombin</a>

```
frombin mac-binary-files
```

Will unwrap a macbinary file. On the mac it creates the obvious file, with the attributes of the original. On non-mac systems it creates three files, one for the data-fork, one for the resource-fork and one containing random info about the file.

### <a name="Showfond">Showfond</a>

```
showfond fontfile
```

Will dump some information about the macintosh font resources (FOND, NFNT, sfnt) found in the file.

### <a name="Rational">Rational</a>

Fondu and ufond were initial experiments so I could make [pfaedit (now called fontforge)](http://fontforge.sourceforge.net/) edit fonts from the mac.

tobin and frombin were created because I can't find any open source way of creating macbinary files. Not even on the OS/X sites. Grump.

### <a name="Standards">Standards</a>

*   [MacBinary](http://www.lazerware.com/formats/macbinary.html) format
    *   The CRC used in the MacBinary header is the same as that used in [XModem](http://www.ohse.de/uwe/software/lrzsz.html) (I didn't find this in the MacBinary docs, but it is mentioned on other sites).
*   [Binhex](http://www.lazerware.com/formats/Specs/BinHex_Specs.pdf) format
*   [Mac Resource Fork](http://developer.apple.com/techpubs/mac/MoreToolbox/MoreToolbox-9.html)
*   Mac [NFNT/FONT](http://developer.apple.com/techpubs/mac/Text/Text-250.html) resource
*   Mac [FOND](http://developer.apple.com/techpubs/mac/Text/Text-269.html) resource
*   Mac [sfnt](http://developer.apple.com/techpubs/mac/Text/Text-253.html) resource
    *   This is basically a [truetype](http://fonts.apple.com/TTRefMan/) font file stuffed into a resource
*   The POST resource
    *   (I haven't seen this documented, it's behavior has been determined empirically)
    *   The connection between postscript file and FOND is described in the [Style Mapping Table](http://developer.apple.com/techpubs/mac/Text/Text-275.html) of the FOND
    *   [Type1 postscript fonts](http://partners.adobe.com/asn/developer/PDFS/TN/T1_SPEC.PDF) are described by Adobe
*   [Information determined emperically about mac font formats](http://pfaedit.sf.net/macformats.html#dfont)
*   The [BDF](http://partners.adobe.com/asn/developer/PDFS/TN/5005.BDF_Spec.pdf) file
*   The [AFM](http://partners.adobe.com/asn/developer/PDFS/TN/5004.AFM_Spec.pdf) file

### <a name="Bugs">Bugs</a>

*   Ufond does not add kerning information to the FOND.

Please report bugs to [fontforge-devel@lists.sourceforge.net](mailto:fontforge-devel@lists.sourceforge.net).

### <a name="Downloads">Downloads</a>

*   [Sources in a gzipped tarball](fondu_src-060102.tgz) 2-Jan-2006
*   [Sources in an rpm](fondu-051010-1.src.rpm) (10-Oct-2005)
*   [386 Redhat 7.3 executable rpm](fondu-051010-1.i386.rpm) (10-Oct-2005)
*   [PPC Suse executable rpm](fondu-020620-1.ppc.rpm) (20-June-2002)
*   [Mac OS/X package](Fondu-051010.pkg.zip) (10-Oct-2005)

### <a name="License">License</a>

> > <a name="license">Copyright</a> © 2001,2002,2003,2004,2005 by George Williams
> > 
> > Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
> > 
> > Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
> > 
> > Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
> > 
> > The name of the author may not be used to endorse or promote products derived from this software without specific prior written permission.
> > 
> > THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

### <a name="Changelog">Changelog</a>

*   9-Oct-2017
    * Zoltan Hawryluk updated the config.guess and config.sub files so that this program can now compile using Cygwin for Windows.
*   1-Jan-2006
    *   Han-Wen Nienhuys provided a patch to fold the mac build into the configured makefile & handle separate source & build directories
*   10-Oct-2005
    *   Someone pointed out a couple of errors in the res2data program (which copies the resource fork of a mac file into a data fork).
    *   Ages ago someone sent me another patch which I only just noticed. And applied.
*   25-Aug-2005
    *   Tigger says calls involving the FSSpec datatype are (mostly) depreciated so, don't use them.
*   22-Dec-2004
    *   Neil Parker provided a patch for a crash from an unspecified string format in the FOND postscript names table.
*   25-Sept-2004
    *   Fondu would crash if given a type1 font where the /CharStrings dictionary was initialized as a bigger dictionary than was needed.
*   22-Sept-2004
    *   Fondu failed to generate a proper error message (usually failed) when it could not find a resource fork.
*   19-Aug-2004
    *   Fixed a bug in reading mac binary on mac
*   27-May-2004
    *   Fondu now generates real afm files
    *   Added a few more arguments to fondu
*   03-Feb-2004
    *   created lumper
    *   showfond now dumps out the name of 'sfnt's
*   04-Nov-2003
    *   ufond had a very simplistic bdf parser, which failed to read many bdf files.
*   28-Apr-2003
    *   Oops. Was outputting pfb section byte counts with the wrong endian-ness.
*   22-Jan-2003
    *   ufond had problems with FONDS containing multiple styles and multiple point sizes
*   23-Dec-2002
    *   Fondu could crash when generating an afm file.
*   21-Dec-2002
    *   I was generating bad macbinary files
        *   I hadn't noticed that the various file sections need to be padded out to a multiple of 128 bytes.
            *   This meant I sometimes read macbinary files incorrectly too
        *   I got the CRC calculations wrong.
    *   I got sick and tired of the fact that I can't find any open source programs that create macbinary files. So I wrote my own-- [tobin](#tobin).
*   26-Oct-2002
    *   Changed fondu so it can extract a bare ttf/otf file (ie one that isn't in a resource file) from a binhex or macbinary wrapper. It's easy, and ttf files are now accepted on macs, so someone might binhex one out of caution.
*   23-Oct-2002
    *   dfont2res would produce invalid macbinary files on some dfonts.
*   17-Oct-2002
    *   Added an empty glyph-encoding sub-table for FONDs produced by ufond
*   22-June-2002
    *   added a configure script
*   20-June-2002
    *   Oops. When Fondu was looking for the name of an 'sfnt' (ttf) resource, it was not looking for an apple macroman name. The most likely case. I should do so now.
*   25-Apr-2002
    *   Added some patches from Grigory Entin
        *   clean option in makefile didn't clean everything
        *   showfond didn't work as well as it might with long filenames
        *   bug when reading NFNTs in a file with multiple NFNT resources
*   28-Feb-2002
    *   On Mac OS/X it is now possible to open an old-style resource file directly.
*   5-Feb-2002
    *   Added the dfont2res program.
    *   Many bug fixes
