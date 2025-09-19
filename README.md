MP3 Tag Reader and Editor (ID3v2.3)
===================================

Overview 
--------
This is a C-based command-line program to view and edit ID3v2.3 
metadata inside MP3 files. You can check or update information 
like Title, Artist, Album, Year, Genre, and Comment.

The program reads the MP3 in binary mode and either displays 
the metadata or updates it. Updates are done by creating a 
temporary copy of the file with the new tag applied.

Features
--------
- View ID3v2.3 tags: Title, Artist, Album, Year, Genre, Comment
- Edit individual tag fields
- Manual endian conversion for frame sizes
- Simple command-line interface

File Structure
--------------
main.c     : Parses arguments and calls view/edit functions
View.c     : Reads and displays tag frames
Edit.c     : Writes updated tags into a temporary MP3
header.h   : Shared function declarations

Compilation
-----------
Use gcc or any standard C compiler:

    gcc *.c

Usage
-----
1. View tags
   ./a.out -v <file.mp3>

   Example:
   ./a.out -v sample.mp3

   Output:
   ===== MP3 Tag Viewer =====
   Title   : gana_gana_mana 
   Artist  : Yo Yo Honey Singh - [SongsPk.CC]
   Album   : Yaariyan
   Year    : 2025
   Genre   : Bollywood Music - [SongsPk.CC]
   Comment : eng
   ==========================

2. Edit a tag
   ./a.out -e <file.mp3> <option> <new_value>

   Options:
     -t   Title
     -a   Artist
     -A   Album
     -y   Year
     -g   Genre
     -c   Comment

   Example:
   ./a.out -e song.mp3 -a "HipHop"

   Output:
   ===== MP3 Tag Updated =====
   TPE1 -> HipHop
   ===========================

3. Help
   ./a.out --help

---------------
- ID3v2.3 format is assumed
- Each frame has:
    Frame ID (4 bytes)
    Frame size (4 bytes, big endian)
    Flags (3 bytes in this program)
    Content (variable size)
- Endianness handled manually
- Editing writes to "temp.mp3" which replaces the original

