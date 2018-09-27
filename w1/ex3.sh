#!/bin/sh

find /usr/lib -type f -exec ls -tl {} +

# find
#   find(1) search for files in a directory hierarchy
# -type f
#   search for regular files
# -exec command {} +
#   runs command on the selected files ({})
# ls -tl
#   ls(1) list directory contents
#   -t
#     sort by time, newest first
#   -l
#     long listing format (so we can check the modification date)

# We could have used ls -lRt /usr/lib with the recursive option (-R) but we
# would have been listing extra informations such as directory name,
# blocks used on disk per directory (the total line) and blank lines.
