#!/bin/sh

WORDS="words"

# /usr/**/dict/words is not on my linux distribution
# I found a sample on users.cs.duke.edu

if [ ! -f "$WORDS" ]; then
  echo "Downloading words file sample"
  wget -q https://users.cs.duke.edu/~ola/ap/linuxwords -O $WORDS
fi

[ -r "$WORDS" ] || { echo "Cannot read $WORDS" ; exit 2 ; }

# Checks if a given char is a vowel
is_vowel()
{
  vowels="aAeEiIoOuU"
  for i in $(seq 1 10); do
    vowel=$(echo "$vowels" | cut -c "$i")
    if [ "$vowel" = "$1" ]; then
      return 0
    fi
  done
  return 1
}

# Computes the max consecutive vowels sequence for a given word
consecutive_vowels()
{
  cv=0
  maxcv=0
  wordLength=$(echo "$1" | tr -d '\n' | wc -c)
  for i in $(seq 1 "$wordLength"); do
    if is_vowel "$(echo "$1" | cut -c "$i")"; then
      cv=$((cv + 1))
    else
      cv=0
    fi
    [ "$maxcv" -lt "$cv" ] && maxcv=$cv
  done
  echo "$maxcv"
}

# Print out the number of max consecutive vowels in the word with the longest sequence of consecutive vowels
extract()
{
  maxcv=0
  maxw=""
  while IFS= read -r l; do
    w=$(echo "$l" | tr -d '\n')
    cv=$(consecutive_vowels "$w")
    [ "$cv" -gt "$maxcv" ] && { maxcv=$cv ; maxw=$w ; }
  done < "$WORDS"
  #echo "$maxw" # The matching word
  echo "$maxcv"
}

# Retrieve word
extract

# Example with https://users.cs.duke.edu/~ola/ap/linuxwords file
#
#~/system_software/w1 > wc -l words
#45402 words
#~/system_software/w1 > time ./ex2.sh
#5
#./ex2.sh  6463,63s user 2036,30s system 126% cpu 1:51:58,45 total
